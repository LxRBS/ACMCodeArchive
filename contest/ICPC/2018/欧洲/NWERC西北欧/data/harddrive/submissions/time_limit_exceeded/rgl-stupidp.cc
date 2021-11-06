#include <bits/stdc++.h>
using namespace std;

static bool broken[1<<20];
static bool dp[2][1<<20];

int main(){
  ios::sync_with_stdio(false);
  int n,c,b; cin>>n>>c>>b;
  while (b--) {int x; cin>>x; broken[x-1]=true;}
  dp[0][0]=dp[1][0]=1;

  // dynamic programming
  for (int i=0; i<n; i++){
    for (int j=min(i,c); j>=0; --j){
      if (broken[i]){
        dp[0][j]=dp[1][j-1];
      }else{
        dp[1][j]=dp[0][j-1] or dp[1][j];
        dp[0][j]=dp[1][j-1] or dp[0][j];
      }
    }
  }

  // assert that we have a solution
  if (not dp[0][c] and not dp[1][c]){
    cout<<"impossible\n";
    return 0;
  }

  // "backtracking"
  string res="";
  for (int i=0; i<n; i++) res+=("01"[i==0? c%2: not broken[i]]);
  for (int i=1; i<n; i++) c-=(res[i]!=res[i-1]);
  for (int i=n-1; i-->1;) if (res[i]=='1' and not broken[i] and c<=-2) {res[i]='0'; if (res[i-1]=='0' and res[i+1]=='0') c+=2;}
  for (int i=n-1; i-->1;) if (res[i]=='1' and not broken[i] and c>=+2 and res[i-1]=='1' and res[i+1]=='1'){res[i]='0'; c-=2;}
  cout<<res<<endl;
}
