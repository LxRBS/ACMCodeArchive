#!/usr/bin/python3

import random

inverses = [0,1,19,25,28,15,31,16,14,33,26,27,34,20,8,5,7,24,35,2,13,30,32,29,17,3,10,11,4,23,21,6,22,9,12,18,36]

def generateInvertibleMatrix(n):
  m = []
  m2 = []
  for i in range(n):
    m.append([])
    m2.append([])
    for j in range(n):
      a = random.randrange(0,37)
      m[i].append(a)
      m2[i].append(a)
    for j in range(n):
      if i == j:
        m2[i].append(1)
      else:
        m2[i].append(0)

#  print(m2)

  for r in range(n):
    # find row with non-zero entry in column r
    found = False
    for r2 in range(r,n):
      if m2[r2][r] != 0 and not found:
        # swap row r with row r2... they might be the same
        found = True
        for c in range(2*n):
          tmp = m2[r][c]
          m2[r][c] = m2[r2][c]
          m2[r2][c] = tmp

#    print(m2[r])

    # if not found, not invertible
    if not found:
      print("Not invertible!")
      return None

    # scale row r so column r == 1
    a = inverses[m2[r][r]]
    for c in range(2*n):
      m2[r][c] = (m2[r][c] * a) % 37;

#    print(m2[r])

    # add scaled row to all other rows to zero out column r
    for r2 in range(n):
      if r2 != r:
        a = m2[r2][r]
        for c in range(2*n):
          m2[r2][c] = (m2[r2][c] + 37 - (a * m2[r][c]) % 37) % 37

#  print(m2)

  m3 = []
  m4 = []
  for r in range(n):
    m3.append([])
    m4.append([])
    for c in range(n):
      m3[r].append(m2[r][c+n])
      m4[r].append(0)

  for r in range(n):
    for c in range(n):
      for k in range(n):
        m4[r][c] = (m4[r][c] + m[r][k] * m3[k][c]) % 37

  print(m4)

  return m

plains = [
  "TWO PENGUINS WALK INTO A BAR OW OW",
  "BONO AND THE EDGE WALK INTO A BAR THE BARTENDER SAYS OH NO NOT U2 AGAIN",
  "MY HOVERCRAFT IS FULL OF EELS",
  "3 POINT 141592653589793238462643383279 0ZYXWVUTSRQPONMLKJIHGFEDCBA",
  "GET THE COOL SHOESHINE",
]

print(plains)

for i in range(1,37):
  if (i * inverses[i]) % 37 != 1:
    print("Bad inverse")

fnum = 1

for n in range(1,11):
  for plain in plains:

    A = None
    while A is None:
      A = generateInvertibleMatrix(n)

    # open file
    fname = '{:03}.in'.format(fnum)
    print(fname)

    f = open(fname,"w")

    # output n
    f.write(str(n))
    f.write('\n')

    # output A
    for r in A:
      f.write(str(r[0]))
      for i in range(1,n):
        f.write(' ')
        f.write(str(r[i]))
      f.write('\n')

    # output plain
    f.write(plain)
    f.write('\n')

    # close file
    f.close()

    fnum += 1
