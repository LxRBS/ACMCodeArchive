#include <bits/stdc++.h>
using namespace std;

struct Group{
  double total;
  int n;

  Group operator+(Group const &o)const{return {total+o.total,n+o.n};}
  double get(){return total/n;}
};

double solve(vector<int> x){

  vector<Group> g;
  for (auto i: x){
    g.push_back(Group{(double)i,1});
    while (g.size()>=2 and g[g.size()-1].get()<=g[g.size()-2].get()){
      g[g.size()-2]=g[g.size()-2]+g[g.size()-1];
      g.pop_back();
    }
  }

  double res=0.0;
  int l=0;
  for (auto i: g){
    for (int j=l+i.n; j-->l;){
      res+=powl(i.get()-x[j],2);
    }
    l+=i.n;
  }
  return res;
}

int main(){
  int n; cin>>n;
  vector<int> x(n),y(n);
  for (int i=0; i<n; i++) cin>>x[i]>>y[i];
  cout.precision(7);
  cout<<fixed<<solve(x)+solve(y)<<endl;
}
