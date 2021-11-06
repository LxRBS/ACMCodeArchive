# this generator constructs input files where no merges occur
import random

N = 10**5
MIN_STEP = 0
MAX_STEP = 50

MIN_VAL = 1
MAX_VAL = 10**6

RANDOM_OFFSET = 500

def get():
    erg = []
    mv = 0
    s = 0
    for i in range(N):
        s += random.randint(MIN_STEP, MAX_STEP)
        p = s + random.randint(-RANDOM_OFFSET, RANDOM_OFFSET)
        p = max(0, p)
        erg.append(p)
        mv = max(mv, p)
    return map(lambda x: MIN_VAL + x * (MAX_VAL - MIN_VAL) // mv, erg)

print(N)
for x, y in zip(get(), get()):
    print("{} {}".format(x, y))
