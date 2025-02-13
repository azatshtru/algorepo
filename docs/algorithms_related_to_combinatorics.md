Combinatorics studies methods for counting combinations of objects.
# Combinatorial problems as recurrent relations
Combinatorial problems usually find combinations of larger set of objects from combinations of smaller sets of objects, effectively making it recursive.

The number of ways to represent the sum of an integer, say n.
For example, there 8 ways to represent the sum of 4..
- 1 + 1 + 1 + 1
- 2 + 2
- 1 + 1 + 2
- 3 + 1
- 1 + 2 + 1
- 1 + 3
- 2 + 1 + 1
- 4

The number $n$ can be represented as the sum $k + (n - k)$
To make n, we need to sum all the ways to make k, and all the ways to make (n-k)
Therefore, to make n, we need to find all the ways to make k and n-k for all k < n.

This can be modelled as a recurrent relation..
$$f(n) = \begin{cases} 1 & n = 0\\\sum_{x=0}^{n-1}f(x) & n > 0 \end{cases}$$
With enough algebraic manipulation and noticing patterns among the recurrent relation's value/output, we can find a _closed-form formula_ for the recurrent relation.

For the above example with n = 4, the values of the recurrent function are..
- f(0) = 1
- f(1) = 1
- f(2) = 2
- f(3) = 4
- f(4) = 8

It can be conjectured that the number of ways to make the sum n is $2^{n-1}$
This conjecture can be proved as follows,
1 + 1 + 1 + ... + 1 = n
The number of plus(+) signs in the above sum is n - 1
A plus sign can be removed by replacing a `1 + 1` with `2`
Any plus sign can be removed by replacing itself and its left and right operands by their sum.
There are n - 1 plus signs, and we have two choices for each of them: to remove, or not to remove.

For the two choices of the first plus sign, we have 2 choices for the next plus sign, giving us 4 possible combinations..
chosen      chosen
chosen      not-chosen
not-chosen  chosen
not-chosen  not-chosen

Similarly, for n - 1 combinations we have $2 \times 2 \times 2 \times ... \times 2 = 2^{n-1}$ choices.
Since each unique combination of removing/keeping plus signs corresponds to a unique sum for n, we can say:
$$f(n) = 2^{n-1}$$
# Binomial coefficient
The binomial coefficients correspond to the coefficients of the terms in a binomial expansion and to the numbers in the Pascal's triangle.

The binomial coefficient denotes the number of ways of choosing k objects from a set of n objects, Like the number of ways $a^kb^{n-k}$ appears in the binomial expansion of $(a + b)^n$
The binomial coefficient is written as $n \choose k$, pronounced "n choose k" for all $0 \leq k \leq n$.
## recursive method to calculate binomial coefficients
We can select some object "x" from the set of n, then there will be k-1 objects remaining for us to select and there will be n-1 objects left in the set. In this case the remaining problem is to select k-1 objects from n-1 objects, i.e. ${n - 1 \choose k - 1}$

If we decide to not select "x" and ignore it, then there will be k objects still remaining for us to select and n - 1 objects left in the entire set since we are ignoring one. Hence the remaining problem is ${n - 1\choose k}$

Hence, we can either pick and object or ignore it, in each case we will have to solve the respective remaining problems. The sum of the combinations in the remaining problems is equal to the total possible combinations.
$${n\choose k} = {n - 1 \choose k - 1} + {n - 1 \choose k}$$
## permutative method to calculate binomial coefficients
There are n! permutations of n elements. We go through all permutations and always include the first k elements of the permutation in the subset. Since the order of the elements in the subset and outside the subset does not matter, n! is divided by k! and (n− k)! giving..
$${n \choose k} = \frac{n!}{k!(n-k)!}$$
## some properties of binomial coefficients (without proof)
1. $${n \choose k} = {n \choose n - k}$$
2. $${n\choose 0}+{n\choose 1}+\dots+{n\choose n} = 2^n$$
# boxes and balls
> or stars and bars or sticks and stones or dots and dividers
## no two balls overlap
Given n boxes and k balls, find out how many ways are there to place the balls in boxes such that no two balls are in the same box.
This is the problem of choosing k boxes to place the balls from total n boxes, i.e. $n \choose k$
## balls can overlap
If a box can contain multiple balls, then the problem can be visualized as a placing operation. The character 'o' represents the operation of placing a ball, the character '->' represents the operation of moving to the next box.

For example, if n = 5 and k = 2, the following sequence of operations..
"-> -> o -> o ->” represents starting from the first box, then leaving the first two boxes empty, then placing the ball in the third box, then moving to the fourth box, then placing the ball in the fourth box, then moving to the fifth box. i.e. a setup like this: `_ _ x x _`

Starting from the first box, we can move to n - 1 more boxes, this means that there will be n - 1 arrows in the placing operation string, and since we can place k balls, there will always be k 'o's in the operation string.

Given a string of length `n - 1 + k`, we can fill it with `n - 1` arrows and `k` 'o's.
This boils down to a problem of choosing `k` places from `n - 1 + k` places..
$$n - 1 + k \choose k$$
## no two adjacent boxes can have balls and no two balls can overlap
We have k fixed boxes with balls in them, initially kept adjacent. Then, we can insert a box between these k boxes so that no two adjacent boxes have balls in them. Doing this will require k - 1 more boxes. In total we have used $k + (k - 1) = 2k - 1$ boxes.
The remaining boxes are $n - (2k - 1)$.

Since $2k - 1$ boxes are fixed, the number of ways to place remaining boxes will give the required result.

There are n - 1 spaces between the boxes with balls for the remaining boxes to be placed, there are two more spaces, extreme left and extreme right. In total there are n + 1 spaces for the remaining $n - 2k + 1$ boxes to be placed.

We can use the strategy in the previous section to place these boxes..
'->' represent moving to the next place where it is possible to place the box
'+' represents placing a box.
Since there are k + 1 possible places for the remaining box to be placed, there will be $k + 1 - 1 = k$ arrows, and since there are $n - 2k + 1$ remaining boxes, there will be $n - 2k + 1$ plus signs in the final operation string.
In total the operation string will have $k + 1 - 1 + n - 2k + 1 = n - k + 1$ characters.
From these characters, we have to choose $n - 2k + 1$ character to put a '+' sign, i.e. the remaining boxes.
$$n - k + 1\choose n - 2k + 1$$
# multinomial coefficients
The multinomial coefficient equals the number of ways we can divide n elements into subsets of sizes $k_1,k_2,...,k_m$, where $k_1 + k_2 + · · · + k_m = n$
$${n \choose k_1,k_2,...,k_m} = \frac{n!}{k_1!k_2!· · · k_m!}$$
# Catalan numbers
A catalan number represents the "valid" parentheses combinations using n opening and n closing parentheses. Represented as $C_n$

For example, $C_3 = 5$ because using 3 opening and 3 closing parentheses, we can have 5 possible valid arrangements..
- ()()()
- (())()
- ()(())
- ((()))
- (()())

A valid combination follows three rules:
- An empty parenthesis expression is valid.
- If an expression `A` is valid, then also the expression `(A)` is valid.
- If expressions `A` and `B` are valid, then also the expression `AB` is valid.
## recursive method to calculate catalan numbers
This can be formulated recursively as discussed in the first section because smaller valid parentheses expressions can be combined to create larger expressions.
$$C_n = \sum_{i=0}^{n-1}C_iC_{n-i-1}$$
- $C_i$ is the number of ways to construct the left part of the expression while excluding the outermost parentheses
- $C_{n-i-1}$ is the number of ways to construct the right part of the expression.
- $C_0 = 1$ is the base case.
## using binomial coefficients to calculate catalan numbers
There are $2n \choose n$ ways to choose n places to put a '(' in a string of size 2n, the remaining places will be filled with ')'. However doing this can give some invalid strings like: ")((()(", this has equal amounts of '(' and ')', but is invalid.

The idea is to reverse each parenthesis that belongs to such a prefix. For example, the expression ())()( contains a prefix ()), and after reversing the prefix, the expression becomes )((()(. The resulting expression consists of n+1 left parentheses and n−1 right parentheses. The number of such expressions is $2n \choose n+1$

The number of valid expressions can be calculated by subtracting invalid ones from the total ones..
$$C_n = {2n \choose n} - {2n \choose n+1}$$
After some diligent algebraic manipulation we get..
$$C_n = \frac{1}{n+1}{2n\choose n}$$
## numbers of binary trees
- there are $C_n$ binary trees of n nodes
- there are $C_{n−1}$ rooted trees of n nodes

For example, for $C_3 = 5$, the binary trees are
```
binary trees
  o
 / \
o   o

    o
   /
  o
 /
o 


    o
   /
  o
   \
    o 

o
 \
  o
 /
o 

o
 \
  o
   \
    o 

```
and the rooted binary trees are
```
  o
 /|\
o o o

   o
   |
   o
   | 
   o 
   |
   o


  o
 / \
o   o
|
o

  o
 / \
o   o
    |
    o

  o
  |
  o
 / \
o   o

```
# Inclusion/Exclusion
The size of the union $X_1 ∪ X_2 ∪ · · · ∪ X_n$ can be calculated by going through all possible intersections that contain some combinations of the sets $X_1, ... , X_n$
If the intersection contains an odd number of sets, its size is added to the answer, and otherwise its size is subtracted from the answer.

For example, the size of union of three sets A, B and C..
$|A ∪ B ∪ C| = |A| + |B| + |C| − |A ∩ B| − |A ∩ C| − |B ∩ C| + |A ∩ B ∩ C|$
Intersections $A, B, C, A\cap B\cap C$ contain odd number of sets, hence they are added.
Intersections $A\cap B, A\cap C, B\cap C$ contain even number of sets, hence they are subtracted from the answer.

Similar relations can be used to calculate size of intersection of some sets.
$|A ∩ B ∩ C| = |A| + |B| + |C| − |A ∪ B| − |A ∪ C| − |B ∪ C| + |A ∪ B ∪ C|$
Unions $A, B, C, A\cup B\cup C$ contain odd number of sets, hence they are added.
Unions $A\cup B, A\cup C, B\cup C$ contain even number of sets, hence they are subtracted from the answer.
# Derangements
A derangement of an array is another array where no element remains at its original place.

For example, `[3, 1, 2]` is a derangement of `[1, 2, 3]`. But `[3, 2, 1]` is not a derangement because `2` is in its original place.
## calculating number of derangements using inclusion-exclusion.
Let $X_k$ be the set of permutations that contain the element k at position k.
For example, when n = 3, the sets are as follows:
$X_1$ = {(1,2,3),(1,3,2)}
$X_2$ = {(1,2,3),(3,2,1)}
$X_3$ = {(1,2,3),(2,1,3)}

Using these sets, the number of derangements equals $n!− |X1 ∪ X2 ∪ · · · ∪ Xn|$
It suffices to calculate the size of the union. Using inclusion-exclusion, this reduces to calculating sizes of intersections which can be done efficiently.
$$!n=n!⋅(1−1/1!​+1/2!​−1/3!​+⋯+(−1)^n/n!​)$$
## calculating number of derangements using recurrent relation
After removing element 1, there are n-1 ways to choose another element x that is kept at the position of element 1 in the derangement. Two things can happen:
1. The other chosen element x is also placed at element 1's position, in which case both element 1 and element x are deranged, therefore we now need to find derangements for the remaining n-2 elements.
2. No other element is placed at element x's position, in this case we need to find derangements of remaining n - 1 elements such that no element is placed on the current position of element 1.

$$f(n) = \begin{cases}0 & n = 1\\1 & n = 2\\(n-1)(f(n-2)+f(n-1)) & n > 2\end{cases}$$
# Burnside's Lemma
> and some necklaces with beads and colors

If there is a subset of combinations such that each combination in the subset can be obtained by manipulating any other combination from the same subset according to some given set of manipulations, then the combinations in the subset are said to be **symmetric** to each other.

For example, if there is a necklace with n beads, the beads can have any color from a set of some m colors..
```
This is a necklace with 4 beads, and 3 possible colors: r, g, b, i.e. n=4 and m=3, then one of the combinations is..
  r
 / \
g   b
 \ /
  r
other combinations with r, g, b and 4 beads are..
  g
 / \
r   r
 \ /
  b
  r
 / \
b   r
 \ /
  r
  b
 / \
r   r
 \ /
  g
```
Each of the four necklaces given above can be obtained by rotating any of the other necklace from above clockwise a few times.
If we define a set of manipulations with 4 ways to manipulate:
1. rotate clockwise once
2. rotate clockwise twice
3. rotate clockwise thrice
4. rotate clockwise four-times

according to these manipulations, the four necklaces above are symmetric to each other because each of them can be obtained from the any other using any one of the manipulations given above.

Burnside's Lemma is used to count the number of combinations such that only one combination is counted for a subset of symmetric combinations.
$$\sum_{k=1}^n\frac{c(k)}{n}$$
$n$ is the number of ways to manipulate the combination according to the given rule. 
- For example, a necklace can be rotated n=4 times before it reaches its original position, therefore there are n=4 ways to manipulate the combination: rotating it once, rotating it twice, thrice and four times.

c(k) is the number of possible combinations that remain unchanged when the kth manipulation according to the rule is applied.
- For example, if we take the 2nd way of manipulation in the necklace, i.e. rotating it twice, then the number of possible combinations of the necklace that would remain unchanged after rotating it twice would be $3^2$ (explained next)

With 3 colors and 4 beads, there are total $3^4$ possible necklaces because there are 4 beads and 3 possible colors for each bead. For n beads and m colors, there are $m^n$ possible necklaces.

If we use the second way of manipulation, i.e. rotating the necklace twice, then there would be a subset of necklaces from the total possible necklaces that would remain unchanged. How many necklaces with 4 beads and 3 possible colors are there that will remain unchanged upon rotating it twice?

`_ _ _ _`
There are 3 choices of colors for the first bead of such a necklace. After rotating twice, the 3rd bead of the necklace would be at the first bead's position, therefore the 3rd bead should have the same color as the first bead, hence we only have one choice for the third bead because we fix it according to the first bead..
`3 _ 1 _`
For the second bead, we have 3 choices of colors, but this would fix the fourth bead using the same logice as before, we have..
`3 3 1 1`

$3\times3\times1\times1=3^2=9$

Therefore there are $3^2$ necklaces that would remain unchanged when rotating twice clockwise given 3 colors and 4 beads.

In fact, once we fix some beads, the choices for colors of other beads are automatically fixed according to the number of clockwise rotations.

When we fix a bead for some number of rotations k, the bead that is k positions before the current bead replaces the current bead after rotation, and the current bead replaces the bead that is is k positions after it.

Riding on this chain of thought, we can derive that if we fix initial $\gcd(k, n)$ adjacent beads, then remaining beads will be fixed according to these initial beads, and we will have $\frac{n}{\gcd(k, n)}$ groups of adjacent beads and these groups will replace each other without conflicts when rotation is performed k times.

Since we have $m$ choices for for $\gcd(k, n)$ beads and the remaining will be fixed according to them, in total we can construct $m^{\gcd(k, n)}$ necklaces that would remain unchanged after rotating the necklace k times.

Or in the language of Burnside's lemma, there would be $c(k) = m^{\gcd(k, n)}$ possible necklaces that would remain unchanged when we apply the kth manipulation on them.

To only represent one element from the set of symmetric necklaces, we will divide by n and add the elements for each k.
$$\sum_{k=0}^{n-1}\frac{m^{\gcd(k, n)}}{n}$$
# Cayley's formula
There are $n^{n-2}$ labeled trees that contain n nodes.
Two labelled trees are different if their structure is different or labelling is different.
For example, there are $4^{4-2}=16$ labelled trees for $n=4$
```
  1
 /|\
2 3 4

  2
 /|\
1 3 4

  3
 /|\
1 2 4

  4
 /|\
1 2 3

1-2-3-4

1-2-4-3

1-3-2-4

1-3-4-2

1-4-2-3

1-4-3-2

2-1-3-4

2-1-4-3

2-3-1-4

2-4-1-3

3-1-2-4

3-2-1-4
```
## Prüfer code
The Prüfer code for a tree is constructed by following a process that removes n−2 leaves from the tree.
At each step, the leaf with the smallest label is removed, and the label of its only neighbor is added to the code.
```
For example,
1 2-5
 \|
3-4

This tree can also be represented as:
     2
    / \
   4   5
  / \
 1   3
```
Leaf with smallest key is 1, so it is removed and its only neighbor, 4 is added to the code, the code becomes `[4]`, the tree becomes..
```
     2
    / \
   4   5
    \
     3
```
The next leaf with the smallest key is 3, it is removed from the tree, and its neighbor, 4 is added to the code. The code becomes `[4, 4]` and the tree becomes..
```
     2
    / \
   4   5
```
The next leaf with smallest key is 4, it is removed and the neighbor, 2 is added to the code, the code becomes: `[4, 4, 2]`, and the tree..
```
    2
     \
      5
```
We have removed n-2 nodes from the tree, therefore we stop here.

Importantly, the original tree can be constructed uniquely from a Prüfer code.

A Prüfer code looks like this `[_, _, _, _, ...]` There are n-2 elements in a Prüfer code. For each of the n-2 positions, there can be any number from 1 to n, i.e. there can be total $n^{n-2}$ unique Prüfer codes of length n-2. Since each labelled tree generates a unique Prüfer code, each Prüfer code corresponds to a unique labelled tree. Hence, there are $n^{n-2}$ unique labelled trees, each corresponding to a unique Prüfer code.

