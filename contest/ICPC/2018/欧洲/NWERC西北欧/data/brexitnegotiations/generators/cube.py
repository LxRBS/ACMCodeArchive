import random

filename1 = "cube_random_weights.in"
filename2 = "cube_subset_random_weights.in"

random.seed(521849)

k=10
n = 2**k

dependencies1 = list()
dependencies2 = list()

for i in range(0,n):
	prev1 = list()
	prev2 = list()
	for j in range(0,k):
		if i&2**j:
			prev1.append(i-2**j)
			if random.randint(1,3)==1:
				prev2.append(i-2**j)
	dependencies1.append(prev1)
	dependencies2.append(prev2)

with open(filename1, 'w') as fin1, open(filename2, 'w') as fin2:
	fin1.write(str(n)+"\n")
	fin2.write(str(n)+"\n")
	for i in range(0,n):
		fin1.write(str(random.randint(1,10**4)) + " " + str(len(dependencies1[i])))
		fin2.write(str(random.randint(1,10**4)) + " " + str(len(dependencies2[i])))
		if len(dependencies1[i]) > 0:
			fin1.write(" " + ' '.join(str(e) for e in dependencies1[i]))
		if len(dependencies2[i]) > 0:
			fin2.write(" " + ' '.join(str(e) for e in dependencies2[i]))
		fin1.write("\n")
		fin2.write("\n")
