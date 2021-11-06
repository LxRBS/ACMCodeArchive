import random

filename = "random.in"
random.seed(2615897)

n = random.randint(1, 2*10**5)

canisters = list()

for i in range(1,n+1):
    canisters.append(random.randint(1,i))

fin = open(filename, "w")
fin.write(str(n)+"\n")
fin.write(' '.join(str(e) for e in canisters) + "\n")
