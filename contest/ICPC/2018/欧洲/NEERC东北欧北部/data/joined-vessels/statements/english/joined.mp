prologues := 3; % make it work with ps2pdf
outputtemplate := "%j-%c.eps"; % better file names

u := 50pt;

color mygray;
mygray := 0.6 * white;


vardef rects(expr n)(suffix hs, ls, st) = 
  pen p;
  psz := 6pt;
  interh := 0.1u;
  p := pencircle scaled psz;
  for i = 0 upto n - 1:
    pair shift;
    shift := (3.5u, 0) * i;
    if i = 0:
      draw ((0, 0) -- (0, 6u)) shifted shift withpen p;
    else:
      draw ((0, 0) -- (0, hs[i - 1] * u - interh - 0.5psz)) shifted shift withpen p;
      draw ((0, hs[i - 1] * u + interh + 0.5psz) -- (0, 6u)) shifted shift withpen p;
    fi;
    draw ((0, 0) -- (3u, 0)) shifted shift withpen p;
    if i = n - 1:
      draw ((3u, 0) -- (3u, 6u)) shifted shift withpen p;
    else:
      draw ((3u, 0) -- (3u, hs[i] * u - interh - 0.5psz)) shifted shift withpen p;
      draw ((3u, hs[i] * u + interh + 0.5psz) -- (3u, 6u)) shifted shift withpen p;
    fi;
    if ls[i] > 0:
      fill ((0.5psz, 0.5psz) -- (3u - 0.5psz, 0.5psz) -- (3u - 0.5psz, ls[i] * u) -- (0.5psz, ls[i] * u) -- cycle) shifted shift withcolor mygray;
    fi;
  endfor;
  for i = 0 upto n - 2:
    pair shift;
    shift := (3.5u * i + 3u, hs[i] * u);
    draw ((0, -interh) -- (0.5u, -interh)) shifted shift withpen p;
    draw ((0, +interh) -- (0.5u, +interh)) shifted shift withpen p;
    if (hs[i] <= ls[i]) or (hs[i] <= ls[i + 1]):
      fill ((-0.5psz, 0) -- (0.5u + 0.5psz, 0) -- (0.5u + 0.5psz, -interh + 0.5psz) -- (-0.5psz, -interh + 0.5psz) -- cycle) shifted shift withcolor mygray;
    fi;
    if (hs[i] < ls[i]) or (hs[i] < ls[i + 1]):
      fill ((-0.5psz, 0) -- (0.5u + 0.5psz, 0) -- (0.5u + 0.5psz, interh - 0.5psz) -- (-0.5psz, interh - 0.5psz) -- cycle) shifted shift withcolor mygray;
    fi;
    if (hs[i] > ls[i]) and (hs[i] <= ls[i + 1]):
      pair last;
      last := (0, -0.5psz);
      speed := 1;
      for j = 0 step 0.01 until (ls[i + 1] - ls[i] - 0.5psz / u):
        pair next;
        next := last - (0.1 u / speed, 0.01u);
        draw (last .. next) shifted shift withcolor mygray withpen p;
        last := next;
        speed := speed + 1;
      endfor;
    fi;
    if (hs[i] <= ls[i]) and (hs[i] > ls[i + 1]):
      pair last;
      last := (0.5u, -0.5psz);
      speed := 1;
      for j = 0 step 0.01 until (ls[i] - ls[i+1] - 0.5psz / u):
        pair next;
        next := last - (-0.1 u / speed, 0.01u);
        draw (last .. next) shifted shift withcolor mygray withpen p;
        last := next;
        speed := speed + 1;
      endfor;
    fi;
  endfor;
  draw (1.5u + 3.5 u * st, 0.1u) -- (1.5u + 3.5u * st, 6u) withcolor mygray withpen p;
enddef;

beginfig(1)
  numeric hs[];
  numeric ls[];
  
  hs[0] = 1;
  hs[1] = 4;
  hs[2] = 2;
  hs[3] = 3;
  hs[4] = 5;

  ls[0] = 5;
  ls[1] = 5;
  ls[2] = 5;
  ls[3] = 5;
  ls[4] = 5;
  ls[5] = 0.1;

  rects(6, hs, ls, 0);
endfig;

beginfig(2)
  numeric hs[];
  numeric ls[];
  
  hs[0] = 1;
  hs[1] = 4;
  hs[2] = 2;
  hs[3] = 3;
  hs[4] = 5;

  ls[0] = 0.1;
  ls[1] = 1;
  ls[2] = 4;
  ls[3] = 4;
  ls[4] = 4;
  ls[5] = 5;

  rects(6, hs, ls, 5);
endfig;

beginfig(3)
  numeric hs[];
  numeric ls[];
  
  hs[0] = 1;
  hs[1] = 4;
  hs[2] = 2;
  hs[3] = 3;
  hs[4] = 5;

  ls[0] = 4;
  ls[1] = 4;
  ls[2] = 3;
  ls[3] = 3;
  ls[4] = 0.1;
  ls[5] = 0;

  rects(6, hs, ls, 1);
endfig;

beginfig(4)
  numeric hs[];
  numeric ls[];
  
  hs[0] = 1;
  hs[1] = 4;
  hs[2] = 2;
  hs[3] = 3;
  hs[4] = 5;

  ls[0] = 0;
  ls[1] = 0.1;
  ls[2] = 4;
  ls[3] = 4;
  ls[4] = 4;
  ls[5] = 0;

  rects(6, hs, ls, 4);
endfig;

end.