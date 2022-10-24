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