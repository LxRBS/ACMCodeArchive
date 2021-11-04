#include<bits/stdc++.h>
using namespace std;

const int mod=998244353;
int n,jc[100010],inv[100010],w[262147],p[262147],T,b[100010],c[100010];
vector<int> A,B;

int quickmi(int a,int b)
{
    int t=1;
    for (; b; b>>=1,a=1ll*a*a%mod)
        if (b&1) t=1ll*t*a%mod;
    return t;
}

void dft(vector<int> &A,int fl)
{
    int n=A.size(); p[0]=0;
    for (int i=1; i<n; i++)
        p[i]=(p[i>>1]>>1)|((i&1)?(n>>1):0);
    for (int i=0; i<n; i++)
        if (p[i]<i) swap(A[i],A[p[i]]);
    for (int i=1; i<n; i<<=1)
        for (int j=0; j<n; j+=(i<<1))
            for (int k=0; k<i; k++)
            {
                int t1=A[j+k],t2=1ll*w[i+k]*A[i+j+k]%mod;
                A[j+k]=(t1+t2>=mod?t1+t2-mod:t1+t2);
                A[i+j+k]=(t1<t2?t1-t2+mod:t1-t2);
            }
    if (fl==-1)
    {
        int inv=quickmi(n,mod-2);
        for (int i=0; i<n; i++) A[i]=1ll*A[i]*inv%mod;
        for (int i=1; i<(n>>1); i++) swap(A[i],A[n-i]);
    }
}

vector<int> mul(vector<int> A,vector<int> B)
{
    int nA=A.size(),nB=B.size(),L=1;
    for (; L<nA+nB-1; L<<=1);
    A.resize(L),B.resize(L),dft(A,1),dft(B,1);
    for (int i=0; i<L; i++) A[i]=1ll*A[i]*B[i]%mod;
    dft(A,-1),A.resize(nA+nB-1); return A;
}

vector<int> solve(int l,int r)
{
    if (l==r) {vector<int> A; A.push_back(c[l]),A.push_back(b[l]); return A;}
    int mid=(l+r)>>1; return mul(solve(l,mid),solve(mid+1,r));
}

int main()
{
    for (int i=0; i<18; i++)
    {
        int wn=quickmi(3,(mod-1)>>(i+1)); w[1<<i]=1;
        for (int j=(1<<i)+1; j<(1<<i+1); j++) w[j]=1ll*w[j-1]*wn%mod;
    }
    jc[0]=1;
    for (int i=1; i<=100000; i++) jc[i]=1ll*jc[i-1]*i%mod;
    inv[100000]=quickmi(jc[100000],mod-2);
    for (int i=100000; i; i--) inv[i-1]=1ll*inv[i]*i%mod;
    scanf("%d",&T);
    while (T--)
    {
        scanf("%d",&n),A.resize(n+1);
        for (int i=0; i<=n; i++) scanf("%d",&A[i]);
        for (int i=2; i<=n; i++) scanf("%d",&b[i]);
        for (int i=2; i<=n; i++) scanf("%d",&c[i]);
        B=solve(2,n);
        for (int i=0; i<=n; i++) A[i]=1ll*A[i]*jc[i]%mod;
        for (int i=0; i<=n-i; i++) swap(A[i],A[n-i]);
        A=mul(A,B);
        for (int i=0; i<=n-i; i++) swap(A[i],A[n-i]);
        for (int i=0; i<=n; i++) A[i]=1ll*A[i]*inv[i]%mod;
        for (int i=0; i<=n; i++) printf("%d%c",A[i],i==n?'\n':' ');
    }
    return 0;
}