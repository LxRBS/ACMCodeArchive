p1, p2 = input(), input()
def concat(a,b): return a+b
def shuffle(a): return sorted(a)
if eval(p1) != eval(p2): print('not equal')
else:
  def shuffle(a): return sorted(a, reverse=True)
  print('equal' if eval(p1) == eval(p2) else 'not equal')
