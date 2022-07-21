#include<bits/stdc++.h>
#define M 2005
using namespace std;
int n,m,cnt,mark[400005];
long long ans;
struct pos{
    int x,y;
}P[M];
struct hzl{
    int s,a,b;
}A[M*M];
bool cmp(hzl a,hzl b){
    return a.s<b.s;
}
bitset<2005>s[M];
int main(){
    mark[1]=1;
    for(int i=2;i<=200000;i++){
        if(mark[i])continue;
        for(int j=i+i;j<=200000;j+=i)mark[j]=1;
    }
    int T;
    scanf("%d",&T);
    while(T--){
        ans=cnt=0;
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++)s[i].reset();
        for(int i=1;i<=n;i++)scanf("%d%d",&P[i].x,&P[i].y);
        for(int i=1;i<=n;i++)
            for(int j=i+1;j<=n;j++)
                A[++cnt]=(hzl){abs(P[i].x-P[j].x)+abs(P[i].y-P[j].y),i,j};
        sort(A+1,A+cnt+1,cmp);
        for(int i=1;i<=cnt;i++){
            if(!mark[A[i].s])ans+=(s[A[i].a]^s[A[i].b]).count();
            s[A[i].a][A[i].b]=1;
            s[A[i].b][A[i].a]=1;
        }
        printf("%lld\n",ans);
    }
    return 0;
}

