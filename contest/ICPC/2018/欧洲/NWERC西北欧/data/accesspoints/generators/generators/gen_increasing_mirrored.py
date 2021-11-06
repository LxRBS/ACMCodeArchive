# this generator constructs input files where no merges occur
import random

N = 10**5
MIN_STEP = 0
MAX_STEP = 10

MIN_VAL = 1
MAX_VAL = 10**6

SUBSEQ = 20

def get():
    erg = []
    s = 0
    for i in range(0, N, SUBSEQ):
        cur = []
        for j in range(SUBSEQ):
            s += random.randint(MIN_STEP, MAX_STEP)
            cur.append(s)
        cur = cur[::-1]
        erg.extend(cur)
    return map(lambda x: MIN_VAL + x * (MAX_VAL - MIN_VAL) // s, erg)

print(N)
for x, y in zip(get(), get()):
    print("{} {}".format(x, y))
