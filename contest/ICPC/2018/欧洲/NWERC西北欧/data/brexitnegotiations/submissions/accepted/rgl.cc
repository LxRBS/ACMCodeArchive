#include <bits/stdc++.h>
using namespace std;


int main(){
  int n; cin>>n;
  vector<int> size(n);
  vector<vector<int>> edge(n);
  vector<int> indeg(n);
  //V+E
  for (int i=0,d; i<n; i++){
    cin>>size[i]>>d;
    for (int j=0; j<d; j++){
        int x; cin>>x; --x; edge[i].push_back(x); ++indeg[x];
    }
    ++indeg[i];
  }

  vector<int> by_size(n); for (int i=n; i--;) by_size[i]=i;
  //V log V
  sort(by_size.begin(),by_size.end(),[&size](int a,int b){return size[a]<size[b];});

  int lef=-1;
  //30 ~= 2 * log W
  for (int rad=(1<<30); rad; rad>>=1){
    int mid=(lef+rad);
    vector<int> deps=indeg;

    vector<int> todo;
    //V+E
    for (int i=0,j=0; i<n; i++){
      while (j<n and size[by_size[j]]+(n-1-i)<=mid){
        if (not --deps[by_size[j]]){
          todo.push_back(by_size[j]);
        }
        ++j;
      }
      if (i==todo.size()){
        break;
      }
      for (int y: edge[todo[i]]){
        if (not --deps[y]){
          todo.push_back(y);
        }
      }
    }

    if (todo.size()<n){
      lef=mid;
    }
  }

  cout<<lef+1<<endl;
}
