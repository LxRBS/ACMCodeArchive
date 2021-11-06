#!/usr/bin/python3

board = []
choices = []

# count number of 1-bits in an integer
def countBits(n):
  c = 0
  while n != 0:
    c += 1
    n = n & (n - 1)
  return c

# unique location rule
def applyU():

  # loop over all digits
  d = 0
  while d < 10:
    d += 1

    # see if digit has only one choice in any row
    for r in range(9):
      # c == -1 --> no position found for d
      # c == -2 --> multiple positions found for d
      # c >= 0  --> c is the only position for d
      c = -1
      for i in range(9):
        if (choices[r][i] & (1 << d)) != 0:
          if c == -1:
            c = i
          else:
            c = -2
      # if only one position, apply the rule
      if c >= 0:
        board[r][c] = d
        makeChoice(r,c)
        return True
        
    # see if digit has only one choice in any column
    for c in range(9):
      r = -1
      for i in range(9):
        if (choices[i][c] & (1 << d)) != 0:
          if r == -1:
            r = i
          else:
            r = -2
      if r >= 0:
        board[r][c] = d
        makeChoice(r,c)
        return True
        
    # see if digit has only one choice in any 3x3 block
    for r2 in [0,3,6]:
      for c2 in [0,3,6]:
        r = -1
        c = -1
        for i in range(9):
          if (choices[r2+i//3][c2+i%3] & (1 << d)) != 0:
            if r == -1:
              r = r2 + i // 3
              c = c2 + i % 3
            else:
              r = -2
              c = -2
        if r >= 0:
          board[r][c] = d
          makeChoice(r,c)
          return True
          
  # if we get here, no digit had a single location in any row, column or block
  return False
  
# single value rule
def applyS():
  # loop over all cells
  for r in range(9):
    for c in range(9):
      # if exactly one choice exists, apply the rule here
      if countBits(choices[r][c]) == 1:
        # extract bit position == choice
        choice = 0
        while choices[r][c] != 1:
          choice += 1
          choices[r][c] = (choices[r][c] >> 1)
        # make the choice and return
        board[r][c] = choice
        makeChoice(r,c)
        return True
        
  # if we get here, no position has a single value remaining
  return False
  
# make a choice for [r][c]... board[r][c] has the choice filled in
def makeChoice(r,c):
  # bitmask turns off the selected bit
  bitmask = ~(1 << board[r][c])
  # selected cell has no more choices
  choices[r][c] = 0
  # turn off choice along row and column
  for i in range(9):
    choices[i][c] = (choices[i][c] & bitmask)
    choices[r][i] = (choices[r][i] & bitmask)
  # turn off choice in block
  r2 = r - r % 3
  c2 = c - c % 3
  for i in range(3):
    for j in range(3):
      choices[r2+i][c2+j] = (choices[r2+i][c2+j] & bitmask)

# mainline code

# read the input

for i in range(9):
  line = input()
  row = list(map(int,line.split(' ')))
  board.append(row)
  choices.append([1022]*9)

# count number of cells to fill  

numToFill = 0

for r in range(9):
  for c in range(9):
    if board[r][c] == 0:
      numToFill += 1
    else:
      makeChoice(r,c)
      
# apply the rules until they don't change the board

good = True

while good:
  good = False
  
  # try one unique location rule
  if applyU():
    good = True
    numToFill -= 1
    
  # try one single value rule
  if applyS():
    good = True
    numToFill -= 1
    
# done applying rules... if no cells left, we win, else, we lose. print outcome

if numToFill == 0:
  print('Easy')
  for r in board:
    r = map(str,r)
    s = ' '.join(r)
    print(s)
else:
  print('Not easy')
  for r in board:
    for i in range(9):
      if r[i] == 0:
        r[i] = '.'
      else:
        r[i] = str(r[i]);
    s = ' '.join(r);
    print(s)

# done

