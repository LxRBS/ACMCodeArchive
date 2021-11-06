size(1000);
defaultpen(4);
bbox(white, Fill);

pen longdashed = linetype(new real[] {4,2});
pen teampen = rgb(0, 0, 1);
pen accessptpen = rgb(0.8, 0, 0.5);
pen fs = fontsize(120pt);

void draw_box(pair team, int f, int l) {
  real size = 0.07;
  fill((team.x-size,team.y-size)--(team.x-size,team.y+size)--(team.x+size,team.y+size)--(team.x+size,team.y-size)--cycle,teampen);
  string teams = string(f+1);
  if (f != l) {
    teams = teams + " - " + string(l + 1);
  }
  if (l < 20) {
    label(teams, (team.x+0.2, team.y+0.12), fs);
  }
}

int n = stdin;
bool first = true;
pair last = (0, 0);
int lastTeam = 0;
for (int i = 0; i < n; ++i) {
  real xCoord = stdin, yCoord = stdin, xTeam = stdin, yTeam = stdin;
  pair coord = (xCoord, yCoord);
  pair team = (xTeam, yTeam);
  draw(coord--team, longdashed);
  if (!first && last != team) {
    draw_box(last, lastTeam, i - 1);
    lastTeam = i;
  }
  last = team;
  first = false;
  dot(coord, accessptpen);
}
draw_box(last, lastTeam, n - 1);

shipout(bbox(xmargin=10, white, Fill));
