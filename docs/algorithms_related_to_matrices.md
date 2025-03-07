Matrices are 2-dimensional arrays of integers. The size of matrix is represented as $n\times m$ where n is the number of rows and m is the number of columns.

A matrix with size $n\times 1$ is called a vector.

The transpose of a matrix is obtained by swapping its rows with columns.

A matrix of size $n\times n$ is called a square matrix.

Elements of a matrix can be represented as $A[i, j]$ where the element is in the $i^{th}$ row and $j^{th}$ column of the matrix $A$.
# Matrix addition
Two Matrices can be added elementwise.
# Matrix multiplication
Not every two matrices can be multiplied, for two matrices A and B to be multiplication compatible, the number of columns in A must be equal to the number of rows in B

The sizes shall be $A(p\times q)$ and $B(q\times r)$

The $(i, j)^{th}$ element of the product matrix is calculated as:
$$AB[i, j] = \sum_{k=1}^n A[i, k]\cdot B[k, j]$$
1. Matrix multiplication is not commutative.
2. Matrix multiplication is associative.

The algorithm to compute the product takes $O(n^3)$ time.
To compute the product of chains of matrices, an efficient algorithm can be formed using dynamic programming as mentioned in [[Matrix Chain Multiplication and the elements of Dynamic Programming]].
## Min-plus matrix multiplication
Min-plus product is another way to multiply two matrices.
The $(i, j)^{th}$ element of the Min-plus product of two matrices $A$ and $B$ is calculated as
$$AB[i,j] = \min_{k=1}^n\{A[i,k]+B[i,k]\}$$
## Identity matrix
The elements on the principal diagonal of an identity matrix are all 1 and the remaining elements are zero.
Any matrix remains unchanged when multiplied with the identity matrix.
# Matrix exponentiation
An efficient algorithm can be used to compute powers of a matrix in $O(n^3logk)$ time using dynamic programming with the following recurrent relation:
$$A^n=\begin{cases}I & n = 0\\A^{n/2}A^{n/2} & n\text{ is even}\\A^{n-1}A & n\text{ is odd}\end{cases}$$
# Determinant
Determinant of a square matrix can be recursively calculated using the formula
$$det(A) = \sum_{j=1}^nA[1,j]C[1,j]$$
where $C[1,j]$ is the cofactor of $A$ at the $(1,j)^{th}$ element, calculated recursively as:
$$C[i,j] = (-1)^{i+j}det(M[i, j])$$
where $M[i, j]$ is a matrix called the minor of $A$ at the position $(i, j)$ and is obtained by removing the $i^{th}$ row and $j^{th}$ column from $A$.

The determinant can be computed in $O(n^3)$ quickly using the [[Gauss method of determinant]] or the [[Kraut method of determinant]].
# Inverse of a matrix
The inverse of matrix exists only when its determinant is nonzero and the inverse's $(i, j)^{th}$ element can be calculated as
$$A^{-1}[i, j] = \frac{C[i, j]}{det(A)}$$
# Gauss-Jordan algorithm for solving system of linear equations using matrices
The coefficients of a system of linear equations can be represented in an augmented matrix.

This method is based on two transformations, that are swapping two rows and replacing a row with its linear combination with any other row.

[Gauss method for solving system of linear equations](https://cp-algorithms.com/linear_algebra/linear-system-gauss.html)
```psuedocode
h := 1 // Initialization of the pivot row
k := 1 // Initialization of the pivot column
while h ≤ m and k ≤ n
    // Find the k-th pivot
    i_max := argmax(i = h ... m, abs(A[i, k]))
    if A[i_max, k] = 0
        // No pivot in this column, pass to next column
        k := k + 1
    else
        swap rows(h, i_max)
        // Do for all rows below pivot
        for i = h + 1 ... m:
            f := A[i, k] / A[h, k]
            // Fill with zeros the lower part of pivot column
            A[i, k] := 0
            // Do for all remaining elements in current row
            for j = k + 1 ... n:
                A[i, j] := A[i, j] - A[h, j] * f
        // Increase pivot row and column
        h := h + 1
        k := k + 1
```
# Linear recurrences
A linear recurrence is a function f(n) which is calculated as a linear combinations of its past values.
$$f(n) = c_1f(n-1) + c_2f(n-2) + \dots + c_kf(n-k)$$
Dynamic programming can be used to calculated values of linear recurrences efficiently. However, linear recurrences can also be modelled using matrices efficiently for smaller n.

A linear recurrence matrix $X$ can be modelled in such a way that when a vector $\vec u$ of the form..
$$\vec u = \begin{bmatrix}f(k)\\f(k+1)\\f(k+2)\\\vdots\\f(n-1)\end{bmatrix}$$
is multiplied with $X$, the result i.e. $X\vec u$ is..
$$\vec u = \begin{bmatrix}f(k+1)\\f(k+2)\\f(k+3)\\\vdots\\f(n)\end{bmatrix}$$
which means $X$ shifts each of the linear recurrences up by one, i.e. after multiplication $f(k)$ is replaced by $f(k+1)$, $f(k+1)$ is replaced by $f(k+2)$ and so on, the last element of the result vector is the new value of $f(n)$ we have calculated.

Such a matrix $X$ that shifts up each value of linear recurrences by one can be constructed as..
$$X = \begin{bmatrix}0&1&0&0&\dots&0\\0&0&1&0&\dots&0\\0&0&0&1&\dots&0\\\vdots&\vdots&\vdots&\vdots&\ddots&\vdots\\0&0&0&0&0&1\\c_k&c_{k-1}&c_{k-2}&c_{k-3}&\dots&c_1\end{bmatrix}$$
The first k - 1 rows of this matrix are used to shift the first k - 1 elements of the input vector by one.

The last row of this matrix is used to calculated the last element of the result vector from the values of all the previous linear recurrences.

Powers of $X$ can be pre-calculated efficiently to calculate linear recurrences some k steps ahead. For example, multiplying $\vec u$ with $X^k$ will shift the values in $\vec u$ up by k.
## Modelling fibonacci linear recurrence using matrices
Fibonacci series is a linear recurrence of the form $f(n) = f(n-1)+f(n-2)$ with the base cases: $f(0) = 0$ and $f(1) = 1$.
Since the linear recurrence depends on values two steps before n. We have:
$\vec u = \begin{bmatrix}f(k)\\f(k+1)\end{bmatrix}$
The coefficients of $f(n-1)$ and $f(n-2)$ are 1, therefore the last row of $X$, which holds the coefficients will be $[1, 1]$
Finally $X$ becomes
$$X = \begin{bmatrix}0&1\\1&1\end{bmatrix}$$
Fibonacci numbers k steps ahead can be calculated by multiplying $\vec u$ with $X^k$
Starting from the zeroth and the first fibonacci number $\vec u_0 = \begin{bmatrix}0\\1\end{bmatrix}$ 
If we multiply $\vec u_0$ with $X^k$, the last element of the result vector will contain the $k^{th}$ fibonacci number.
# Adjacency matrices
A graph of $n$ vertices can be represented as an adjacency matrix of $n \times n$ where the $(i, j)^{th}$ element of the adjacency matrix is 1 if there is an edge between the $i^{th}$ and $j^{th}$ vertex. In weighted graphs, the $(i, j)^{th}$ element equals the weight of the edge.

The adjacency matrix representation of graphs have some properties which can be used to efficiently calculate some information about the graph.
## Paths of k edges in graph
Let $V$ be the adjacency matrix of a graph, then $V$ is non zero at all the edges of the graph. The edges are just paths of length 1 between two vertices. In other words, $V$ has nonzero elements at all the paths of length 1 between any two vertices in the graph.

Why did I say "edge" in such a weird way? I could have just said "edge", but I emphasized "paths of length 1 between two vertices if it exists". Believe me, calling edges as paths of length 1 takes us to great places with adjacency matrices because, brace yourselves, the nonzero elements of the $k^{th}$ integral power of adjacency matrix correspond to the paths of length k in a graph.

More formally, the nonzero elements of $V^k$ correspond to the paths of $k$ edges between any two vertices if such paths exist in the graph.
## Shortest paths in adjacency matrix
To calculate shortest paths between any two vertices of a weighted graph, we create a distance adjacency matrix where every element is infinity except the elements that correspond to the edges in the graph, the elements of the adjacency matrix corresponding to the edges contain the weight of the edge instead of infinity. If we call such an adjacency matrix $V$

We can find the shortest paths between two vertices if we calculate powers of $V$ using Min-plus product instead of the regular matrix multiplication.

The non-infinite elements of $k^{th}$ power of $V$ using Min-plus product give the shortest path of k edges if it exists between two vertices in the graph.
## Number of spanning trees, Kirchoff's theorem and Laplacian matrix
To calculate the number of spanning trees in a graph, we construct the Laplacean matrix $L$, where $L[i, i]$ is the degree of vertex $i$ and $L[i, j] = −1$ if there is an edge between vertices $i$ and $j$, and otherwise $L[i, j]= 0$.

Then Kirchoff's theorem states that if we remove any one column and any one row from the Laplacean matrix, and take the determinant $\Delta$ of the reduced matrix, then it can be shown that the number of spanning trees in the original graph is equal to the determinant $\Delta$.

> Cayley's formula is a special case of Kirchoff's theorem.
