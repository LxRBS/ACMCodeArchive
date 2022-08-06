#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<string>
#include<cctype>
#include<vector>
#include<queue>
#include<cmath>
using namespace std;
#define pause system("pause")
#define mem(a, b) memset(a, b, sizeof(a))
#define rep(i,a,b) for(int i=(a),__##i##__=(b);i<=__##i##__;i++)
#define dwn(i,a,b) for(int i=(a),__##i##__=(b);i>=__##i##__;i--)
#define pb push_back
#define mkpr make_pair
#define sz(x) ((int)x.size())
#define fi first
#define se second
typedef long long ll;
typedef unsigned long long ull;
template <typename T>
T read()
{
    T x=0;int f=1;char ch=getchar();
    while(ch!=EOF&&!isdigit(ch)) f=(ch=='-'?-1:1),ch=getchar();
    while (ch!=EOF&&isdigit(ch)) x=x*10+ch-'0',ch=getchar();
    return x*f;
}
#define rdi read<int>()
#define rdl read<ll>()
size_t rds(char *__s, bool _getspace = false)
{
    size_t len=0;char ch=getchar();
    while(ch!=EOF&&(ch=='\r'||ch=='\n'||(!_getspace&&isspace(ch))))ch=getchar();
    while(ch!=EOF&&(ch!='\r'&&ch!='\n'&&(_getspace||!isspace(ch))))__s[len++]=ch,ch=getchar();
    __s[len]='\0';
    return len;
}
#define rds_sp(str) rds(str,true)
char rdc(){char ch=getchar();while(isspace(ch))ch=getchar();return ch;}
const int N=100005;
int n;
ll a[N],d[80];
int main()
{
    rep(_,1,rdi)
    {
        mem(d,0);
        n=rdi;
        rep(i,1,n) a[i]=rdl;
        rep(i,1,n)
        {
            ll x=a[i];
            dwn(j,62,0)
            {
                if(x&(1ll<<j)) if(d[j]) x^=d[j];
                else {d[j]=x;break;}
            }
        }
        ll ans=0;
        dwn(i,62,0)
            ans=max(ans,ans^d[i]);
        printf("%lld\n",ans);
    }
    return 0;
}
