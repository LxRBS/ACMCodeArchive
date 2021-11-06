#include <iostream>
#include <vector>

using namespace std;


int Solve_Helper(int height, int pallets, vector<vector<int> >& memo){
  // cout << "pallets = " << pallets << "; height = " << height << endl;
  if(pallets == 1)
    return height;
  if(height <= 1)
    return height;
 
  if(memo[height][pallets] != -1)
    return memo[height][pallets];
  int min_exp = 50000;
  for(int i = 1; i <= height; i++){
    int cur = max(Solve_Helper(i-1, pallets-1, memo), Solve_Helper(height-i, pallets, memo)) + 1;
    if(cur < min_exp)
      min_exp = cur;
  }
  memo[height][pallets] = min_exp;
  //cout << "Solve_Helper(" << height << "," << pallets << ") = " << min_exp << endl;
  return min_exp;
}

		  
  


int Solve(int height, int pallets, vector<vector<int> >& memo, vector<int>& ties){
  int min_exp = 50000;
  
  ties.push_back(1);  // in case base case triggers
   if(pallets == 1)
    return height;
  if(pallets == 0)
    return 0;
  if(height == 0)
    return 0;
  if(height == 1)
    return 1;
  for(int i = 1; i <= height; i++){
    int num_exp = max(Solve_Helper(i-1, pallets-1, memo), Solve_Helper(height-i, pallets, memo)) + 1;
    if(num_exp < min_exp){
      min_exp = num_exp;
      ties.resize(1);
      ties[0] = i;
    }
    else if(num_exp == min_exp){
      ties.push_back(i);

    }
  }
 
  return min_exp;
}
      
int main(){
  int n, m;
  cin >> n >> m;
  vector<vector<int> > memo(n+1);

  
  for(int i = 0; i <= n; i++)
    memo[i].resize(m+1, -1);

  vector<int> ties;
  int num_exp = Solve(n, m, memo, ties);
  cout << num_exp << " ";
  if(ties.size() == 1)
    cout << ties[0] << endl;
  else
    cout << ties[0] << "-" << ties[ties.size()-1] << endl;

  return 0;
}
