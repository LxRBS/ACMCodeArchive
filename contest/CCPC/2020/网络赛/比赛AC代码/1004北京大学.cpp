#include<bits/stdc++.h>
using namespace std;

set<pair<int,int> > s;
int n,hd[500010],m,cnt,f[500010],T,R,B,d[500010],x,y;
struct node{int to,next;}e[500010],E[500010];
bool bo[500010],boo[500010];

int main()
{
    scanf("%d",&T);
    for (int TT=1; TT<=T; TT++)
    {
        scanf("%d%d%d%d",&n,&m,&R,&B),cnt=0;
        for (int i=1; i<=n; i++) bo[i]=1,hd[i]=0,d[i]=0,boo[i]=1;
        for (int i=1; i<=B; i++) scanf("%d",&x),bo[x]=0;
        for (int i=1; i<=n; i++) scanf("%d",&f[i]),f[i]=-f[i];
        for (int i=1; i<=m; i++)
        {
            scanf("%d%d",&x,&y),d[x]++;
            e[++cnt]=(node){x,hd[y]},hd[y]=cnt;
        }
        for (int i=1; i<=n; i++) s.insert(make_pair(f[i],i));
        while (!s.empty())
        {
            x=(*s.begin()).second,s.erase(s.begin()),boo[x]=0;
            for (int i=hd[x]; i; i=e[i].next) if (boo[e[i].to]){
                if (!bo[e[i].to]) s.erase(make_pair(f[e[i].to],e[i].to)),f[e[i].to]=f[x],s.insert(make_pair(f[e[i].to],e[i].to));
                else 
                {
                    d[e[i].to]--;
                    if (!d[e[i].to]) s.erase(make_pair(f[e[i].to],e[i].to)),f[e[i].to]=f[x],s.insert(make_pair(f[e[i].to],e[i].to));
                }}
        }
        printf("Case #%d:\n",TT);
        for (int i=1; i<=n; i++) printf("%d%c",-f[i],i==n?'\n':' ');
    }
    return 0;
}
