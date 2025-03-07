To multiply a chain of matrices, the naive solution is to just do it sequentially. However consider three matrices:   
$A (10 \times 100)$   
$B (100 \times 5)$   
$C (5 \times 50)$   
The product $ABC$ can have two associations:   
1. $(AB)C$   
2. $A(BC)$   
   
The algorithm to multiply two matrices of order $(p\times q)$ and $(q\times r)$ is of order $O(pqr)$ and the resultant matrix is $(p\times r)$   
```
1 if columns [A]  rows [B]

2    then error "incompatible dimensions"

3    else for i 1 to rows [A]

4             do for j 1 to columns[B]

5                    do C[i, j]  0

6                       for k  1 to columns [A]

7                           do C[i ,j]  C[i ,j] + A [i, k] B[k, j]

8         return C

```
   
In the first association, the order of time complexity is:   

$$
\underbrace{10 \cdot 100\cdot 5}_{(AB)} + \underbrace{10\cdot 5\cdot 50}_{((AB)C)} = 5000+2500=7500
$$
In the second association, the order of time complexity is:   

$$
\underbrace{100 \cdot 5\cdot 50}_{(BC)} + \underbrace{10\cdot 100\cdot 50}_{(A(BC))} = 25000+50000=75000
$$
It is clear that the order of associations does matter.   
To efficiently calculate the order of multiplication of matrix chain, Dynamic Programming is utilized.   
   
The elements of Dynamic Programming are:   
1. Optimal substructures.   
2. Overlapping subproblems.   
3. Memoization.   
   
   
### Optimal Substructure   
In matrix chain, it can be noticed that if sub-chain $A\_{1:k}$ of some larger chain $A\_{1:n}$ contains optimal associativity, then, no other associativity exists for $A\_{1:k}$ that is more optimal than the current one, because if it did exist, then $A\_{1:k}$ would have that associativity instead.    
It is trivial to prove optimal substructure if hypothesized: Start by assuming the opposite (the selected substructure is not optimal), then prove by contradiction.   
Based on this, an optimal strategy is to consider some sub-chain $A\_{i:j}$   
In this chain, if we take a random position k, and paranthesize it, then two sub-chains are formed: $A\_{i:k}$ and $A\_{k+1:j}$   
Now the cost of finding $A\_{i:j}$'s optimal associativity is the sum of costs of $A\_{i:k}$ and $A\_{k+1:j}$ and the cost of combining them.   
The cost of combining is calculated as follows:   
The number of rows in the $i^{th}$ matrix is denoted by $p\_i$   
1. The first matrix in $A\_{i:k}$ contains $p\_{i-1}$ rows, since rows of the first matrix dissolve the rows of second matrix in multiplication, i.e., a matrix of $(p\times q)$ multiplied by $(q\times r)$ give $(p\times r)$, no matter what is multiplied by the first matrix, the resultant matrix will also have $p\_{i-1}$ rows.   
2. By the same logic, the resultant matrix in $A\_{i:k}$ will have the same number of columns as the last matrix in $A\_{i:k}$, if the last matrix has index k, then the number of columns in the resultant matrix is $p\_k$   
3. In $A\_{k+1:j}$, the resultant matrix will have $p\_{j}$ rows from the abovementioned logic.   
4. Hence, the resultant matrix will take $p\_{i-1}p\_kp\_j$ order of time to complete.   
   
To find the optimal solution for $A\_{i:j}$, one needs to minimize cost over all the $k$s between $i$ and $j$.   

$$
m[i, j]=\begin{cases}0 & if\space i=j\\\min_k[m(i, k)+m(k+1,j)+p_{i-1}p_kp_j] & if\space i < j \end{cases}
$$
   
### Overlapping subproblems   
For a dynamic programming algorithm to be efficient, more subproblems shall overlap. For example, in Matrix chain multiplication, many smaller sub-chains would be referenced more while solving because other larger sub-chains would recursively break down into some combination of smaller sub-chains. Hence, it makes sense to not recompute the solutions to smaller chains again and store them in a memoized array somewhere for referencing when bigger subproblems require them.   
The more overlapping subproblems, the more the efficiency of a Dynamic Programming algorithm.   
A bottom up approach to solve dynamic programming is done by iteratively building up an array containing solutions of smaller subproblems and further using those solutions to calculate ones for the larger subproblems until finally solving the problem.   
### Memoization   
Top-down memoization is another way to perform dynamic programming. A top-down recursive step is followed, but the results of the recursive steps are cached into a memoized array somewhere, so that when the larger subproblems require solutions of smaller subproblems, the memoized array can be referenced. However, this method uses a bit more memory.   
