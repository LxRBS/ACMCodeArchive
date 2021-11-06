#include<bits/stdc++.h>
#define dd(x) cerr<<#x<<" = "<<x<<" "
#define de(x) cerr<<#x<<" = "<<x<<endl
#define de_arr(a,s,t) cout<<#a<<": ";for (int z=(s);z<=(t);++z)cout<<a[z]<<" ";cout<<endl;
#define sz(x) int(x.size())
#define All(x) x.begin(),x.end()
#define pb push_back
#define mp make_pair
#define fi first
#define se second
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int,int> P;
const double eps=1e-8;
const int mod=1e9+7;
inline int sign(double x){return (x>eps)-(x<-eps);}
inline int add(int a,int b){a+=b;return a<0?a+mod:a>=mod?a-mod:a;}
inline int mul(ll a,ll b){return a*b%mod;}
const int maxn=5e3+10,INF=0x3f3f3f3f;
char s[maxn];
int f[maxn][maxn],cnt[maxn][maxn],pt[maxn];
ll ANS[maxn];
void calc_f(int n,int k){
    for (int st=2;st<=n;++st){
        int dif=0;
        for (int i=1,j=st,len=-1; j<=n; ++i,++j,--len){
            while (i+len+1<=n&&j+len+1<=n&&dif<=k){
                len++; 
                dif+=s[i+len]!=s[j+len];
            }
            f[i][j]=len+(dif<=k);
            dif-=s[i]!=s[j];
        }
    }
}
void solve(int n){
    for (int i=0;i<=n;++i){
        pt[i]=n/2+1;
        for (int j=0;j<=n;++j)
            cnt[i][j]=0;
    }
    ll ans=0;
    for (int j=n;j>1;--j){
        //update
        for (int i=1;i<j;++i)
            while (pt[i]>j-i){
                ans-=cnt[i][pt[i]];
                cnt[i][pt[i]-1]+=cnt[i][pt[i]];
                pt[i]--;
            }
        //add
        for (int i=1;i<j;++i){
            int len=min(f[i][j],j-i);
            cnt[i][len]++;
            ans+=len;
        }
        ANS[j]=ans;
        //delete
        while (pt[j-1]>=0){
            ans-=ll(cnt[j-1][pt[j-1]])*pt[j-1];
            pt[j-1]--;
        }
    }
}
int main()
{
    int T;
    cin>>T;
    while (T--){
        int n,k;
        scanf("%d%d%s",&n,&k,s+1);
        calc_f(n,k);
        solve(n);
        for (int i=2;i<=n;++i)
            printf("%d\n",ANS[i]);
    }
    return 0;
}
 