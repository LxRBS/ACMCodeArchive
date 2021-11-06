#include <iostream>
#include <vector>
#include <string>

using namespace std;

void Get_Next_Space(int r, int c, int dir, int& next_r, int& next_c){
  if(dir == 0){ // upper left
    next_r = r-1;
    next_c = c-1;
  }
  if(dir == 1) { //upper center
    next_r = r-1;
    next_c = c;
  }
  if(dir == 2) { // upper right
    next_r = r-1;
    next_c = c+1;
  }
  if(dir == 3) { // left
    next_r = r;
    next_c = c-1;
  }
  if(dir == 4){ // right
    next_r = r;
    next_c = c+1;
  }
  if(dir == 5){  // lower left
    next_r = r+1;
    next_c = c-1;
  }
  if(dir == 6){ // down
    next_r = r+1;
    next_c = c;
  }
  if(dir == 7){ // lower right
    next_r = r+1;
    next_c = c+1;
  }
}

bool On_Grid(const vector<vector<char> >& Grid, int r, int c){
  if(r < 0 || c < 0 || r >= Grid.size() || c >= Grid[r].size())
    return false;
  else
    return true;
}

// we just placed a letter at (r,c) and are looking in direction "dir" for
// the letter at word[pos]
bool Solve(const vector<vector<char> >& Grid, const string& word, int pos, int r, int c, int dir, int kinks_left, vector<vector<vector<vector<vector<int> > > > >& Memo){
  if(pos == word.size() && kinks_left == 0)
    return true;
  if(pos == word.size() && kinks_left != 0)
    return false;
  if(kinks_left < 0)
    return false;
  
  if(Memo[r][c][pos][kinks_left][dir] != -1)
    return Memo[r][c][pos][kinks_left][dir];
  bool solved = false;
  for(int i = 0; i < 8; i++){
    int next_r, next_c;
    Get_Next_Space(r,c,i, next_r, next_c);
    if(On_Grid(Grid, next_r, next_c) && Grid[next_r][next_c] == word[pos]){
      if(i == dir)
	solved = Solve(Grid, word, pos+1, next_r, next_c, i, kinks_left, Memo);
      else
	solved = Solve(Grid, word, pos+1, next_r, next_c, i, kinks_left-1, Memo);
      if(solved)
	i = 8;
    }
  }
  Memo[r][c][pos][kinks_left][dir] = solved;
  return solved;
}

int main(){
  int r, c;
  cin >> r >> c;
  vector<vector<char> > Grid(r);
  for(int i = 0; i < r; i++){
    Grid[i].resize(c);
    for(int j = 0; j < c; j++)
      cin >> Grid[i][j];
  }
  int kinks;
  cin >> kinks;
  string word;
  cin >> word;

  // row x column x position in word x kinks left x cur_direction.  Yeesh.
  vector<vector<vector<vector<vector<int> > > > >Memo(r);
  for(int i = 0; i < r; i++){
    Memo[i].resize(c);
    for(int j = 0; j < c; j++){
      Memo[i][j].resize(word.size());
      for(int k = 0; k < word.size(); k++){
	Memo[i][j][k].resize(kinks+2);
	for(int cur = 0; cur < kinks+2; cur++){
	  Memo[i][j][k][cur].resize(9, -1);
	}
      }
    }
  }
	
  bool can_solve = false;
  for(int i = 0; i < r; i++)
    for(int j = 0; j < c; j++)
      if(Grid[i][j] == word[0]){
	if(word.size() == 1 && kinks == 0)
	  can_solve = true;
	else
	//for(int dir = 0; dir < 7; dir++)
	  if(Solve(Grid, word, 1, i,j, 8, kinks+1, Memo))
	    can_solve = true;
      }
  if(can_solve)
    cout << "YES" << endl;
  else
    cout << "NO" << endl;
  return 0;
  
}  
