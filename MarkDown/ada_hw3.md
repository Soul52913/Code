# ADA HW_3
> 范秉逸 B10902117
## 1 reference Myself
## 2 reference Myself
## 3 reference Myself
## 4 reference Myself
## 5 reference Myself
## 6 reference Myself
## 5
### (a)
By Kosaraju Algorithm, we know that if a sequence of starting time of a series number is same as the inverse sequence of finishing time, this series number is in the same SCC <1><br> 
Thus, if vertices a and b are in the same SCC and their starting time is $ s_b < s_a $, their finishing time must be $ f_a < f_b $ <br>
If there is a node between a and b called c, their finishing time is $ f_a < f_c < f_b $, and a b is in the same SCC, $ s_b < s_c < s_a $ must exist. Thus, by <1>, a, b, and c are in the same SCC.
### (b)
Taipei Main Station is the station from which taking a ride to the farthest station from it costs the least. <br>
1. Look at the graph of all station and choose the stations in the middle of the graph in my checklist.
2. Look 1 by 1 to find the station from which taking a ride to the farthest station from it costs the least in the website.
3. Find the answer.
### (c)
Assume there exist k Professor Cheng won't construct any point-cycle.<br>
Try to build a graph with no point cycle :<br>
K professor Cheng which 1 point to 2, 2 point to 3, ...,and k-1 point to k.<br>
Since every point must have exactly one out-degree, k must point to a previous point. Thus, k Professor Cheng must construct at least one point-cycle. Contradiction !<br>
Let n be the minimum index in a point-cycle, n > 0 and k be the length of the point-cycle, k > 0. $a_k = F_k(n) = n$. Thus $ a_{k+k} = F_{k+k}(n) = n $. Thus, $ a_{N+T} = a_{N} $
### (d) & (e)
1. create an array Point[N - 1][N] (start from 1) and Length[N - 1] (start from 1)
2. Find out evey cycle and put it into each row. In each row, each column save the label of the sequence of a single cycle.
3. Length[i] save the length of Point[i] single cycle
4. To find$ F_K(i) $, we first find c which Point[r][c] = i. Then let K = K % Length[r].
5. If K + c > Length[r], K = K - (Length[r] - c) - 1. And change c which Point[r][c] = Point[Length[r]]. 
6. $ F_K(i) = Point[r][c + K] $<br>
#### Explain
In each row, we save the label of the sequence of a single cycle in each column. We do this to avoid running a sequence into a loop. This will prevent us from dropping into a infinite loop. Since there is only N label, it only take O(N)<1> to search the starting point. Next, in each row, we will find the next K sequence to get $ F_K(i) $. But we need to watch out not to let c + K exceed Length[r]. By doing 4. and 5. , we can make sure c + K never exceed Length[r].
#### Time Complexity
1. <1> : O(N)
2. Find the next K sequence to : O(1)
3. Don't let c + K exceed Length[r] : O(1)
4. Get F_K(i) : O(1)
Total : O(N) + O(1) + O(1) + O(1) = O(N)
### (f)
