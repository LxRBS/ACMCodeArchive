#include<bits/stdc++.h>
#define pb push_back
using namespace std;
const int N=1e5+50;
int n,t,a[N],b[N],mx,dat[N][20],ans;long long g[N][20];
struct node{
  int x,cos;
};
vector<node>v[N];
int main(){
	scanf("%d",&t);
	while (t--)
	{
		ans=1e9;
		mx=0;
  scanf("%d",&n);
  for(int i=1,x;i<=n;i++){
    scanf("%d",&a[i]);mx=max(mx,a[i]);
  }
  memset(dat,0,sizeof(dat));
  for(int i=1;i<=n;i++){
  	v[i].clear();
    b[0]=a[i];int mn=0;
    for(int j=1;b[j-1];j++){
      b[j]=b[j-1]/2;mn=j-1;
    }
    v[i].pb((node){0,mn+1});
    for(int j=mn;b[mn]<=mx;j--)
      for(int k=mn-j;k>=max(0,-j);k--){
        if (b[j+k]<=mx) v[i].pb((node){b[j+k],k+j+k}),b[j+k]*=2;
        if(b[j+k]>mx&&!dat[i][j+k])
          dat[i][j+k]=b[j+k],g[i][j+k]=k+j+k+1;
      }
  }
  for(int i=n-1;i;i--)
    for(int j=0;dat[i][j];j++){
      long long dd=1e18;
      for(int k=0;dat[i+1][k];k++)
        dd=min(dd,g[i+1][k]+(dat[i+1][k]<dat[i][j]?n-i:0));
      g[i][j]+=dd;
    }
  for(int i=2;i<=n;i++){
    int k=0;int mn=v[i-1][0].cos;
    for(int j=0;j<v[i].size();j++){
      while(k+1<v[i-1].size()&&v[i-1][k+1].x<=v[i][j].x)
        mn=min(mn,v[i-1][++k].cos);
      v[i][j].cos+=mn;
    }
    while(k+1<v[i-1].size()&&v[i-1][k+1].x<=mx)mn=min(mn,v[i-1][++k].cos);
    for(int j=0;dat[i][j];j++){
      ans=min(1ll*ans,mn+g[i][j]);
    }
  }
  for(int i=0;i<v[n].size();i++)
    ans=min(ans,v[n][i].cos);
  cout<<ans<<endl;
}
  return 0;
}
