beginfig(1)
u = 15mm;
drawarrow (0,0)--(6u,0);
drawarrow (0,0)--(0,6u);

dotlabel.llft("0", (0,0));
for i=1 step 1 until 5:
  draw (i*u,-.1u)--(i*u,.1u);
  draw (i*u,0)--(i*u,5.5u) withpen pencircle scaled 0.005u dashed evenly;
  label.bot(decimal(i), (i*u,-.1u));
endfor;
label.bot(btex $x$ etex, (6u,0));

for i=1 step 1 until 5:
  draw (-.1u,i*u)--(.1u,i*u);
  draw (0,i*u)--(5.5u,i*u) withpen pencircle scaled 0.005u dashed evenly;
  label.lft(decimal(i), (-.1u,i*u));
endfor;
label.lft(btex $y$ etex, (0,6u));

path square;
square = (2u,4u)--(3u,2u)--(5u,3u)--(4u,5u)--cycle;

alpha = 5/8;  % alpha: 0=invisible, 1=opaque
color filler; filler = .95[blue,white];
picture bg, fg; 
bg = currentpicture; % save the current pic *before* filling the box
fg = image( 
  for e within bg:
    draw e if 5=colormodel e: withcolor alpha[colorpart e, filler] fi;
  endfor
);
clip fg to square; 

fill square withcolor filler;  
draw fg;
draw square;


endfig;
end