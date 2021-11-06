import random
import numpy as np

filename = "random_impossible.in"
random.seed(2615897)

n = random.randint(1000, 2*10**5)

canisters = np.random.permutation(range(1, n+1))
canisters[random.randint(100,n-100)] += 1

fin = open(filename, "w")
fin.write(str(n)+"\n")
fin.write(' '.join(str(e) for e in canisters) + "\n")
