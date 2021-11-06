prologues := 3; % make it work with ps2pdf
outputtemplate := "%j-%c.eps"; % better file names

def A =
  j := j + 1;
enddef;

def B =
  draw ((0u, 0u) -- (0u, 1u) -- (1u, 1u) -- (1u, 0u) -- cycle) shifted ((j + gj) * u, -(i + gi) * u); 
  j := j + 1;
enddef;

def N = 
  i := i - 1;
  j := 0;
enddef;

beginfig(1)
  u := 4mm;

  i := 0; j := 0; gi := 0; gj := 0;

  B B B B B N
  B B B N
  B B N
  B N 
  B N

  i := 0; j := 0; gi := 0; gj := 7;

  B B B B N
  B B B N
  B B N
  B B N 
  B N

  i := 0; j := 0; gi := 0; gj := 13;

  B B B B N
  B B B B N
  B B A B N
  B N

endfig;

beginfig(2)
  u := 4mm;

  i := 0; j := 0; gi := 0; gj := 0;

  B B B B B N
  B B B B N
  B B B B N
  B B B N 
  B N

  drawarrow (0,0)*u -- (6,0)*u;
  drawarrow (0,0)*u -- (0,6)*u;
  draw (0,0)*u -- (5,5)*u dashed evenly;
  label.bot(btex $x$ etex, (5.5u, -0.1u) / 0.8) scaled 0.8;
  label.lft(btex $y$ etex, (-0.1u, 5.5u) / 0.8) scaled 0.8;

endfig;



end.