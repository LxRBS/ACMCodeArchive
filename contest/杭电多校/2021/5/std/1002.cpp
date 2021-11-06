#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef pair<ll,ll> pii;
#define rep(i,x,y) for(int i=x;i<y;i++)
#define rept(i,x,y) for(int i=x;i<=y;i++)
#define all(x) x.begin(),x.end()
#define fi first
#define se second
#define mes(a,b) memset(a,b,sizeof a)
#define mp make_pair
#define pb push_back
#define dd(x) cout<<#x<<"="<<x<<" "
#define de(x) cout<<#x<<"="<<x<<"\n"
const int inf=0x3f3f3f3f;
const int maxn=500;
const int mod=1e9+9;
ll x[maxn],y[maxn];
int p[maxn],q[maxn];

class matrix
{
    public:
        ll arrcy[maxn][maxn];//?????§³???¡À?0??row-1,0??column-1
        int row,column;//row??§µ?column???
        matrix()
        {
            memset(arrcy,0,sizeof arrcy);
            column=row=0;
        }
        friend matrix operator *(matrix s1,matrix s2)
        {
            int i,j;
            matrix s3;
            for (i=0;i<s1.row;i++)
            {
                for (j=0;j<s2.column;j++)
                {
                    for (int k=0;k<s1.column;k++)
                    {
                        s3.arrcy[i][j]+=s1.arrcy[i][k]*s2.arrcy[k][j];
                        s3.arrcy[i][j]%=mod;
                    }
                }
            }
            s3.row=s1.row;
            s3.column=s2.column;
            return s3;
        }
        void show()
        {
            for(int i=0;i<row;i++)
            {
                for (int j=0;j<column;j++)
                    cout<<arrcy[i][j]<<" ";
                cout<<"\n";
            }
        }
}mat1,mat2,mat3;

ll qpow(ll a,ll b)
{
    ll ans=1;
    for(;b;b>>=1,a=a*a%mod)
        if(b&1)
            ans=ans*a%mod;
    return ans;
}
/*
matrix quick_pow(matrix s1,long long n)
{
    matrix mul=s1,ans;
    ans.row=ans.column=s1.row;
    memset(ans.arrcy,0,sizeof ans.arrcy);
    for(int i=0;i<ans.row;i++)
        ans.arrcy[i][i]=1;
    while(n)
    {
        if(n&1) ans=ans*mul;
        mul=mul*mul;
        n/=2;
    }
    return ans;
}
*/


int g=13;

void solve()
{
    
    int k,n;
    ll l;
    cin>>k>>l>>n;
    k-=2;
    x[0]=1;
    g=qpow(13,(mod-1)/n);
    rept(i,1,n) x[i]=x[i-1]*g%mod;
    mat1.row=mat1.column=n;
    rep(i,0,n)
        rep(j,0,n)
            mat1.arrcy[i][j]=qpow(g,i*j);
//    mat1.show();
    mat3=mat1;
    rep(i,0,n) rep(j,i+1,n) swap(mat3.arrcy[i][j],mat3.arrcy[j][i]);
    mat2.row=mat2.column=n;
    rep(i,0,n) rep(j,0,n) mat2.arrcy[i][j]=qpow(x[i]+x[j]+k,l);
    //mat1.show();
    //mat2.show();
    //mat3.show();
    mat1=mat1*mat2;
    mat1=mat1*mat3;
    p[0]=q[0]=0;
    rep(i,1,n) p[i]=q[i]=n-i;
    ll nn=qpow(n*n,mod-2);
    rep(i,0,n)
    {
        rep(j,0,n)
        {
            cout<<mat1.arrcy[p[i]][q[j]]*nn%mod;
            if(j==n-1) cout<<"\n";
            else cout<<" ";
        }
    }
    return ;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    int T;
    cin>>T;
    while(T--)
        solve();
    return 0;
}
 