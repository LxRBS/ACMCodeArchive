#include <iostream>
#include <vector>

using namespace std;

void Print_Board(const vector<vector<int> >& Board){
  for(int i = 0; i < Board.size(); i++){
    for(int j = 0; j < Board.size(); j++){
      if(Board[i][j] != 0)
	cout << Board[i][j] << " ";
      else
	cout << "." << " ";
    }
    cout << endl;
  }
}

bool Can_Place(const vector<vector<int> >& Board, int r, int c, int val){
  if(Board[r][c] != 0)
     return false;
     
  
  for(int cur_c = 0; cur_c < Board.size(); cur_c++)
    if(Board[r][cur_c] == val)
      return false;

 
  for(int cur_r = 0; cur_r < Board.size(); cur_r++)
    if(Board[cur_r][c] == val)
      return false;

 
  for(int box_r = (r/3)*3; box_r < (r/3)*3 + 3; box_r++)
    for(int box_c = (c/3)*3; box_c < (c/3)*3 + 3; box_c++)
      if(Board[box_r][box_c] == val)
	return false;

  return true;
}

      

void Get_Possible_Values(const vector<vector<int> >& Board, int r, int c, vector<int>& possibles){
  possibles.resize(0);
  for(int val = 1; val <= Board.size(); val++){
    if(Can_Place(Board, r, c, val))
      possibles.push_back(val);
  }
}

bool Single_Value(vector<vector<int> >& Board){
  bool found = false;
  for(int i = 0; i < Board.size(); i++){
    for(int j = 0; j < Board[i].size(); j++){
      vector<int> possibles;
      Get_Possible_Values(Board, i, j, possibles);
      if(possibles.size()== 1){
	found = true;
	Board[i][j] = possibles[0];
      }
    }
  }
  return found;
}

bool Unique_Row(vector<vector<int> >& Board){
  bool found = false;
  for(int r = 0; r < Board.size(); r++){
    for(int val = 1; val <= Board.size(); val++){
      vector<int> places;
      for(int c = 0; c < Board.size(); c++)
	if(Can_Place(Board, r,c,val))
	  places.push_back(c);
      if(places.size() == 1){
	found = true;
	Board[r][places[0]] = val;
      }
    }
  }
  return found;
}

bool Unique_Col(vector<vector<int> >& Board){
  bool found = false;
  for(int c = 0; c < Board.size(); c++){
    for(int val = 1; val <= Board.size(); val++){
      vector<int> places;
      for(int r = 0; r < Board.size(); r++)
	if(Can_Place(Board, r, c, val)){
	  places.push_back(r);
	}
      if(places.size() == 1){
	found = true;
	Board[places[0]][c] = val;
      }
    }
  }
  return found;
}

bool Unique_Single_Box(vector<vector<int> >& Board, int r, int c){
  bool found = false;
  for(int val = 1; val <= Board.size(); val++){
    int num_found = 0;
    int found_r = -1;
    int found_c = -1;
    for(int cur_r = r; cur_r < r+3; cur_r++)
      for(int cur_c = c; cur_c < c+3; cur_c++)
	if(Can_Place(Board, cur_r, cur_c, val)){
	  num_found++;
	  found_r = cur_r;
	  found_c = cur_c;
	}
    if(num_found == 1){
      found = true;
      Board[found_r][found_c] = val;
    }
  }
  return found;
}

bool Unique_Box(vector<vector<int> >& Board){
  bool found = false;
  for(int r = 0;r < Board.size(); r = r+3)
    for(int c = 0; c < Board.size(); c = c+3)
      if(Unique_Single_Box(Board, r,c))
	found = true;
  return found;
}
	
bool Unique_Location(vector<vector<int> >& Board){
  return Unique_Row(Board) || Unique_Col(Board) || Unique_Box(Board);
}

bool Am_I_Solved(vector<vector<int> >& Board){
  for(int i = 0; i < Board.size(); i++)
    for(int j = 0; j < Board.size(); j++)
      if(Board[i][j] == 0)
	return false;
  return true;
}

int main(){
  vector<vector<int> > Board(9);
  for(int i = 0; i < 9; i++){
    Board[i].resize(9);
    for(int j = 0; j < 9; j++)
      cin >> Board[i][j];
  }

  bool progress = true;
  bool solved = false;
  while(!solved && progress){
    progress = false;
    bool cur = Single_Value(Board);
    // cout << "After single value pass: " << endl;
    // Print_Board(Board);
    if(cur)
      progress = true;
    cur = Unique_Location(Board);
    if(cur)
      progress = true;

    solved = Am_I_Solved(Board);
    // cout << "After unique location pass: " << endl;
    // Print_Board(Board);
    //cout << endl;
  }
  if(solved)
    cout << "Easy" << endl;
  else
    cout << "Not easy" << endl;
  Print_Board(Board);
  return 0;
}
