#include <bits/stdc++.h>
using namespace std;

int main(){
  ios::sync_with_stdio(false);
  int n; cin>>n;
  vector<int> v(n); for (auto &i: v) cin>>i;
  for (int i=n; i-->1;){
    bool sorted=true;
    for (int j=n-1; j--;){
      if (v[j+1]<v[j]){
        swap(v[j+1],v[j]);
        sorted=false;
      }
    }
    if (sorted) break;
  }
  long double res=1.L;
  for (int i=n; i--;){
    if (v[i]>i+1){
      cout<<"impossible"<<endl;
      return 0;
    }else{
      res=min(res,v[i]/(i+1.L));
    }
  }

  cout.precision(16);
  cout<<res<<endl;
}
