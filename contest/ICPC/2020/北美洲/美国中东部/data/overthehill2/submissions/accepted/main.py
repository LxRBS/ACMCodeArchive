#!/usr/bin/python3

alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 "

inverses = [0, 1, 19, 25, 28, 15, 31, 16, 14, 33, 26, 27, 34, 20, 8, 5, 7, 24, 35, 2, 13, 30, 32, 29, 17, 3, 10, 11, 4,
            23, 21, 6, 22, 9, 12, 18, 36]

debug = False


def encrypt():
    global nSolutions

    cTest = []
    for r in range(0, len(plain), n):
        out = [0] * n
        for jj in range(n):
            for k in range(n):
                out[jj] += ans[jj][k] * plain[r + k]
            cTest.append(out[jj] % 37)
    for r in range(len(cipher)):
        if cTest[r] != cipher[r]:
            nSolutions = 0


def findMatrix():
    global nSolutions

    T = []

    # slice the plaintext array
    P = []
    C = []
    for i in range(n):
        C.append([])
    for i in range(0, len(plain), n):
        P.append(plain[i:i+n])
        for j in range(n):
            C[j].append(cipher[i+j])

    if debug:
        print('P:', P)
        print('C:', C)

    # try to find a solution for all rows
    for row in range(n):
        # make a copy of P
        A = []
        for r in range(len(P)):
            A.append([])
            for c in range(n):
                A[r].append(P[r][c])
        # get b vector, it's an entry in C
        b = C[row]

        # Now, consider Ax = b.
        # Solve for x... x = inv(A)b
        # x is the row we want

        # so... it's off to find an inverse matrix
        # start by making a 'pseudo-augmented' matrix
        # it's like an augmented matrix but only has zeroes appended
        AA = []
        for r in range(len(P)):
            AA.append([])
            for c in range(n):
                AA[r].append(P[r][c])
            for c in range(n):
                AA[r].append(0)

        if debug:
            print('AA:', AA)

        # let's see if we can find enough good rows to form an inverse
        for r in range(n):
            # find a row to swap into place
            swapRow = -1
            for r2 in range(r, len(AA)):
                if AA[r2][r] != 0:
                    swapRow = r2
                    break

            # if we failed, then either there is no solution or there are too many solutions
            # either way, add an extra row of zeroes to the end and choose it to be the swap row
            if swapRow == -1:
                # either multiple solutions exist, or no solutions exist
                nSolutions = 2
                if debug:
                    print('No swap row found')
                    print('AA:', AA)
                # exit(0)
                swapRow = len(AA)
                AA.append([])
                for c in range(2*n):
                    AA[swapRow].append(0)
                b.append(0)

            # swap the rows
            for c in range(2*n):
                tmp = AA[swapRow][c]
                AA[swapRow][c] = AA[r][c]
                AA[r][c] = tmp
            # don't forget to swap rows in b
            tmp = b[swapRow]
            b[swapRow] = b[r]
            b[r] = tmp

            # add 1 to the proper column on the augmented side
            AA[r][n+r] += 1

            # scale the row so that column r is 1
            inv = inverses[AA[r][r]]
            for c in range(2*n):
                AA[r][c] = (AA[r][c] * inv) % 37

            # subtract the (scaled) row from all others, set column r to zero
            for r2 in range(len(AA)):
                if r != r2:
                    scale = AA[r2][r]
                    for c in range(2*n):
                        AA[r2][c] = (AA[r2][c] + 37 - (scale * AA[r][c]) % 37) % 37

        # if we get here, we found an inverse matrix
        if debug:
            print('found inverse')
            print('AA:', AA)

        # compute x = inv(A)*b
        x = []
        for r in range(n):
            x.append(0)
            for c in range(n):
                x[r] = (x[r] + AA[r][c+n] * b[c]) % 37

        # and add x to T
        T.append(x)

    return T


n = int(input())
plainText = input()
cipherText = input()

plain = []
cipher = []

for ii in range(len(plainText)):
    plain.append(alphabet.index(plainText[ii]))
    cipher.append(alphabet.index(cipherText[ii]))

nSolutions = 1

ans = findMatrix()

# try to encrypt using the result
encrypt()

if debug:
    print('ans:', ans)

if nSolutions == 0:
    print('No solution')
elif nSolutions == 2:
    print('Too many solutions')
else:
    for line in ans:
        print(' '.join(list(map(str, line))))
