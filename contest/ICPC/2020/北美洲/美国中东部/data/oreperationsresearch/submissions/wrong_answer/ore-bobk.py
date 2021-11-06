#!/usr/bin/python3

#
# f(c,a,b) = 1, if c == len(C)
#            f(c+1,(a+1)%len(A),b), if C[c] == A[a]
#            f(c+1,a,(b+1)%len(B)), if C[c] == B[b]
#            f(c+1,(a+1)%len(A),(b+1)%len(B)), if C[c] == A[a] + B[b]
#            0, otherwise

(nA,nB,nC) = map(int,input().split(' '))
A = list(map(int,input().split(' ')))
B = list(map(int,input().split(' ')))
C = list(map(int,input().split(' ')))

answer = "yes"

a = 0
b = 0
for c in range(nC):
  if C[c] == A[a]:
    a = (a + 1) % nA
  elif C[c] == B[b]:
    b = (b + 1) % nB
  elif C[c] == A[a] + B[b]:
    a = (a + 1) % nA
    b = (b + 1) % nB
  else:
    answer = "no"
    
print(answer)

