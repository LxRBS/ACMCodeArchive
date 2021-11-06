#include <bits/stdc++.h>
using namespace std;

int sign(int x){
  return x? x>0? +1: -1: 0;
}

struct vec2{
  int x,y;
  vec2(int x,int y):x(x),y(y){}
};

int main(){
  string s; cin>>s;
  int const n=s.length();

  vector<vec2> moves;
  for (auto i: s)
    switch (i){
      case 'U': moves.emplace_back(0,+1); break;
      case 'D': moves.emplace_back(0,-1); break;
      case 'L': moves.emplace_back(-1,0); break;
      case 'R': moves.emplace_back(+1,0); break;
      default: assert(false);
    }

  // Cases with three or more final moves in the same direction are impossible,
  // because it is impossible to avoid going over the target twice.
  if (moves.size()>=3
      and abs(moves[n-3].x)==abs(moves[n-2].x)
      and abs(moves[n-2].x)==abs(moves[n-1].x)){
    cout<<"impossible"<<endl;
    return 0;
  }

  vector<vec2> blocks;

  int radius=100'000'000;
  vec2 ball={0,0};
  for (int i=0; i<n; i++){
    if (i==0 or abs(moves[i].x)!=abs(moves[i-1].x)){
      radius+=2;
      if (moves[i].x){
        blocks.emplace_back(-radius,ball.y);
        blocks.emplace_back(+radius,ball.y);
      }else{
        blocks.emplace_back(ball.x,-radius);
        blocks.emplace_back(ball.x,+radius);
      }
    }
    if (moves[i].x) ball.x=(radius-1)*sign(moves[i].x);
    if (moves[i].y) ball.y=(radius-1)*sign(moves[i].y);
  }

  cout<<-ball.x<<" "<<-ball.y<<endl;
  cout<<blocks.size()<<endl;
  for (auto i: blocks){
    cout<<" "<<i.x-ball.x<<" "<<i.y-ball.y<<endl;
  }
}
