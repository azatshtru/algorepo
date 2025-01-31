# Bit Manipulation cheat sheet

1. Even-odd check can be performed by $x\&1$, in particular $x\&(2^k-1)$ is divisibility check for the $k^{th}$ power of 2.
2. $\~x$ is bit inversion, equivalent to $-x-1$
3. $x<<k$ corresponds to multiplying $x$ by $2^k$, $x>>k$ corresponds to dividing by $2^k$.
4. $x|(1<<k)$ sets the $k^{th}$ bit to one.
5. $x\&~(1<<k)$ sets the $k^{th}$ bit to zero.
6. $x\^(1<<k)$ inverts the $k^{th}$ bit.
7. $x\&(x-1)$ sets the last one bit to zero.
8. $x\&-x$ sets all bits to zero except the last one bit.
9. $x|(x-1)$ inverts all the bits after the last one bit.
10. A positive number is a power of two exactly when $x\&(x-1)$ is zero.


##[Bit twiddling hacks](https://graphics.stanford.edu/~seander/bithacks.html#CountBitsSetNaive)
1. to swap two values without using a temporary variable, do:
>```
>a=a^b
>b=a^b
>a=a^b
>```

2. Carmack's fast inverse square root
>1. Evil bit hacking
>2. What the fuck?
>3. Newton iteration

3. f_randi

4. If a number is power of two, then modulo is same as bitwise &


