#include <bits/stdc++.h>
using namespace std;
#define rep(i,h,t) for (int i=h;i<=t;i++)
#define dep(i,t,h) for (int i=t;i>=h;i--)
#define ll long long
#define me(x) memset(x,0,sizeof(x))
#define IL inline
#define rint register int
inline ll rd(){
    ll x=0;char c=getchar();bool f=0;
    while(!isdigit(c)){if(c=='-')f=1;c=getchar();}
    while(isdigit(c)){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
    return f?-x:x;
}
char ss[1<<24],*A=ss,*B=ss;
IL char gc()
{
    return A==B&&(B=(A=ss)+fread(ss,1,1<<24,stdin),A==B)?EOF:*A++;
}
template<class T>void maxa(T &x,T y)
{
    if (y>x) x=y;
}
template<class T>void mina(T &x,T y)
{
    if (y<x) x=y;
}
template<class T>void read(T &x)
{
    int f=1,c; while (c=gc(),c<48||c>57) if (c=='-') f=-1; x=(c^48);
    while(c=gc(),c>47&&c<58) x=x*10+(c^48); x*=f;
}
const int mo=998244353;
ll fsp(int x,int y)
{
    if (y==1) return x;
    ll ans=fsp(x,y/2);
    ans=ans*ans%mo;
    if (y%2==1) ans=ans*x%mo;
    return ans;
}
struct cp {
    ll x,y;
    cp operator +(cp B)
    {
        return (cp){x+B.x,y+B.y};
    }
    cp operator -(cp B)
    {
        return (cp){x-B.x,y-B.y};
    }
    ll operator *(cp B)
    {
        return x*B.y-y*B.x;
    }
    int half() { return y < 0 || (y == 0 && x < 0); }
};
const int N=6e5;
const int G=3;
int f[N],g[N],n;
struct fft{
  int l,n,m;
  int a[N],b[N],inv[N];
  int C[N],D[N];
  fft()
  {
    inv[0]=inv[1]=1;
    rep(i,2,N-1) inv[i]=(1ll*inv[mo%i]*(mo-(mo/i)))%mo; 
  }
  IL void clear()
  {
      rep(i,0,n) a[i]=b[i]=0;
  }
  int ppr[N];
  inline void ntt_init(){
    int lg=0,x;
    for (x=1;x<=m;x*=2) lg++;
    n=x;
    ppr[0]=1;ppr[x]=fsp(31,1<<(21-lg));
    for(int i=x>>1;i;i>>=1) ppr[i]=1ll*ppr[i<<1]*ppr[i<<1]%mo;
    for(int i=1;i<x;i++) ppr[i]=1ll*ppr[i&(i-1)]*ppr[i&-i]%mo;
  }
  inline int del(const int x){
    return x>=mo?x-mo:x;
  }
  inline void DIF(int *f,const int x){
    int len,hl,uni,*s,*i,*w;
    for(len=x,hl=x>>1;hl;len=hl,hl>>=1){
        for(s=f,w=ppr;s!=f+x;s+=len,w++){
            for(i=s;i<s+hl;i++){
                uni=1ll**(i+hl)**w%mo;
                *(i+hl)=del(*i+mo-uni);
                *i=del(*i+uni);
            }
        }
    }
  }
  inline void DIT(int *f,const int x){
    int len,hl,uni,*s,*i,*w;
    for(len=2,hl=1;len<=x;hl=len,len<<=1){
        for(s=f,w=ppr;s!=f+x;s+=len,w++){
            for(i=s;i!=s+hl;i++){
                uni=*i;
                *i=del(uni+*(i+hl));
                *(i+hl)=1ll*(uni+mo-*(i+hl))**w%mo;
            }
        }
    }
    reverse(f+1,f+x);int invx=mo-(mo-1)/x;
    for(i=f;i!=f+x;i++) *i=1ll**i*invx%mo;
  }
  IL void getcj(int *A,int *B,int len)
  {
    m=len*2; ntt_init();
    for (int i=0;i<=len;i++) a[i]=(A[i]%mo+mo)%mo,b[i]=(B[i]%mo+mo)%mo;
    DIF(a,n); DIF(b,n);
    for(int i=0;i<n;i++) a[i]=1ll*a[i]*b[i]%mo;
    DIT(a,n);
    for (int i=0;i<=m;i++) B[i]=a[i];
    clear();
  }
  IL void getcj(int *C,int len)
  {
  //    for (int i=0;i<=len;i++) a[i]=(A[i]%mo+mo)%mo,b[i]=(B[i]%mo+mo)%mo;      
      m=len*2; ntt_init();
      rep(i,0,n) a[i]=(a[i]+mo)%mo,b[i]=(b[i]+mo)%mo;
      DIF(a,n); DIF(b,n);
      for (int i=0;i<n;i++) a[i]=1ll*a[i]*b[i]%mo;
      DIT(a,n);
      for (int i=0;i<n;i++) C[i]=a[i];
      clear();
  }
  IL void getinv(int *A,int *B,int len)
  {
    if (len==1) { B[0]=fsp(A[0],mo-2); return; }
    getinv(A,B,(len+1)>>1);
    m=len*2; ntt_init();
    for (int i=0;i<=len;i++) a[i]=A[i],b[i]=B[i];
    DIF(a,n); DIF(b,n);
    for (int i=0;i<n;i++) a[i]=1ll*a[i]*b[i]%mo*b[i]%mo;
    DIT(a,n);
    for (int i=0;i<=len;i++) B[i]=((2*B[i]-a[i])%mo+mo)%mo; 
    clear();
  }
  IL void getsqrt(int *A,int *B,int len)
  {
    int inv2=fsp(2,mo-2);
    if (len==1) {B[0]=sqrt(A[0]); return;}
    getsqrt(A,B,(len+1)>>1);
    int C[N]={};
    getinv(B,C,len);
    getcj(A,C,len);
    for (int i=0;i<=len;i++) B[i]=1ll*(C[i]+B[i])%mo*inv2%mo;
  }
  IL void getDao(int *a,int *b,int len)
  {
    for (int i=1;i<=len;i++) b[i-1]=1ll*i*a[i]%mo;
    b[len-1]=0;
  }
  IL void getjf(int *a,int *b,int len)
  {
    for (int i=0;i<=len;i++) b[i+1]=1ll*a[i]*inv[i+1]%mo;
    b[0]=0;
  }
  IL void getln(int *A,int *B,int len)
  {
  //  me(C); me(D);
    getDao(A,C,len);
    getinv(A,D,len);
    getcj(C,D,len);
    getjf(D,B,len);
    rep(i,0,len) C[i]=0,D[i]=0;
  }
  IL void getexp(int *A,int *B,int len)
  {
    if (len==1) {B[0]=1; return;}
    getexp(A,B,(len+1)>>1);
    int C[N];
    getln(B,C,len);
    for(int i=0;i<=len;i++) C[i]=((-C[i]+A[i])%mo+mo)%mo;
    C[0]=(C[0]+1)%mo;
    getcj(C,B,len);
  }
}F;
/*

f[i]=\sum f[j]*g[i-j]; 

*/
/*
int now[N];
void solve(int h,int t)
{
  if (h>=t) return; 
  if (t-h<=32)
  {
      rep(i,h,t)
        rep(j,h,i)
          f[i]=(f[i]+1ll*f[j]*g[i-j])%mo;
    return;
  }
  int mid=(h+t)/2;
  solve(h,mid);
  rep(i,h,mid) F.a[i-h]=f[i];
  rep(i,1,t-h) F.b[i]=g[i];
  F.getcj(now,(t-h+1));
  rep(i,mid+1,t) f[i]=(f[i]+now[i-h])%mo;
  solve(mid+1,t);
}
*/
int now[N],a[N],b[N],c[N],d[N],e[N];
ll jc[N],jc2[N];
/*
\prod (1+a[i]x) 
*/ 
void solve(int h,int t,int *a)
{
    if (h==t) return;
    int mid=(h+t)/2;
    solve(h,mid,a); solve(mid+1,t,a);
    rep(i,h,mid) F.a[i-h+1]=a[i];
    rep(i,mid+1,t) F.b[i-mid]=a[i];
    F.a[0]=F.b[0]=1;
    F.getcj(now,(mid-h+2));
    rep(i,h,t) a[i]=now[i-h+1];
}
int S(int x)
{
	return log2(max(1,x));
}
int js(int x)
{
	return x+S(S(S(x)));
}
const int N2=2e5+10;
int sum[N2],H[N2];
struct re{
	vector<int> a[3][3];
};
#define mid ((h+t)/2)
re solve(int h,int t)
{
	if (t-h+1<=6)
	{
		ll f[6][6][7];
		memset(f,0,sizeof(f));
		rep(i,h,t)
		{
			f[i-h][i-h][1]=H[i];
	    }
	    rep(tt,1,t-h+1)
	      rep(i,h,t)
	        rep(j,i,t)
	        {
	      	  int k=js(j)+1;
			  rep(p,k,t)
			  {
				(f[i-h][p-h][tt+1]+=f[i-h][j-h][tt]*H[p])%=mo;
		      }
	        }
	    re jl;
	    rep(i,0,2)
	      rep(j,0,2) jl.a[i][j].resize(t-h+3);
	    rep(tt,1,t-h+1)
	      rep(i,h,t)
	        rep(j,i,t)
	        {
	      	  (jl.a[min(i-h,2)][min(t-j,2)][tt]+=f[i-h][j-h][tt])%=mo;
	        }
	    jl.a[2][2][0]=1;
	    return jl;
	}
	re t1=solve(h,mid);
	re t2=solve(mid+1,t);
	re t3;
	rep(i,0,2)
	  rep(j,0,2) t3.a[i][j].resize(t-h+3);
	rep(i,0,2)
	  rep(j,0,2)
	    rep(i1,0,2)
	    {
	    	int k=max(js(mid-i1)-(mid-i1)-i1,0);
	    	int ttt=0;
	    	rep(i,0,t-h+5) a[i]=b[i]=0;
	    	rep(i2,k,2)
	    	{
	    		ttt=1;
	    		for (int q=0;q<t2.a[i2][j].size();q++)
	    		  (a[q]+=t2.a[i2][j][q])%=mo;
	    	}
	    	if(ttt)
	    	{
	    		for (int q=0;q<t1.a[i][i1].size();q++)
	    		  (b[q]+=t1.a[i][i1][q])%=mo;
	    		int gg1=0,gg2=0;
	    		dep(q,t-h+1,0) if (a[q]!=0) { gg1=q; break;}
	    		dep(q,t-h+1,0) if (b[q]!=0) { gg2=q; break;}
				F.getcj(a,b,max(gg1,gg2)+1);
				rep(q,0,t-h+1) (t3.a[i][j][q]+=b[q])%=mo;
	    	}
	    }
	return t3;
}
int main()
{
	ios::sync_with_stdio(false);
	int m;
	cin>>n>>m;
	rep(i,1,m) cin>>H[i];
	re now=solve(1,m);
	rep(i,0,2) 
	  rep(j,0,2)
	  {
	  	for (int k=0;k<now.a[i][j].size();k++)
	  	  (sum[k]+=now.a[i][j][k])%=mo;
      }
	sum[0]=-1;
	rep(i,1,n) sum[i]=(-sum[i]%mo+mo)%mo;
	F.getinv(sum,f,n+3);
	rep(i,0,n) if (i%2==0) f[i]=-f[i];
	cout<<(f[n]%mo+mo)%mo <<endl;
	return 0;
}
/*
100000 100000
*/
