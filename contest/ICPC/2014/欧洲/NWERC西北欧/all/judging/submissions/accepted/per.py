import itertools
import sys
def read(N):
    return dict((k, len(list(v))) for (k,v) in itertools.groupby(sorted([sys.stdin.readline() for i in range(N)])))

N = int(sys.stdin.readline())
K = read(N)
res = 0
for (j, c) in read(N).iteritems():
    res += min(c, K.get(j, 0))
print res
