#include <bits/stdc++.h>
using namespace std;

double solve(vector<int> x){
  int const n=x.size();

  double res=0.L;
  for (auto i: x) res+=powl(i,2);

  vector<double> s(n+1);
  for (int i=0; i<n; i++) s[i+1]=s[i]+x[i];

  vector<vector<double>> dp(n+1,vector<double>(n+1,1e60L));
  dp[0][0]=0;
  for (int i=1; i<=n; i++){
    for (int j=0; j<i; j++){
      for (int k=0; k<=j; k++){
        if (j==k or (s[i]-s[j])/(i-j)>=(s[j]-s[k])/(j-k)){
          dp[i][j]=min(dp[i][j],(double)(-powl(s[i]-s[j],2)/(i-j)+dp[j][k]));
        }
      }
    }
  }

  double best=1e60L;
  for (int i=n; i--;){
    best=min(best,dp[n][i]);
  }
  return res+best;
}

int main(){
  int n; cin>>n;
  vector<int> x(n),y(n);
  for (int i=0; i<n; i++){
    cin>>x[i]>>y[i];
  }
  cout.precision(6);
  cout<<fixed<<solve(x)+solve(y)<<endl;
}
