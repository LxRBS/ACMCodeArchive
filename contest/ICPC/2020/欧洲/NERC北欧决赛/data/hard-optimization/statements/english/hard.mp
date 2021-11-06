beginfig(1)
  numeric i;
  u := 0.8cm;
  drawarrow (0, 0) -- (12u, 0);
  for i = 0 upto 11:
     draw (i * u, -0.1u) -- (i * u, 0.1u);
     label.bot(decimal i, (i * u, 0));
     draw (i * u, 0) -- (i * u, 4u) dashed withdots;
  endfor

  draw (1u, 1u) withpen pencircle scaled 4bp;
  draw (10u, 1u) withpen pencircle scaled 4bp;
  draw (1u, 1u) -- (10u, 1u);
  label.bot(decimal 1, (5.5u, 1u));

  draw (2u, 2u) withpen pencircle scaled 4bp;
  draw (3u, 2u) withpen pencircle scaled 4bp;
  draw (2u, 2u) -- (3u, 2u);
  label.bot(decimal 2, (2.5u, 2u));

  draw (5u, 2u) withpen pencircle scaled 4bp;
  draw (9u, 2u) withpen pencircle scaled 4bp;
  draw (5u, 2u) -- (9u, 2u);
  label.bot(decimal 3, (7.0u, 2u));

  draw (6u, 3u) withpen pencircle scaled 4bp;
  draw (7u, 3u) withpen pencircle scaled 4bp;
  draw (6u, 3u) -- (7u, 3u);
  label.bot(decimal 4, (6.5u, 3u));
endfig;

beginfig(2)
  numeric i;
  u := 0.8cm;
  drawarrow (0, 0) -- (12u, 0);
  for i = 0 upto 11:
     draw (i * u, -0.1u) -- (i * u, 0.1u);
     label.bot(decimal i, (i * u, 0));
     draw (i * u, 0) -- (i * u, 4u) dashed withdots;
  endfor

  draw (3u, 1u) withpen pencircle scaled 4bp;
  draw (6u, 1u) withpen pencircle scaled 4bp;
  draw (3u, 1u) -- (6u, 1u);
  label.bot(decimal 1, (4.5u, 1u));

  draw (2u, 2u) withpen pencircle scaled 4bp;
  draw (3u, 2u) withpen pencircle scaled 4bp;
  draw (2u, 2u) -- (3u, 2u);
  label.bot(decimal 2, (2.5u, 2u));

  draw (7u, 2u) withpen pencircle scaled 4bp;
  draw (9u, 2u) withpen pencircle scaled 4bp;
  draw (7u, 2u) -- (9u, 2u);
  label.bot(decimal 3, (8.0u, 2u));

  draw (6u, 3u) withpen pencircle scaled 4bp;
  draw (7u, 3u) withpen pencircle scaled 4bp;
  draw (6u, 3u) -- (7u, 3u);
  label.bot(decimal 4, (6.5u, 3u));
endfig;

end.
