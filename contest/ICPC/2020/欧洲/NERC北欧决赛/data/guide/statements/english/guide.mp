u := 1cm;

beginfig(1)
  z1 = (2u,2u);
  z2 = (1u,1u);
  z3 = (3u,1u);
  z4 = (0u,0u);
  z5 = (2u,0u);
  z6 = (4u,0u);
  dotlabel.urt("1",z1);
  dotlabel.ulft("2",z2);
  dotlabel.urt("3",z3);
  dotlabel.ulft("4",z4);
  dotlabel.urt("5",z5);
  dotlabel.urt("6",z6);
  draw z4--z2--z1;
  draw z5--z2;
  draw z6--z3--z1;
  pickup pencircle scaled 1pt;
  drawarrow z1{dir(200)}..z2;
endfig;

beginfig(2)
  z1 = (2u,2u);
  z2 = (1u,1u);
  z3 = (3u,1u);
  z4 = (0u,0u);
  z5 = (2u,0u);
  z6 = (4u,0u);
  dotlabel.urt("1",z1);
  dotlabel.ulft("2",z2);
  dotlabel.urt("3",z3);
  dotlabel.ulft("4",z4);
  dotlabel.urt("5",z5);
  dotlabel.urt("6",z6);
  draw z4--z2--z1;
  draw z5--z2;
  draw z6--z3--z1;
  pickup pencircle scaled 1pt;
  drawarrow z1{dir(-20)}..z3;
  drawarrow z3{dir(-20)}..z6;
  drawarrow z6{dir(160)}..z3;
  drawarrow z3{dir(160)}..z1;
  drawarrow z1{dir(200)}..z2;
  drawarrow z2{dir(-20)}..z5;
  drawarrow z5{dir(160)}..z2;
  drawarrow z2{dir(200)}..z4;
endfig;

beginfig(3)
  z1 = (0u,4u);
  z2 = (0u,3u);
  z3 = (0u,2u);
  z4 = (0u,1u);
  z5 = (0u,0u);
  dotlabel.urt("1",z1);
  dotlabel.urt("2",z2);
  dotlabel.urt("3",z3);
  dotlabel.urt("4",z4);
  dotlabel.urt("5",z5);
  draw z1--z2--z3--z4--z5;
  pickup pencircle scaled 1pt;
  drawarrow z1{dir(250)}..z2;
  drawarrow z2{dir(250)}..z3;
  drawarrow z3{dir(250)}..z4;
endfig;

end;

