beginfig (1);
  label.top(btex Participant\ 1 etex, (1.5cm, -0cm) / 0.85) scaled 0.85;
  label.top(btex Participant\ 2 etex, (1.5cm, -1cm) / 0.85) scaled 0.85;
  label.top(btex Participant\ 3 etex, (1.5cm, -2cm) / 0.85) scaled 0.85;
  label.top(btex Participant\ 4 etex, (1.5cm, -3cm) / 0.85) scaled 0.85;
  label.top(btex Participant\ 5 etex, (1.5cm, -4cm) / 0.85) scaled 0.85;
  label.top(btex Participant\ 6 etex, (1.5cm, -5cm) / 0.85) scaled 0.85;
  label.top(btex Participant\ 7 etex, (1.5cm, -6cm) / 0.85) scaled 0.85;
  label.top(btex Participant\ 8 etex, (1.5cm, -7cm) / 0.85) scaled 0.85;

  label.top(btex Winner of S1M1 etex, (4.5cm, -0.5cm) / 0.85) scaled 0.85;
  label.top(btex Winner of S1M2 etex, (4.5cm, -2.5cm) / 0.85) scaled 0.85;
  label.top(btex Winner of S1M3 etex, (4.5cm, -4.5cm) / 0.85) scaled 0.85;
  label.top(btex Winner of S1M4 etex, (4.5cm, -6.5cm) / 0.85) scaled 0.85;

  label.top(btex Winner of S2M1 etex, (7.5cm, -1.5cm) / 0.85) scaled 0.85;
  label.top(btex Winner of S2M2 etex, (7.5cm, -5.5cm) / 0.85) scaled 0.85;

  label.top(btex Winner of S3M1 etex, (10.5cm, -3.5cm) / 0.85) scaled 0.85;


  for i:=0 upto 7:
    draw (0cm, i * -1cm) -- (3cm,i * -1cm);
  endfor;

  for i:=0 upto 3:
    draw (3cm,(2 * i) * -1cm) -- (3cm,(2 * i + 1) * -1cm);
  endfor;

  for i:=0 upto 3:
    draw (3cm,(2 * i + 0.5) * -1cm) -- (6cm,(2 * i + 0.5) * -1cm);
  endfor;

  for i:=0 upto 1:
    draw (6cm, (4 * i + 0.5) * -1cm) -- (6cm, (4 * i + 2 + 0.5) * -1cm);
  endfor;

  draw (6cm, (4 * 0 + 1.5) * -1cm) -- (9cm, (4 * 0 + 1.5) * -1cm);
  draw (6cm, (4 * 1 + 1.5) * -1cm) -- (9cm, (4 * 1 + 1.5) * -1cm);
  draw (9cm, (4 * 0 + 1.5) * -1cm) -- (9cm, (4 * 1 + 1.5) * -1cm);
  draw (9cm, (4 * 0 + 1.5 + 2) * -1cm) -- (12cm, (4 * 0 + 1.5 + 2) * -1cm);

  draw (2cm, 0.8cm) -- (2cm, 1cm) -- (4cm, 1cm) -- (4cm, 0.8cm);
  label.top(btex Stage 1 etex, (3cm, 1cm) / 0.9) scaled 0.9;
  
  draw (5cm, 0.8cm) -- (5cm, 1cm) -- (7cm, 1cm) -- (7cm, 0.8cm);
  label.top(btex Stage 2 etex, (6cm, 1cm) / 0.9) scaled 0.9;
  
  draw (8cm, 0.8cm) -- (8cm, 1cm) -- (10cm, 1cm) -- (10cm, 0.8cm);
  label.top(btex Stage 3 etex, (9cm, 1cm) / 0.9) scaled 0.9;
endfig;

end.