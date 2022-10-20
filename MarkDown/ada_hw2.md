# ADA HW_2
> 范秉逸 B10902117
## 1 reference Your Mom
## 2
## 3
## 4
## 5
### (a)
i from 1 to 7<br>
- On Day 9, buy 7-th weapon. t(i) is 5 and p(i) is 3
- On Day 21, buy 1-th weapon. t(i) is 10 and p(i) is 4
- On Day 28, buy 5-th weapon. t(i) is 25 and p(i) is 2
- On Day 32, buy 2-th weapon. t(i) is 3 and p(i) is 5
### (b)
#### Algorithm
m is the number of valid weapon<br>
v[ ] is the array of valid weapon which store i
1. For every attack, we push all the weapon which is not yet been pushed and available on that day (t(i) <= T(i)). Then store them into V[ ]
2. Find the mininmium price among the valid weapon( min(p(V[i])) )
3. Record the weapon we found and mark it used (remove it from V[ ])
#### Prove
#### 1. Cast Optimization Problem
- P(i): minimal cost of weapon on i-th attack
- Goal: P(N)
#### 2. Prove Optimal Substructure
#### Suppose OPT is an optimal solution to C(i), there are 4 cases
m is the number of valid weapon<br>
v[ ] is the array of valid weapon which store i
- Valid weapon 1 in OPT is an optimal solution of P(i - 1) + p(v[1])
- Valid weapon 2 in OPT is an optimal solution of P(i - 1) + p(v[2])
<br>...
- Valid weapon m in OPT is an optimal solution of P(i - 1) + p(v[m])
#### 3. Prove Greedy-Choice Property
#### Proof via contradiction (use the attack 3 ≤ 𝑖 < 4 for demo)
- Assume that there is no OPT including this greedy choice (choose 2)<br>
→ all OPT use v[1], v[2], v[4] for i-th attack
- v[4] cannot be used
- weapon with price p(v[2]) < p(v[2]) → otherwise we can use a p(v[2]) to have a better output
- weapon with price p(v[1]) < p(v[1]) → otherwise we can use a p(v[1]) to have a better output
- We cannot use a p(v[1]) with the constraints (at most 5 + 4 = 9)