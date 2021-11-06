#!/usr/bin/python3

alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 "

n = int(input())
A = []
for r in range(n):
  A.append(list(map(int,input().split(' '))))
  
#print(n)
#print(A)

plain = list(input())

while len(plain) % n != 0:
  plain.append(' ')
  
for i in range(len(plain)):
  plain[i] = alphabet.index(plain[i])

#print(plain)

cipher = []

for i in range(0,len(plain),n):
  out = [0]*n

  for j in range(n):
    for k in range(n):
      out[j] += A[j][k] * plain[i+k]
    out[j] = alphabet[out[j] % 37]
    cipher.append(out[j])

print(''.join(cipher))

