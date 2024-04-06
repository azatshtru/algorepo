#Minimizing sums

Consider the expression of the form:
$$|a_1-x|^c+|a_2-x|^c+\dots+|a_n-x|^c
The goal is to minimize the above expression at some c and x.

-For c = 1, the optimal strategy is to take x as the median of $a_1, a_2\dots a_n$ arranged in ascending order.
-For c = 2, the optimal strategy is to take x as the mean of $a_1, a_2\dots a_n$.

$$|a_1-x|^2+|a_2-x|^2+\dots+|a_n-x|^2$$
Expanding the above, we get:
$$x^2 + 2x(a_1+a_2+\dots+a_n) + (a_1+a_2+\dots+a_n)^2$$

The last term doesn't depend on x and can be ignored, the remaining sum $x^2 + 2xs$ where $x=(a_1+a_2+\dots+a_n)$ is a parabola which has zeroes $0$ and $2s/n$.
The minima of a parabola is the average of roots, i.e. $\frac{0+2s/n}{2} = \fracsn$