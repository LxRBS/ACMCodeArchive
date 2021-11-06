prologues:=3;
filenametemplate "%j.%c.eps";
verbatimtex
\documentclass[12pt]{article}
\usepackage[T1]{fontenc}
\begin{document}
etex

numeric rad, size;
rad:=20;
size:=4;
color colorA, colorB;
colorA:=0.4blue+0.6white;
colorB:=0.6red+0.4white;

def draw_cell(expr o, rad, lbl) =
  for i=0 upto 5:
    numeric aa, bb;
    aa := 30 + 60 * i;
    bb := 30 + 60 * (i + 1);
    pair A, B;
    A := o shifted (rad * cosd(aa), rad * sind(aa));
    B := o shifted (rad * cosd(bb), rad * sind(bb));
    if lbl = "-2,0":
      fill o--A--B--cycle withcolor colorA;
    fi;
    if lbl = "2,0":
      fill o--A--B--cycle withcolor colorB;
    fi;
    draw A--B; 
  endfor;
  defaultscale:=0.8;
  label(lbl, o);
enddef;

pair dx, dy;
dx := (rad * 1, 0);
dy := (rad * 0.5, rad * sqrt(3.0) / 2);

def draw_arrow(expr xa, ya, xb, yb, col) = 
  pair A, B;
  A = 0.5[ (2 * xa) * dx, (2 * ya) * dy];
  B = 0.5[ (2 * xb) * dx, (2 * yb) * dy];
  drawarrow A--B withcolor col;
enddef;

def field =
  pickup pencircle scaled 0.5;
  for i=-size upto size:
    for j=-size upto size:
      if ((-size <= i + j) and (i + j <= size)):
        pair ddx, ddy, O;
        ddx := (2 * i) * dx;
        ddy := (2 * j) * dy;
        O := 0.5[ddx, ddy];
        draw_cell(O, rad / 2, decimal(i) & "," & decimal(j));
      fi;
    endfor;
  endfor;
enddef;

beginfig(0);
	u := 1.4cm;
	pickup pencircle scaled 0.03u;
	draw (0, 0)--(u, u)--(2u, 0)--(3u, u)--(4u, 2u)--(5u, u)--(6u, 0);
	fill (0, 0)--(u, u)--(2u, 0)--(3u, u)--(4u, 2u)--(5u, u)--(6u, 0)--cycle withcolor 0.75white;
	pickup pencircle scaled 0.07u;
	draw (0, 0); draw (u, u); draw (2u, 0); draw (3u, u); draw (4u, 2u); draw (5u, u); draw (6u, 0);
	pickup pencircle scaled 0.07u;
	dotlabel.lrt("(3.4,0.6)", (3.4u, 0.6u));
	pickup pencircle scaled 0.03u;
	drawarrow (0, 0)--(0, 2.5u);
	drawarrow (0, 0)--(6.4u, 0);
	draw (-0.03u,1u)--(0.03u,1u);
	draw (-0.03u,2u)--(0.03u,2u);
	draw (1u,-0.03u)--(1u,0.03u);
	draw (3u,-0.03u)--(3u,0.03u);
	draw (4u,-0.03u)--(4u,0.03u);
	draw (5u,-0.03u)--(5u,0.03u);
	label.bot("x", (6.3u, 0));
	label.ulft("y", (0, 2.15u));
	label.llft("0", (0, 0));
	label.bot("1", (1u, 0));
	label.bot("2", (2u, 0));
	label.bot("3", (3u, 0));
	label.bot("4", (4u, 0));
	label.bot("5", (5u, 0));
	label.bot("6", (6u, 0));
	label.lft("2", (0, 2u));
	label.lft("1", (0, 1u));
	h := 2.2u;
	f := 2;
	label("(", (0.5u, h));
	label(")", (1.5u, h));
	label("(", (2.5u, h));
	label("(", (3.5u, h));
	label(")", (4.5u, h));
	label(")", (5.5u, h));
endfig;

end
