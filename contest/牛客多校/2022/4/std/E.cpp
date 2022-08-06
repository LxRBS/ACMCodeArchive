#include <cstdio>
#include <iostream>
#include <unordered_map>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <climits>
#include <algorithm>
#include <complex>
#include <string.h>
#include <iomanip>
#include <assert.h>
#include <random>
using namespace std;
int cnt[405][405][405];
int a[1000001],b[1000001],c[1000001],id[1000001];
int ans;
const int mod=998244353;
struct node{
    int x,y;
    friend bool operator <(node a,node b){
        return a.x<b.x||a.x==b.x&&a.y<b.y;
    }
};
inline bool cmp2(int x,int y){
    return c[x]<c[y];
}
int main() {
    int T = 1, kase = 0;
    //cin >> T;
    while (T--) {
        int n,q;
        scanf("%d %d",&n,&q);
        for(int i=1,k;i<=n;i++){
            scanf("%d",&k);
            for(int j=1;j<=k;j++) scanf("%d%d%d",&a[j],&b[j],&c[j]),id[j]=j;
            sort(id+1,id+k+1,cmp2);
            set <node> s;
            for(int j=1;j<=k;j++){
                while(1){
                    auto it=s.lower_bound(node{a[id[j]],0});
                    if(it==s.end()) break;
                    if((*it).y>=b[id[j]]){
                        cnt[(*it).x][(*it).y][c[id[j]]]--;
                        int px=(*it).x,py=(*it).y,ex=0,ey=0;
                        if(it!=s.begin()){
                            --it;
                            cnt[px][(*it).y][c[id[j]]]++;
                            ey=(*it).y;
                            ++it;
                        }
                        ++it;
                        if(it!=s.end()){
                            cnt[(*it).x][py][c[id[j]]]++;
                            ex=(*it).x;
                        }
                        --it;
                        s.erase(it);
                        if(ex&&ey) cnt[ex][ey][c[id[j]]]--;
                    }
                    else break;
                }
                auto it=s.lower_bound(node{a[id[j]],INT_MAX/10});
                if(it!=s.begin()){
                    --it;
                    if((*it).y<=b[id[j]]) continue;
                    ++it;
                }
                int ex=0,ey=0;
                if(it!=s.end()) cnt[(*it).x][b[id[j]]][c[id[j]]]--,ex=(*it).x;
                if(it!=s.begin()){
                    --it;
                    cnt[a[id[j]]][(*it).y][c[id[j]]]--,ey=(*it).y;
                }
                if(ex&&ey) cnt[ex][ey][c[id[j]]]++;
                cnt[a[id[j]]][b[id[j]]][c[id[j]]]++;
                s.insert(node{a[id[j]],b[id[j]]});
            }
        }
        //cout<<"???????"<<endl;
        for(int i=1;i<=400;i++)
            for(int j=1;j<=400;j++)
                for(int k=1;k<=400;k++)
                    cnt[i][j][k]+=cnt[i][j][k-1];
        for(int i=1;i<=400;i++)
            for(int j=1;j<=400;j++)
                for(int k=1;k<=400;k++)
                    cnt[i][j][k]+=cnt[i][j-1][k];
        for(int i=1;i<=400;i++)
            for(int j=1;j<=400;j++)
                for(int k=1;k<=400;k++)
                    cnt[i][j][k]+=cnt[i-1][j][k];
        int lastans=0,seed;
        scanf("%d",&seed);
        std::mt19937 rng(seed);
        std::uniform_int_distribution<> u(1,400);
        for (int i=1;i<=q;i++)
        {
            int IQ=(u(rng)^lastans)%400+1;
            int EQ=(u(rng)^lastans)%400+1;
            int AQ=(u(rng)^lastans)%400+1;
            //cout<<IQ<<" "<<EQ<<" "<<AQ<<endl;
            ans=(1LL*ans*seed+cnt[IQ][EQ][AQ])%mod;
            lastans=cnt[IQ][EQ][AQ];
            assert(lastans>=0);
        }
        printf("%d\n",ans);
    }
    return 0;
}
//unordered_map贼勾八慢