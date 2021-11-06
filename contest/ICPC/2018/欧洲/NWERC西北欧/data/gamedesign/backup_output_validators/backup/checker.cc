#include <algorithm>/*{{{*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>
#include <climits>
#include <utility>
#include <cctype>
#include <string>
#include <vector>
#include <stack>
#include <map>
#include <set>
using namespace std;/*}}}*/

// #define DBG(x) {x}

#ifndef DBG
#define DBG(x)
#endif

enum JudgeCode:int{
  judge_error=1,
  correct=42,
  wrong_answer=43,
};

namespace limits{
  constexpr int64_t moves_max=20ll; // 20
  constexpr int64_t blocks_max=10ll*1000; // 10^4
  constexpr int64_t border_radius=1ll*1000*1000*1000+1; // 10^9
}

struct Vec2{/*{{{*/
  int64_t x;
  int64_t y;

  explicit Vec2(int64_t x,int64_t y,JudgeCode const on_fail): x(x), y(y){
    if (abs(x)>=limits::border_radius or abs(y)>=limits::border_radius){
      cout<<"Vector out of bounds: "<<x<<" "<<y<<endl;
      exit(on_fail);
    }
  }

  bool operator<(Vec2 const &other) const{
    return x!=other.x? x<other.x: y<other.y;
  }

  bool operator==(Vec2 const &other) const{
    return x==other.x and y==other.y;
  }

  bool operator!=(Vec2 const &other) const{
    return x!=other.x or y!=other.y;
  }
};/*}}}*/

class Solution{/*{{{*/
  private:
    vector<Vec2> const moves;

    map<int64_t, vector<int64_t>> block_rows;
    map<int64_t, vector<int64_t>> block_cols;

  public:
    Solution(vector<Vec2> const &moves,vector<Vec2> const &blocks): moves(moves){
      DBG(cerr<<"imported blocks"<<endl;)

      // Validate input (should be done by the input_format_validator already)
      for (int i=0; i<moves.size(); i++){
        assert(abs(moves[i].x)==0 or abs(moves[i].y)==0);
        assert(abs(moves[i].x)==1 or abs(moves[i].y)==1);
      }
      for (int i=1; i<moves.size(); i++){
        assert(moves[i]!=moves[i-1]);
      }
      DBG(cerr<<"finished checking moves"<<endl;)

      for (Vec2 const &block: blocks){
        block_rows[block.y].emplace_back(block.x);
        block_cols[block.x].emplace_back(block.y);
      }
      DBG(cerr<<"finished writing rows and columns"<<endl;)
      for (auto &row: block_rows){
        sort(row.second.begin(),row.second.end());
      }
      DBG(cerr<<"finished sorting rows"<<endl;)
      for (auto &col: block_cols){
        sort(col.second.begin(),col.second.end());
      }
      DBG(cerr<<"finished sorting columns"<<endl;)
    }

  private:
    bool crosses_finish(Vec2 const a,Vec2 const b) const{
      return a.x==0 and b.x==0 and min(a.y,b.y)<=0 and 0<=max(a.y,b.y)
          or a.y==0 and b.y==0 and min(a.x,b.x)<=0 and 0<=max(a.x,b.x);
    }

    bool has_block(Vec2 const &block) const{
      auto it=block_rows.find(block.y);
      if (it==block_rows.end()) return false;
      return binary_search(it->second.begin(),it->second.end(),block.x);
    }

    Vec2 simulate(Vec2 const ball,Vec2 const dir) const{
      if (has_block(ball)){
        return ball;
      }

      if (dir.y==0){
        return Vec2(
            dir.x>0
                ? find_next(block_rows, ball.y, ball.x, +limits::border_radius)-1
                : find_prev(block_rows, ball.y, ball.x, -limits::border_radius)+1,
            ball.y,
            judge_error);
      }else{
        return Vec2(
            ball.x,
            dir.y>0
                ? find_next(block_cols, ball.x, ball.y, +limits::border_radius)-1
                : find_prev(block_cols, ball.x, ball.y, -limits::border_radius)+1,
            judge_error);
      }
    }

    int64_t find_next(
        map<int64_t,vector<int64_t>> const &rows,
        int64_t const y,
        int64_t const x,
        int64_t const limit) const{
      auto const it=rows.find(y);
      if (it==rows.end() or it->second.empty() or it->second.back()<x){
        return limit;
      }
      return *upper_bound(it->second.begin(),it->second.end(),x);
    }

    int64_t find_prev(
        map<int64_t,vector<int64_t>> const &rows,
        int64_t const y,
        int64_t const x,
        int64_t const limit) const{
      auto const it=rows.find(y);
      if (it==rows.end() or it->second.empty() or it->second[0]>x){
        return limit;
      }
      return *--lower_bound(it->second.begin(),it->second.end(),x);
    }

  public:
    bool validate(Vec2 const start, JudgeCode const on_fail) const{
      if (has_block(start)){
        cout<<"Ball starts inside a block"<<endl;
        return false;
      }
      if (has_block(Vec2(0,0,on_fail))){
        cout<<"There is a block on top of the exit"<<endl;
        return false;
      }

      vector<Vec2> places={start};
      cout<<"  start: ("<<start.x<<","<<start.y<<")"<<endl;
      for (Vec2 const action: moves){
        places.push_back(simulate(places.back(),action));
        if (places[places.size()-1]==places[places.size()-2]){
          cout<<"On move "<<places.size()-1<<" the ball does not go anywhere"<<endl;
          return false;
        }
        cout<<"  move to: ("<<places.back().x<<","<<places.back().y<<")"<<endl;
      }

      for (size_t i=0; i+2<places.size(); i++){
        if (crosses_finish(places[i],places[i+1])){
          cout<<"Ball crosses (0,0) on move "<<i+1<<"/"<<moves.size()<<" (too early)"<<endl;
          return false;
        }
      }
      if (not crosses_finish(places[places.size()-2],places[places.size()-1])){
        cout<<"On the last move, the ball does not pass (0,0)"<<endl;
        return false;
      }

      return true;
    }
};/*}}}*/

vector<Vec2> read_blocks(istream &source,JudgeCode const on_fail){/*{{{*/
  int64_t n; source>>n;
  if (n<0 or limits::blocks_max<n){
    cout<<"Used too many blocks: "<<n<<"/"<<limits::blocks_max<<endl;
    exit(on_fail);
  }

  vector<Vec2> blocks;
  for (int64_t i=0; i<n; i++){
    int64_t x,y;
    if (not (source>>x>>y)){
      cout<<"Failed to read x and y coordinates"<<endl;
      exit(on_fail);
    }
    if (x<=-limits::border_radius or +limits::border_radius<=x){
      cout<<"x coordinate out of range: "<<x<<endl;
      exit(on_fail);
    }
    if (y<=-limits::border_radius or +limits::border_radius<=y){
      cout<<"y coordinate out of range: "<<y<<endl;
      exit(on_fail);
    }
    blocks.push_back(Vec2{x,y,on_fail});
  }

  sort(blocks.begin(),blocks.end());
  for (size_t i=1; i<blocks.size(); i++){
    if (blocks[i]==blocks[i-1]){
      cout<<"Block "<<blocks[i].x<<" "<<blocks[i].y<<" given more than once"<<endl;
      exit(on_fail);
    }
  }

  char dummy;
  if (source >> dummy) {
    cout<<"trailing output"<<endl;
    exit(on_fail);
  }

  DBG(cerr<<"finished reading team solution"<<endl;)
  return blocks;
}/*}}}*/

bool validate_solution(/*{{{*/
    string const description,
    istream &source,
    string const &first_word,
    vector<Vec2> const &moves,
    JudgeCode const on_fail){
  // Read starting location of ball.
  int64_t ball_x,ball_y;{
    stringstream sst(first_word);
    if (not (sst>>ball_x)){
      cout<<description<<" ball.x is not a number"<<endl;
      return false;
    }
    if (not (source>>ball_y)){
      cout<<description<<" ball.y is not a number"<<endl;
      return false;
    }
  }
  Vec2 ball_xy=Vec2(ball_x,ball_y,on_fail);

  if (ball_xy == Vec2(0,0,on_fail)) {
    cout<<description<<" ball starts on goal"<<endl;
    exit(on_fail);
  }

  // Read rest of solution.
  Solution const solution=Solution(moves,read_blocks(source,on_fail));
  DBG(cerr<<"finished storing "<<description<<" solution"<<endl;)

  // Check that the solution gets to (0,0) on the last move.
  return solution.validate(ball_xy,on_fail);
}/*}}}*/

int main(int argc, char **argv){
  ios::sync_with_stdio(false);

  if (argc<3){
    cerr<<"usage: "<<argv[0]<<" testcase.in testcase.ans [feedback_dir] < team.out"<<endl;
    return judge_error;
  }else if (argc<4){
    cerr<<"writing feedback to stdout"<<endl;
  }else{
    if (argc>4){
      cerr<<"warning: ignoring "<<argc-4<<" extra arguments"<<endl;
    }
    if (not freopen((string(argv[3]) + "/judgemessage.txt").c_str(), "a", stdout)){
      cerr<<"unable to open feedback file"<<endl;
      return judge_error;
    }
  }

  ifstream canonical_input(argv[1]);
  ifstream canonical_output(argv[2]);
  auto &team_output = cin;

  // Read canonical input.
  string moves_str;
  if (not (canonical_input>>moves_str)){
    cout<<"Failed to read moves from input"<<endl;
    return judge_error;
  }
  if (moves_str.length()<1 or limits::moves_max<moves_str.length()){
    cout<<"Too many moves in input or empty ('"<<moves_str<<"'). Maximum is "<<limits::moves_max<<endl;
    return judge_error;
  }
  vector<Vec2> moves;
  for (auto i: moves_str) {
    switch (i){
      case 'U': moves.push_back(Vec2{0,+1,judge_error}); break;
      case 'D': moves.push_back(Vec2{0,-1,judge_error}); break;
      case 'R': moves.push_back(Vec2{+1,0,judge_error}); break;
      case 'L': moves.push_back(Vec2{-1,0,judge_error}); break;
      default:{
        cout<<"Character '"<<i<<"' is not allowed in the input"<<endl;
        return judge_error;
      }
    }
  }

  // Read canonical answer.
  string canonical_answer;
  if (not (canonical_output>>canonical_answer)){
    cout<<"Canonical output is empty"<<endl;
    return judge_error;
  }
  transform(
      canonical_answer.begin(),
      canonical_answer.end(),
      canonical_answer.begin(),
      ::tolower);
  bool const is_impossible=(canonical_answer=="impossible");
  DBG(cerr<<"finished reading canonical answer"<<endl;)

  // Read team answer.
  string team_answer;
  if (not (team_output>>team_answer)){
    cout<<"Team failed to print anything"<<endl;
    return wrong_answer;
  }
  transform(
      team_answer.begin(),
      team_answer.end(),
      team_answer.begin(),
      ::tolower);
  bool const team_impossible=(team_answer=="impossible");
  DBG(cerr<<"finished reading team answer"<<endl;)

  if (team_impossible){
    // Team thinks the case is impossible.
    char dummy;
    if (team_output >> dummy) {
      cout<<"trailing output after impossible"<<endl;
      return wrong_answer;
    }
    if (is_impossible){
      cout<<"OK team agrees case is impossible"<<endl;
      return correct;
    }else{
      // Check that it is actually possible.
      if (validate_solution("canonical",canonical_output,canonical_answer,moves,judge_error)){
        return wrong_answer;
      }else{
        cout<<"Team found no solution, and judge solution is incorrect"<<endl;
        return judge_error;
      }
    }
  }else{
    // Team thinks the case is possible.
    if (validate_solution("team",team_output,team_answer,moves,wrong_answer)){
      if (not is_impossible){
        return correct;
      }else{
        cout<<"Team found a solution, but judge data says there is no solution"<<endl;
        return judge_error;
      }
    }else{
      cout<<"Wrong answer"<<endl;
      return wrong_answer;
    }
  }

  // Not supposed to happen.
  cout<<"Output validator failed to print a verdict"<<endl;
  return judge_error;
}
