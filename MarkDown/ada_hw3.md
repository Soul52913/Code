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
Minquan W. Rd. is the station from which taking a ride to the farthest station from it costs the least. <br>
1. Look at the graph of all station and choose the stations in the middle of the graph in my checklist.
2. Look 1 by 1 in the checklist to find the station from which taking a ride to the farthest station from it costs the least in the website.
3. Find the answer.
### (c)
Assume there exist k Professor Cheng won't construct any point-cycle.<br>
Try to build a graph with no point cycle :<br>
K professor Cheng which 1 point to 2, 2 point to 3, ...,and k-1 point to k.<br>
Since every point must have exactly one out-degree, k must point to a previous point. Thus, k Professor Cheng must construct at least one point-cycle. Contradiction !<br>
Let n be the minimum index in a point-cycle, n > 0 and k be the length of the point-cycle, k > 0. $a_k = F_k(n) = n$. Thus $ a_{k+k} = F_{k+k}(n) = n $. Thus, $ a_{N+T} = a_{N} $
### (d) & (e)
#### Time Complexity & explain
1. create an array loop[ ][ ] (start from 1), an array path[N] (start from 1), an array ans[N] (start from 1), an array Length[N - 1] (start from 1), and the tranpose graph.
2. We run dfs in the tranpose graph. For each point, we marl them visited. And use a vector to store the path. If we reach a point with 0 out-degree, we pop the point in the path until we have another road to travers. If the path is empty, start from a point we haven't visit. If we reach to a visited point, this mean our path complete a loop. We store the path in loop(push_back) and clear path. Start from a point we haven't visit. Recursively do this until we visit all the point. Thus, we have all the loop.
3. Let all points unvisited
4. Find the answer for every loop. Start with a point with index c in loop[j]. Let K = K % loop[j].len(). If c - K < 0, K = loop[j].len() - (K - c - 1). And store ans[loop[j][c]] = loop[j][K]. By this we find all answer of points in loops. This is to prevent us from moving out of the array size.
5. Run dfs in the tranpose graph again. This time we deal with points not in loops. If we visit a point, mark it visited. When we reach the points that have no answer, let the index of the point in the path[] be c and create another path[] that start a point in a loop. If c - K < 0, K = K - c - 1. This mean we reach into a loop. Then, we can use the method in 4. to find the answer of path[c], save it in ans[path[c]]. If we reach a point with 0 out-degree, we pop the point in the path until we have another road to travers. If the path is empty, start from a point we haven't visit. If we reach to a visited point, start from a point we haven't visit. Recursively do this until we visit all the point. Thus, we get all i-th point answer in ans[ ].
#### Time Complexity
1. 2. Run all N points by dfs : O(N)
2. 3. Let all points unvisited : O(N)
3. 4. Run all points in the loops and find answer : O(N) * O(1) = O(N)
4. 5. Run all N points by dfs and find answer : O(N) * O(1) = O(N)
Total : O(N) + O(N) + O(N) + O(N) = O(N)
Find answer: O(1) //search ans[i]
### (f) & (g)


## 6
### (a)
##### algorithm:
stack[] to store our stack
1. create a array sum[N]. In each sum[i] store the sum of value from 0-th to i-th, so we can get the sum of top x node by sum[stack.size] - sum[stack.size - x] which is O(1). By this we can solve dd.
2. pop and push just like normal stack. But also need to maintain our sum. If is pop, pop the sum[stack.size] too. If is push, sum[stack.size] = sum[stack.size - 1] + stack[stack.size]. By this we can solve PUT and TAKE.
3. For cc we pop x node out and save it in the array O[]. We use quick select algorithm to save $ \lceil {x/k} \rceil $ (call it outNumber)-th biggest value as Min
4. Then we push the node to the stack (use PUT) in origin order but only if the value of the node is smaller than Min. For the node >= Min, we add them together. By 3. and 4. we can solve cc.
##### Accounting method for stack
1. Guess per-op amortized costs:
<table>
  <tr>
    <th>Operation</th>
    <th>Actual cost</th>
    <th>Amortized cost</th>
    <th>Credit change</th>
  </tr>
  <tr>
    <td>PUT</td>
    <td>1</td>
    <td>k+2</td>
    <th>存 k+1 元存在帳戶裡</th>
  </tr>
  <tr>
    <td>TAKE</td>
    <td>1</td>
    <td>0</td>
    <th>從 popped object 的帳戶領 1 元</th>
  </tr>
  <tr>
    <td>CC x k</td>
    <td>k+1</td>
    <td>0</td>
    <th>從每個 deleted object(最多x個) 的帳戶領 k + 1 元</th>
  </tr>
  <tr>
    <td>DD x</td>
    <td>1</td>
    <td>1</td>
    <th>不變動</th>
  </tr>
</table>

1. Validity check: Show that every object has credit ≥ 0
    1. push: the pushed object is deposited $1 credit
    2. pop and CC: use the credit stored with the popped object
    3. There is always enough credit to pay for each operation
    If we put T items in the stack, we will have T*(k+1) dollar. Since we can only TAKE x times and CC y items $ (x + y \leq T, 1 \leq k \leq k) $. 
    Thus, $ (x*(k+1)+y) \leq T*(k+1)$. Prove 3.
2. Per-op amortized costs for PUT is O(k) and TAKE, CC is O(1), so total cost is o(kM) < o( $ Mk^{1.1101420} $)
#### (b)
##### Potential method
1. Guess $ Φ(T_i) $ , where T.sum is the number of inserted objects and T.size is the table size
2. Validity check:
    1. Φ($ T_0 $) = 0, because T.sum and T.size is initially 0
    2. Φ($ T_i $) ≥ 0, because T.size must $ \geq$ T.sum to put thing s into the table 
3. Compute the amortized cost of INCREMENT:
    1. Let $ F_j $ is the j-th Fibonacci number. By the speciality of Fibonacci sequence, we know that $ (F_n * \phi(\approx1.618))\approx F_{n+1} $
    2. For example, $ F_3 $ = 2, and $ F_7 $ = 13
    3. $ C_i = c_i + Φ(T_i) − Φ(T_{i-1}) = F_n - (F_{n-1} - 1) \approx F_{n-1} * \phi - F_{n-1} + 1 = \phi$ is Constant
4. All operations have O(1) amortized cost, so the total cost of n operations is O(n)