#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void fup(vector<ll> &v,int x,ll y){
  for (int i=x; i<v.size(); i|=i+1) v[i]+=y;
}

ll fet(vector<ll> &v,int x){
  ll y=0;
  for (int i=x; i>=0; --(i&=i+1)) y+=v[i];
  return y;
}

int main(){
  int n; cin>>n;
  vector<ll> v(n); for (auto &i: v) cin>>i;
  sort(v.begin(),v.end());

  vector<ll> f(n);
  for (int i=0; i<n; i++) fup(f,i,v[i]), fup(f,i+1,-v[i]);

  set<int> breaks;
  for (int i=0; i<n; i++) if (i==0 or v[i]!=v[i-1]) breaks.insert(i);

  ll res=0;
  while (fet(f,n-2)<=fet(f,n-1)){
    ++res;

    auto const increase=[&f,&breaks](int a,int b){
      fup(f,a,+1);
      fup(f,b,-1);
      for (int z: {a,b}){
        if ((fet(f,z)!=fet(f,z-1))) breaks.insert(z); else breaks.erase(z);
      }
    };

    ll a=*breaks.rbegin();
    int group_start,group_end;

    if (n-a>1){
      group_start=a;
      group_end=n-1;
    }
    else{
      group_start=*++breaks.rbegin();
      group_end=a;
    }

    int group_mid=group_start+(group_end-group_start+1)/2;
    increase(0,group_start);
    if (group_mid!=group_end) increase(group_mid,group_end);
  }
  cout<<(res - 1)<<endl;
}
