#!/usr/bin/env python3

import matplotlib.pyplot

n_range = list(range(1, 71))
d = [1.0]

for n in n_range[1:]:
    d.append(d[-1] * (365.0 - n - 1) / 365.0)

matplotlib.pyplot.plot(n_range, d)
matplotlib.pyplot.grid(True)
matplotlib.pyplot.title('$D(n)$: probability of $n$ unique birthdays')
matplotlib.pyplot.xlabel('n')
matplotlib.pyplot.ylabel('D(n)')
matplotlib.pyplot.savefig('birthday_plot.png')
