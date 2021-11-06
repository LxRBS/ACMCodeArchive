#!/usr/bin/python3

#
# generate...
# 10 random files, 1 for each size
# ABCABC -> JKLMNO
# ABCDABCD -> WXYZWXYY
# ABCABCDEF w/random T
# ABCDEFABC w/random T
# ABCDEFDEF w/random T
# ABCDEABCDEVWXYZQRSTUJKLMN w/random T
# 10 zero matrix
# 10 one matrix
# 9 identity matrix (1x1 already done)
# 10 random with one char wrong
#


import random

inverses = [0, 1, 19, 25, 28, 15, 31, 16, 14, 33, 26, 27, 34, 20, 8, 5, 7, 24, 35, 2, 13, 30, 32, 29, 17, 3, 10, 11, 4,
            23, 21, 6, 22, 9, 12, 18, 36]


def generateInvertibleMatrix(n):
    m = []
    m2 = []
    for i in range(n):
        m.append([])
        m2.append([])
        for j in range(n):
            a = random.randrange(0, 37)
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
        for r2 in range(r, n):
            if m2[r2][r] != 0 and not found:
                # swap row r with row r2... they might be the same
                found = True
                for c in range(2 * n):
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
        for c in range(2 * n):
            m2[r][c] = (m2[r][c] * a) % 37

        #    print(m2[r])

        # add scaled row to all other rows to zero out column r
        for r2 in range(n):
            if r2 != r:
                a = m2[r2][r]
                for c in range(2 * n):
                    m2[r2][c] = (m2[r2][c] + 37 - (a * m2[r][c]) % 37) % 37

    #  print(m2)

    m3 = []
    m4 = []
    for r in range(n):
        m3.append([])
        m4.append([])
        for c in range(n):
            m3[r].append(m2[r][c + n])
            m4[r].append(0)

    for r in range(n):
        for c in range(n):
            for k in range(n):
                m4[r][c] = (m4[r][c] + m[r][k] * m3[k][c]) % 37

    # print(m4)

    return m


def generateRandomPlain(ll):
    dest = []

    for ll in range(ll):
        dest.append(alphabet[random.randrange(0, 37)])

    return dest


def encrypt():
    cText = []
    pText = []
    for i in range(len(plain)):
        pText.append(alphabet.index(plain[i]))

    for i in range(0, len(plain), t):
        out = [0] * t

        for j in range(t):
            for k in range(t):
                out[j] += A[j][k] * pText[i + k]
            # out[j] = alphabet[out[j] % 37]
            cText.append(alphabet[out[j] % 37])

    return cText


def isZeroMatrix(M):
    for r in M:
        for c in r:
            if c != 0:
                return False

    return True


def isOneMatrix(M):
    for r in M:
        for c in r:
            if c != 1:
                return False

    return True


def isIdentityMatrix(M):
    for r in range(len(M)):
        for c in range(len(M)):
            if r == c:
                expect = 1
            else:
                expect = 0
            if M[r][c] != expect:
                return False

    return True


def writeOut(n, pText, cText, num, desc):
    fName = '{:03}-{}.in'.format(num, desc)
    num += 1

    f = open(fName, "w")
    f.write(str(n))
    f.write('\n')

    f.write(''.join(pText))
    f.write('\n')

    f.write(''.join(cText))
    f.write('\n')

    f.close()


alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 "

caseNum = 1

# ABCABC -> JKLMNO
writeOut(3, ['A', 'B', 'C', 'A', 'B', 'C'], ['J', 'K', 'L', 'M', 'N', 'O'], caseNum, 'no')
caseNum += 1

# ABCDABCD -> WXYZWXYY
writeOut(4, ['A', 'B', 'C', 'D', 'A', 'B', 'C', 'D'], ['W', 'X', 'Y', 'Z', 'W', 'X', 'Y', 'Y'], caseNum, 'no')
caseNum += 1

# ABCABCDEF w/random T
A = None
while A is None:
    A = generateInvertibleMatrix(3)
    if A is not None and (isZeroMatrix(A) or isOneMatrix(A) or isIdentityMatrix(A)):
        A = None

plain = ['A', 'B', 'C', 'A', 'B', 'C', 'D', 'E', 'F']

t = 3
cipher = encrypt()

writeOut(3, plain, cipher, caseNum, 'manyA')
caseNum += 1

# ABCDEFABC w/random T
A = None
while A is None:
    A = generateInvertibleMatrix(3)
    if A is not None and (isZeroMatrix(A) or isOneMatrix(A) or isIdentityMatrix(A)):
        A = None

plain = ['A', 'B', 'C', 'D', 'E', 'F', 'A', 'B', 'C']

cipher = encrypt()

writeOut(3, plain, cipher, caseNum, 'manyB')
caseNum += 1

# ABCDEFDEF w/random T
A = None
while A is None:
    A = generateInvertibleMatrix(3)
    if A is not None and (isZeroMatrix(A) or isOneMatrix(A) or isIdentityMatrix(A)):
        A = None

plain = ['A', 'B', 'C', 'D', 'E', 'F', 'D', 'E', 'F']

cipher = encrypt()

writeOut(3, plain, cipher, caseNum, 'manyC')
caseNum += 1

# ABCDEABCDEVWXYZQRSTUJKLMN w/random T
A = None
while A is None:
    A = generateInvertibleMatrix(5)
    if A is not None and (isZeroMatrix(A) or isOneMatrix(A) or isIdentityMatrix(A)):
        A = None

plain = ['A', 'B', 'C', 'D', 'E', 'A', 'B', 'C', 'D', 'E', 'V', 'W', 'X', 'Y', 'Z', 'Q', 'R', 'S', 'T', 'U',
         'J', 'K', 'L', 'M', 'N']

t = 5
cipher = encrypt()

writeOut(5, plain, cipher, caseNum, 'manyD')
caseNum += 1

# ABCDABCDABCDWXYZABCDABCDABCDJKLMABCDABCDABCDPQRS w/random T
A = None
while A is None:
    A = generateInvertibleMatrix(4)
    if A is not None and (isZeroMatrix(A) or isOneMatrix(A) or isIdentityMatrix(A)):
        A = None

print(A)
plain = ['A', 'B', 'C', 'D', 'A', 'B', 'C', 'D', 'A', 'B', 'C', 'D', 'W', 'Y', 'X', 'Z',
         'A', 'B', 'C', 'D', 'A', 'B', 'C', 'D', 'A', 'B', 'C', 'D', 'J', 'K', 'L', 'M',
         'A', 'B', 'C', 'D', 'A', 'B', 'C', 'D', 'A', 'B', 'C', 'D', 'E', 'H', 'G', 'F',
         'A', 'B', 'C', 'D', 'A', 'B', 'C', 'D', 'A', 'B', 'C', 'D', 'S', 'P', 'R', 'Q']

t = 4
cipher = encrypt()

writeOut(4, plain, cipher, caseNum, 'good')
caseNum += 1


# 10 random files, 1 for each size
for t in range(1, 11):
    A = None
    while A is None:
        A = generateInvertibleMatrix(t)
        if A is not None and (isZeroMatrix(A) or isOneMatrix(A) or isIdentityMatrix(A)):
            A = None

    pLen = max(20, t * t)
    pLen += t - (pLen % t)
    plain = generateRandomPlain(pLen)

    cipher = encrypt()

    writeOut(t, plain, cipher, caseNum, 'random')
    caseNum += 1

# 10 zero matrix
for t in range(1, 11):
    A = []
    for ii in range(t):
        A.append([])
        for jj in range(t):
            A[ii].append(0)

    pLen = max(20, t * t)
    pLen += t - (pLen % t)
    plain = generateRandomPlain(pLen)

    cipher = encrypt()

    writeOut(t, plain, cipher, caseNum, 'zero')
    caseNum += 1

# 10 one matrix
for t in range(1, 11):
    A = []
    for ii in range(t):
        A.append([])
        for jj in range(t):
            A[ii].append(1)

    pLen = max(20, t * t)
    pLen += t - (pLen % t)
    plain = generateRandomPlain(pLen)

    cipher = encrypt()

    writeOut(t, plain, cipher, caseNum, 'one')
    caseNum += 1

# 9 identity matrix (1x1 already done)
for t in range(2, 11):
    A = []
    for ii in range(t):
        A.append([])
        for jj in range(t):
            if ii == jj:
                A[ii].append(1)
            else:
                A[ii].append(0)

    pLen = max(20, t * t)
    pLen += t - (pLen % t)
    plain = generateRandomPlain(pLen)

    cipher = encrypt()

    writeOut(t, plain, cipher, caseNum, 'ident')
    caseNum += 1

# 10 random with one char wrong
for tt in range(10):
    t = random.randrange(3, 11)
    A = None
    while A is None:
        A = generateInvertibleMatrix(t)

    pLen = max(20, t * t)
    pLen += t - (pLen % t)
    plain = generateRandomPlain(pLen)

    cipher = encrypt()
    pos = random.randrange(0, len(cipher))
    if cipher[pos] == 'X':
        cipher[pos] = ' '
    else:
        cipher[pos] = 'X'

    writeOut(t, plain, cipher, caseNum, 'bad')
    caseNum += 1
