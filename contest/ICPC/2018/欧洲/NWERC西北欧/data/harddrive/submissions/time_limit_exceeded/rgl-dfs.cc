#include <bits/stdc++.h>
using namespace std;

static bool broken[1<<20];
int n;

string res;
void dfs(int i,int c){
  if (c<0){
    return;
  }
  if (i==n){
    if (c==0){cout<<res<<endl;exit(0);}
    return;
  }

  char options[2]={'0','1'};
  if (i and res[-1]==options[0]) swap(options[0],options[1]);
  if (rand()%2) swap(options[0],options[1]);

  for (char x: options){
    if (x=='1' and broken[i]) continue;
    res[i]=x;
    dfs(i+1,c-(i and x!=res[i-1]));
  }
}

int main(){
  ios::sync_with_stdio(false);
  int c,b; cin>>n>>c>>b;
  while (b--) {int x; cin>>x; broken[x-1]=true;}
  for (int i=0; i<n; i++) res+=("01"[i==0? c%2: not broken[i]]);
  dfs(0,c);
}
