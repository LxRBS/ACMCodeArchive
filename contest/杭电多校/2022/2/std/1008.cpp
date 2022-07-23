#include<bits/stdc++.h>
using namespace std;
#define mem(a) memset(a,0,sizeof(a))
#define INF (~(1<<31))
#define inf 0x3f3f3f3f3f3f3f3f
#define eps 1e-8
#define PI 3.141592653589793238462643383
#define lowbit(x) ((x)&(-x))
#define sqr(x) ((x)*(x))
#define pb(x) emplace_back(x)
#define pf(x) push_front(x)
#define all(v) (v).begin(),(v).end()
#define dbg(x,y) cout<<(x)<<" = "<<(y)<< endl;
#define per(i,a,b) for(int i = a; i >= b; --i)
#define rep(i,a,b) for(int i = a; i <= b; ++i)
#define fi first
#define se second
#define ls (rt<<1)
#define rs (rt<<1|1)
#define ll long long
#define int ll
#define __int128 int
typedef bitset<1000010> bt;
typedef unsigned long long ull;
typedef complex<double> comp;
typedef pair<int,int> pii;
typedef pair<double,double> pdd;

const ll N = 2e5 + 7;
const ll M = 1e5 + 7;
const ll MAXN = 4e18 + 7;
const ll Mod = 998244353;
//const ll Mod = 1e9 + 7;

int _,i,j,k,n,m,p,q,s,T,t,l,r,o,u,v,w,x,y,z,ans,sum,num,len,en,sx,sy,tx,ty,th,ma,mi,mod,cnt,la,op,res,flag,cas,bk,ret,mid,now,tmp,rt;
int a[N],b[N],c[N],d[N];
char ch[N],ss;
vector<int> h;
string s1,s2,s3,s4;

pair<char,int> e[N];
ull csl[N],f[N];

signed main()
{
    int T = 1;
    scanf("%lld",&T);
    while(T--){
        scanf("%lld%lld%s",&n,&m,ch+1);
        ans=-1;
        for(i = 1;i < n;++i) if(ch[i]!=ch[i+1]) ++ans;
        ull base = 23333333333,hs=0,key=0,base2=base*base;
        csl[0]=1;
        for(i = 1;i < N;++i) csl[i]=csl[i-1]*base2;
        int tail=1;
        for(i = n-1;i >= 1&&ch[i]==ch[i+1];--i,++tail);
        for(int _ = 0;_ < ans;++_){
            ull s=1;
            while(ch[i]==ch[i-1]) ++s,--i;
            key*=base2;
            key+=ch[i]*base+s;
            //dbg(ch[i],s)
            --i;
        }
        int head=i;
        flag=0;
        p=0;
        for(i = 1;i <= m;++i){
            getchar();
            scanf("%c%lld",&ss,&x);
            if(x==0) continue;
            if(ss=='-'){
                while(p&&x){
                    if(e[p].se<=x) x-=e[p--].se;
                    else e[p].se-=x,x=0;
                }
            }
            else if(!p||e[p].fi!=ss) e[++p]=make_pair(ss,x);
            else e[p].se+=x;
            if(p) f[p]=f[p-1]+(e[p].fi*base+e[p].se)*csl[p];
            if(ans==-1&&e[p].fi==ch[1]&&e[p].se>=n) flag=1;
            if(ans!=-1&&p-1-ans>=1&&e[p].fi==ch[n]&&e[p].se>=tail&&
               key*csl[p-ans]==f[p-1]-f[p-1-ans]&&
               e[p-1-ans].fi==ch[1]&&e[p-1-ans].se>=head) flag=1;
        }
        printf("%s\n",flag? "yes":"no");
    }
    return 0;
}