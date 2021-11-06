#!/usr/bin/env pypy

s=raw_input()
if len(s)<3 or ((set('LR')&set(s[-3:])) and (set('UD')&set(s[-3:]))):
  x,y,bx,by=0,0,[],[]
  for m in s:
    dx=int(m=='R')-int(m=='L')
    dy=int(m=='U')-int(m=='D')
    a,i=(max,min) if max(dx,dy)>0 else (min,max)
    if dx: x=i([a(bx+[0])+dx]+[a-dx for a,b in zip(bx,by) if x*dx<a*dx and b==y])
    if dy: y=i([a(by+[0])+dy]+[b-dy for a,b in zip(bx,by) if y*dy<b*dy and a==x])
    bx+=[x+dx]; by+=[y+dy]
  k=set(zip(bx,by))
  print -x,-y
  print len(k)
  for a,b in k: print a-x,b-y
else:
  print 'impossible'
