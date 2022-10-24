# ADA HW_2
> 范秉逸 B10902117
## 1 reference Myself
## 2 reference Myself
## 3 reference https://youtu.be/0EgQs2WWres
## 4 reference Myself
## 5 reference Myself
## 6 reference Myself
## 5
### (a)
i from 1 to 7<br>
- On Day 9, buy 7-th weapon. t(i) is 5 and p(i) is 3
- On Day 21, buy 1-th weapon. t(i) is 10 and p(i) is 4
- On Day 28, buy 5-th weapon. t(i) is 25 and p(i) is 2
- On Day 32, buy 2-th weapon. t(i) is 3 and p(i) is 5
### (b)
### Algorithm
m is the number of valid weapon<br>
v[ ] is a min heap which store the valid weapon. It will put the weapon with mininmium price on root
1. Sort the weapon by the day t[i]
2. For every attack, we put all the weapon, which is not yet been put in V[ ] and available on that day (t(i) <= T(i)), to V[ ].
3. Find the mininmium price among the valid weapon( min(p(V[i])) )
4. Record the weapon we found and mark it used (remove it from V[ ])
### Prove
#### 1. Cast Optimization Problem
- P(i): minimal cost of weapon on i-th attack
- Goal: P(N)
#### 2. Prove Optimal Substructure
#### Suppose OPT is an optimal solution to C(i), there are m cases
- Valid weapon 1 in OPT is an optimal solution of P(i - 1) + p(v[1])
- Valid weapon 2 in OPT is an optimal solution of P(i - 1) + p(v[2])
<br>...
- Valid weapon m in OPT is an optimal solution of P(i - 1) + p(v[m])
#### 3. Prove Greedy-Choice Property
#### Proof via contradiction (use the attack 3 ≤ 𝑖 < 4 for demo)
- Assume that there is no OPT including this greedy choice (the index of the head of min heap is j)<br>
- If $P(i - 1) + p(v[i]) i \neq j > P(i - 1) + p(v[j])$ , we can replace any items in OPT with item 𝑗
#### The total price must be equal or smaller, because item 𝑗 has the lowest price
#### Thus, by greedy choice, by this algorithm, we can get minimal price
### Time Complexity
- Sorting the weapon will take O(MlogM) time complexity
- Evertime we put a new value in the min heap, it will cost O(logM)
- Evertime we get a minimal value in the min heap, it will cost O(1) to get and O(1) to update the heap <br>
- We have an iteration for a for loop to run through T, it will take O(N) time complexity. 
- In the whole loop, we will put at most M weapon into the min heap, and it will take O(M) * O(logM) time complexity<br>
- N ∈ O(M)<br>
#### Thus, Time Complexity is 
$$O(MlogM) + O(N) + O(MlogM) = O(MlogM)$$
### (c)
i from 1 to 9<br>
- On Day 9, buy 6-th weapon. t(i) is 5 and p(i) is 3
- On Day 21, buy 2-th weapon. t(i) is 10 and p(i) is 1
- On Day 31, buy 3-th weapon. t(i) is 16 and p(i) is 2
- On Day 39, buy 8-th weapon. t(i) is 32 and p(i) is 5
- On Day 45, buy 7-th weapon. t(i) is 28 and p(i) is 6
### (d)
### (e)
### (f)
## 6
### (a)
### Algorithm
V[ ] stores the velocity of participants, from 1 to N.<br> 
d[ ] stores the difference<br>
ans[ ] stores every i groups min total difference
1. Sort all the participants by their velocity in ascending order
2. Use a for loop to calculate the difference of V[i] and V[i + 1], i from 1 to N - 1, and store them in d[i].
3. Sort the d[ ] from 1 to N - 1 in descending order, and let d[0] = 0
4. Calculate the velocity difference between V.head and V.tail and store it in the variable minTotalDiff
5. Use a for loop, i from 1 to N. In each loop, minTotalDiff -= d[i - 1]. Store minTotalDiff in ans[i]
### Correctness
- If we have one group, we have $min_1$ and $max_1$. Total difference is $max_1 - min_1$ 
- If we have two groups, it means that we cut the one groups into two groups
- On the left side of the cut place, we have the max number of the left group, called $max_2$
- On the right side of the cut place, we have the min number of the right group, called $min_2$
- Total difference is $(max_1 - min_2)+(max_2 - min_1) = (max_1 - min_1)-(min_2-max_2)$
- If we can get max difference between two adjacent numbers, we can get min total difference of two groups
- If we have three groups, let min total difference of two groups minus the less max difference between two adjacent numbers. Then, we get min total difference of 3 groups
- If we have i groups, let min total difference of i - 1 groups minus the least i-th max difference between two adjacent numbers. Then, we get min total difference of i groups    
<br>Thus, by the algorithm we can get all difference between two adjacent numbers in descending order. Then, we can get min total difference of all i groups
### Time Complexity
1. Sort all the participants by their velocity in ascending order : O(NlogN)
2. Use a for loop to calculate the difference of V[i] and V[i + 1], i from 1 to N - 1, and store them in d[i] : O(N)
3. Sort the d[ ] from 1 to N - 1 in descending order, and let d[0] = 0 : O(NlogN)
4. Calculate the velocity difference between V.head and V.tail and store it in the variable minTotalDiff : O(1)
5. Use a for loop, i from 1 to N. In each loop, minTotalDiff -= d[i - 1]. Store minTotalDiff in ans[i] : O(N)
- Total :
$$O(NlogN) + O(N) + O(NlogN) + O(1) + O(NlogN) = O(NlogN)$$

### (b)

### (c)
{ {1, 2, 3, 4} }<br>
{ {1}, {2}, {3}, {4} }<br>
{ {1, 2}, {3, 4} }<br>
{ {1, 2}, {3}, {4} }<br>
{ {1}, {2}, {3, 4} }<br>
{ {1, 3}, {2, 4} }<br>
{ {1, 3}, {2}, {4} }<br>
{ {1}, {3}, {2, 4} }<br>
{ {1, 4}, {2, 3} }<br>
{ {1, 4}, {2}, {3} }<br>
{ {1}, {4}, {2, 3} }<br>
{ {2, 3, 4}, 1} }<br>
{ {1, 3, 4}, 2} }<br>
{ {1, 2, 4}, 3} }<br>
{ {1, 2, 3}, 4} }<br>
15 Groups

### (d)

### (e)
{ {1}, {2}, {3}, {5} }<br>
{ {1, 2}, {3, 5} }<br>
{ {1, 2}, {3}, {5} }<br>
{ {1}, {2}, {3, 5} }<br>
{ {1, 3}, {2}, {5} }<br>
{ {1}, {3}, {2, 5} }<br>
{ {1}, {5}, {2, 3} }<br>
{ {2, 3, 5}, {1} }<br>
{ {1, 2, 3}, {5} }<br>
9 Groups