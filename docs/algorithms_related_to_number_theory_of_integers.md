# Algorithms related to number theory of integers

# Primes and Factors

A number is called a factor of another number if it divides the other number completely.
A number is called prime if the only factors it has are 1 and itself.

---

## Factorization of a number

Every number has a prime factorization where it can be written as the product of prime numbers.
$$n=p_1^{a_1}p_2^{a_2}\dots p_n^{a_n}$$
Each factor of the number can be written as the product of some subset of its prime factors.

### Number of factors

Number of factors of a number is $\tau(n)$, where
$$\tau(n)=\prod(a_i+1)$$
This is because there are $a_i+1$ ways to choose how many times each prime factor appears for constructing a factor.

### Sum of factors

The sum of factors is $\sigma(n)$, where
$$\sigma(n)=\prod(1+p_i+p_i^2+\dots+p_i^{a_i})=\prod\frac{p_i^{a_i+1}-1}{p_i-1}$$

### Product of factors

The product of factors is $\mu(n)$, where
$$\mu(n)=n^{\tau(n)/2}$$
This is because there are n/2 pairs of factors whose product is 84

### Perfect number

A number $n$ is called a perfect number if $n=\sigma(n)-n$, for example: 28.

---

## Number of Primes

There are infinite number of prime numbers.
**PROOF**: Consider all the prime numbers in a set, if all of them are multiplied and 1 is added to the product, we get a unique prime.

## Density of Primes

Let $\pi(n)$ denote the number of primes between 1 to n, then
$$\pi(n)\approx\frac{n}{ln(n)}$$

## Conjectures related to number of primes

### Goldbach's conjecture
Each even integer greater than 2 can be represented as a sum of two primes.

### Twin prime conjecture
There are infinite number of pairs of the form (p, p+2) where p and p+2 are both primes.

### Legendre's conjecture
There is always a prime number between $n^2$ and $(n+1)^2$

---

## Checking if a number is prime
If a number is not prime, then it can be represented as a product $ab$ where $a < \sqrt n$ or $b < \sqrt n$, which means it always has a factor between $2$ and $\sqrt n$
We can run a loop sqrt(n) times and check if the any of the numbers between 2 and sqrt(n) divide n, effectively checking the prime in $O(\sqrt n)$

## Finding prime factors of a number
To find the prime factors of a number, we can run a loop sqrt(n) times, and whenever we find a prime factor of n, we repeatedly divide n by that prime factor and add that factor in the return list until that prime factor cannot divide n anymore, then we increment the loop and repeat the same.

## Sieve of Eratosthenes
This builds a preprocessing array where values at all the prime number indices are zero, and values at non-prime indices have any one prime factor of that non-prime index. We run a $O(n)$ algorithm that iterates through each natural number one by one, and at each iteration we check if the current number x is a prime, if it is, we set the values at 2x, 3x, 4x, ..., nx indices of the preprocessing array to x.

This algorithm runs in $O(nlog(logn))$ time.

## Euclid's greatest common divisor algorithm
The algorithm is based on the following formula:
$$gcd(a, b) = \begin{cases} a & b = 0\\gcd(b a \text{mod} b) & b \neq 0\end{cases}$$

For example, gcd(24,36) = gcd(36,24) = gcd(24,12) = gcd(12,0) = 12

## Euler's totient function

Two numbers a and b are coprime if gcd(a, b) = 1. Euler's totient function $\phi(n)$ gives the number of coprimes of n between 1 and n.
$$\phi(n)=\prod p_i^{a_i-1}(p_i-1)$$

If some number n is prime, then it is coprime with every number before it, hence:
$$\phi(n)=n-1$$

---
# Modular Arithmetic

## Some identities related to modular arithmetic

$$(x+y) \mod m = ((x \mod m)+(y \mod m)) \mod m$$
$$(x-y) \mod m = ((x \mod m)-(y \mod m)) \mod m$$
$$(xy) \mod m = ((x \mod m)(y \mod m)) \mod m$$
$$x^n \mod m = (x \mod m)^n \mod m$$

## modular exponentiation
The value of $x^n \text{mod} m$ can be calculated in $O(logn)$ time using the following recursion:
$$x^n=\begin{cases}1 & n = 0\\x^{n/2}x^{n/2} & n\text{ is even}\\x^{n-1}x & n\text{ is odd}\end{cases}$$
n is always halved when it is even leading to a O(logn) time complexity.

## Euler's modulo theorem
If two numbers x and m are coprime, then
$$x^{\phi(m)} \mod m = 1$$

### Fermat's modulo theorem

Fermat's theorem follows from Euler's theorem using the fact that $\phi(n)$ can be $n-1$ if n is prime.

If m is prime and m and x are coprime, then:
$$x^{m-1} \mod m = 1$$
Also:
$$x^k \mod m = x^{k \mod (m-1) \mod m}$$

## Modular inverse

The modular inverse of a number x is a number y such that $xy \mod m = 1$. A modular inverse only exists if both numbers are coprime.

Using Euler's modulo theorem, an expression for calculating the inverse can be derived.

We know that..
$$xx^{-1}\mod m = 1 \space  (1)$$
and..
$$x^{\phi(m)} \mod m = 1$$
or..
$$xx^{\phi(m)-1} \mod m = 1 \space  (2)$$
Comparing this with the first statement..
$$x^{-1}=x^{\phi(m)-1}$$
If m is prime, then..
$$x^{-1}=x^{m-2}$$

# Chinese Remainder Theorem

A set of equations of the form:
$$x=a_1\mod m_1$$
$$x=a_2\mod m_2$$
$$\dots$$
$$x=a_n\mod m_n$$
where $m_1,m_2\dots m_n$ are coprime can be solved using the Chinese Remainder theorem.

Let $X_k=\frac{m_1m_2\dots m_n}{m_k}$
And its inverse with respect to some $m_k$ is $X^{-1}_{k_{m_k}}$

Using the notation above,
$$x = a_1X_1X^{-1}_{1_{m_1}} + a_2X_2X^{-1}_{2_{m_2}} + \dots + a_nX_nX^{-1}_{n_{m_n}}  \space  (1)$$

**PROOF** We know that $X_kX^{-1}_{k_{m_k}}\mod m_k = 1$,
$a_kX_kX^{-1}_{k_{m_k}}\mod m_k = a_k$
If we calculate the modulo of x w.r.t. some $m_k$ in statement $(1)$ above, all other terms but the kth one will become zero since they contain $m_k$ and the kth term will become $a_k$.

If we have a solution $x$, all other solutions can be found as $x+m_1+m_2+\dots+m_n$

---
# Diophantine equations

Diophantine equations are of the form ax+by=c.
They can be solved if c is divisible by gcd(a, b).

Using euclid's algorithm, the solutions to Diophantine equations can be easily derived.
A solution for diophantine equation exists if and only if c is divisible by gcd(a, b).
Then we can write ax+by = gcd(a, b) and solve for x and y by going through Euclid's algorithm for gcd in reverse.
After than we can multiply the equation by constants to derive the values in the original equation.

If one set of solution in known, the others can be derived using the relations:
$$x_k=x+\frac{kb}{gcd(a,b)}$$
$$x_k=y-\frac{ka}{gcd(a,b)}$$

---
# Lagrange's Theorem
Each positive number can be represented a unique combination of squares of four integers.

# Zeckendorf's Theorem
Each positive number can be represented a combination of four non-consecutive unique fibonacci numbers.

# Pythagorean Triplets
The sides of a right angled triangle in an ordered pair of three is called a pythagorean triplet.
They can be easily found using Euclid's formula for pythagorean triplets.
$$(n^2-m^2, 2nm, n^2+m^2)$$
where $0<m<n$

If (a, b, c) is a pythagorean triplet, then (ka, kb, kc) is also a pythagorean triplet.

# Wilson's Theorem
A number n is prime exactly when
(n-1)! mod n = n - 1
