import random

filename = "random_max.in"
random.seed(2615897)

n = 2*10**5

canisters = list()

for i in range(1,n+1):
    canisters.append(random.randint(int(2*i/3)+1,i))

fin = open(filename, "w")
fin.write(str(n)+"\n")
fin.write(' '.join(str(e) for e in canisters) + "\n")
