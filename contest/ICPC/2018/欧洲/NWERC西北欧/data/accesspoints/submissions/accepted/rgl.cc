#include <bits/stdc++.h>
using namespace std;

struct Fraction{
  long long num;
  long long den;

  bool operator<(Fraction const &a)const{
    if ((num/den)!=(a.num/a.den)){
      return (num/den)<(a.num/a.den);
    }else{
      return (num%den)*a.den<(a.num%a.den)*den;
    }
  }
};

long double solve(vector<int> x){
  int const n=x.size();

  vector<long long> s(n+1);
  for (int i=0; i<n; i++)
    s[i+1]=s[i]+x[i];

  vector<Fraction> cx(n+1,Fraction{1000000,1});
  vector<int> ptr(n+1,-1);
  for (int i=n; i--;){
    cx[i]=min(cx[ptr[i]=i+1], Fraction{x[i],1});

    for (int j=ptr[i]; j!=-1; j=ptr[j])
      if (not (Fraction{x[i],1}<cx[j]) and not (Fraction{s[ptr[j]]-s[i],ptr[j]-i}<cx[j]))
        cx[i]=min(cx[ptr[j]], Fraction{s[ptr[j]]-s[i],ptr[j]-i}),
        ptr[i]=ptr[j];
      else
        break;
  }
  for (int i=1; i<n; i++)
    cx[i]=max(cx[i],cx[i-1]);

  double res=0.L;
  for (int i=n; i--;) res+=powl(x[i]-cx[i].num/(long double)cx[i].den,2);
  return res;
}

int main(){
  int n; cin>>n;
  vector<int> x(n),y(n);
  for (int i=0; i<n; i++) cin>>x[i]>>y[i];
  cout.precision(9);
  cout<<fixed<<solve(x)+solve(y)<<endl;
}
