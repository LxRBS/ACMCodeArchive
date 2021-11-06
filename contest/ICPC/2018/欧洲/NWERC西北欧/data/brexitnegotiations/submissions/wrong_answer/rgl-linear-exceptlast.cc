#include <bits/stdc++.h>
using namespace std;

vector<int> size_bucket[10001];

int main(){
  int n; cin>>n;
  vector<int> size(n),deps(n);
  vector<vector<int>> edge(n);
  //V+E
  for (int i=0,d; i<n; i++){
    cin>>size[i]>>d;
    for (int j=0; j<d; j++){
        int x; cin>>x; --x; edge[i].push_back(x); ++deps[x];
    }
    size_bucket[size[i]].push_back(i);
    ++deps[i];
  }

  //W
  vector<int> by_size;
  for (auto i: size_bucket) for (auto j: i) by_size.push_back(j);

  int limit=0;
  vector<int> todo;
  //V+E
  for (int i=0,j=0; i<n; i++){
    for (;j<n and (i==todo.size() or size[by_size[j]]+(n-1-i)<=limit); ++j){
      if (not --deps[by_size[j]]){
        limit=max(limit,size[by_size[j]]+(n-1-i));
        todo.push_back(by_size[j]);
      }
    }
    for (int y: edge[todo[i]]){
      if (not --deps[y]){
        todo.push_back(y);
      }
    }
    if (i+2==n){
      break;
    }
  }

  cout<<limit<<endl;
}
