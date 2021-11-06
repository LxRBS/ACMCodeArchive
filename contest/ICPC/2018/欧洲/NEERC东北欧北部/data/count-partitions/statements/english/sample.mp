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

  B B B B B B B B B N
  B N
  B N
  B N 
  B N
  B N
  B N 
  B N
  B N
  
  i := 0; j := 0; gi := 0; gj := 11;

  B B B B B B N
  B B B B N
  B B B N
  B B N
  B N
  B N
  
  i := 0; j := 0; gi := 0; gj := 19;
  
  B B B B B N
  B B B B N
  B B B B N
  B B B N
  B N 
  
  i := 0; j := 0; gi := 0; gj := 26;

  B B B B B B B N
  B B B N
  B B B N
  B N
  B N
  B N
  B N
  
  
  i := 0; j := 0; gi := 0; gj := 35;
  
  B B B B B N
  B B B B B N
  B B B N
  B B N
  B B N
  
  
  
  
endfig;

end.
