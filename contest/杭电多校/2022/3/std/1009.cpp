#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
typedef pair<int,int>P;
const int N=100005;
int Case,n,k,i,j,t,ans,ql[N],qr[N],del[N];
P e[N];
priority_queue<P,vector<P>,greater<P> >q;
inline bool cmpl(int x,int y){return e[x].first<e[y].first;}
inline bool cmpr(int x,int y){return e[x].second<e[y].second;}
int main(){
  scanf("%d",&Case);
  while(Case--){
    scanf("%d%d",&n,&k);
    for(i=1;i<=n;i++){
      scanf("%d%d",&e[i].first,&e[i].second);
      ql[i]=i;
      qr[i]=i;
      del[i]=0;
    }
    sort(ql+1,ql+n+1,cmpl);
    sort(qr+1,qr+n+1,cmpr);
    for(ans=0,i=j=1;i<=n;i++){
      if(del[qr[i]])continue;
      while(j<=n&&e[ql[j]].first<=e[qr[i]].second){
        q.push(P(e[ql[j]].second,ql[j]));
        j++;
      }
      ans++;
      for(t=1;t<=k;t++){
        if(q.empty())break;
        del[q.top().second]=1;
        q.pop();
      }
    }
    printf("%d\n",ans);
  }
}