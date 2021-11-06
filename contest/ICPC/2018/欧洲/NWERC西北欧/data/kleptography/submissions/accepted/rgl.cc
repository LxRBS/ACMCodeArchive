#include <bits/stdc++.h>
using namespace std;

int main(){
  int n,m; cin>>n>>m;
  string p,c; cin>>p>>c; p=c.substr(0,m-n)+p;
  for (int i=m-n; i--;){
    p[i]=((c[i+n]-p[i+n]+26)%26)+'a';
  }
  cout<<p<<endl;
}
