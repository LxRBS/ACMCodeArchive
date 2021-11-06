#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll,ll>;
#define sz(c) ll((c).size())
#define mp make_pair
#define xx first
#define yy second
#define FOR(i,a,b) for(ll i = (a); i < (b); i++)
#define FORD(i,a,b) for(ll i = ll(b) - 1; i >= (a); i--)

map<char,pll> movement = {{'U',{0,-1}},{'D',{0,1}},{'L',{1,0}},{'R',{-1,0}}};

inline ll get_direction(const char move) {
  if(movement[move].yy == 0)
    return 0;
  return 1;
}

int main() {
	ios_base::sync_with_stdio(false);
  string moves;
  cin >> moves;
  ll len = sz(moves);

  if(len >= 3 && moves[len-1] == moves[len-3] && get_direction(moves[len-1]) == get_direction(moves[len-2])){
    cout << "impossible" << endl;
    return 0;
  }

  ll ball_x = 0, ball_y = 0, next_change_x = 0, next_change_y = 0, direction = -1, radius = 1;
  set<pll> walls;
  FORD(i,0,sz(moves)) {
    char move = moves[i];
    ll new_direction = get_direction(move);
    pll ball_movement = movement[move];
    if(direction != new_direction) {
      direction = new_direction;
      radius += 100;
      ball_x = next_change_x;
      ball_y = next_change_y;
      next_change_x += radius * ball_movement.xx;
      next_change_y += radius * ball_movement.yy;
    }
    walls.insert(mp(ball_x - ball_movement.xx, ball_y - ball_movement.yy));
    ball_x = next_change_x + radius * ball_movement.xx;
    ball_y = next_change_y + radius * ball_movement.yy;
  }
  for(auto entry : movement) {
    auto it = walls.find(entry.yy);
    if(it != walls.end()) walls.erase(it);
  }

  cout << next_change_x << " " << next_change_y << endl;
  cout << sz(walls) << endl;
  for(pll wall : walls) cout << wall.xx << " " << wall.yy << endl;

	return 0;
}
