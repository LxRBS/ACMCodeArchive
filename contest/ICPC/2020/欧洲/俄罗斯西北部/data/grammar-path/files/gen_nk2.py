from sys import argv

k = int(argv[1])
n = int(argv[2])

rules = []

alph = "S"
for i in range(k):
  c = chr(ord('A') + i)
  if c != 'S':
    alph += str(c)

for i in range(len(alph) - 1):
  rules.append((alph[i], alph[i + 1], alph[i + 1]))

rules.append((alph[-1], 'a', ''))


edges = []
for i in range(n):
  if i + 1 < n:
    edges.append((i, i + 1, 'a'))
    edges.append((i + 1, i, 'a'))
  edges.append((i, i, 'a'))

print(len(rules))
for x in rules:
  print(str(x[0]) + " -> " + str(x[1]) + str(x[2]))
print(str(n) + " " + str(len(edges)) + " " + "1" + " " + str(n))
for ed in edges:
  print(str(ed[0] + 1) + " " + str(ed[1] + 1) + " " + str(ed[2]))

