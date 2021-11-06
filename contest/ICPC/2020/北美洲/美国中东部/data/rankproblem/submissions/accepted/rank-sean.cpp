#include <iostream>
#include <vector>

using namespace std;

int Find(const vector<int>& v, int key){
  for(int i = 0; i < v.size(); i++)
    if(v[i] == key)
      return i;
  return -1;
}

int main(){
  int n, m;
  cin >> n >> m;
  vector<int> rankings(n);

  for(int i = 0; i < n; i++)
    rankings[i] = i;

  for(int i = 0; i < m; i++){
    char t;
    int t1;
    int t2;
    cin >> t >> t1 >> t >> t2;
    t1--;
    t2--;
    int t1_pos = Find(rankings, t1);
    int t2_pos = Find(rankings, t2);
    if(t2_pos < t1_pos){
      for(int j = t2_pos; j < t1_pos; j++)
	rankings[j] = rankings[j+1];
      rankings[t1_pos] = t2;
    }
  }
  for(int i = 0; i < rankings.size(); i++){
    cout << "T" << rankings[i]+1 << " ";
  }
  cout << endl;

  return 0;
}
