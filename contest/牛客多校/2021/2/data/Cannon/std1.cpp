#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef pair <int,int> Pii;
#define reg register
#define mp make_pair
#define pb push_back
#define Mod1(x) ((x>=P)&&(x-=P))
#define Mod2(x) ((x<0)&&(x+=P))
#define rep(i,a,b) for(int i=a,i##end=b;i<=i##end;++i)
#define drep(i,a,b) for(int i=a,i##end=b;i>=i##end;--i)
template <class T> inline void cmin(T &a,T b){ ((a>b)&&(a=b)); }
template <class T> inline void cmax(T &a,T b){ ((a<b)&&(a=b)); }

char IO;
template <class T=int> T rd(){
	T s=0; int f=0;
	while(!isdigit(IO=getchar())) f|=IO=='-';
	do s=(s<<1)+(s<<3)+(IO^'0');
	while(isdigit(IO=getchar()));
	return f?-s:s;
}

const int N=1e7+10,P=1e9+9;

int n,m;
int I[N],J[N],T[N];
int Pow[N];
ll qpow(ll x,ll k=P-2) {
	ll res=1;
	for(;k;k>>=1,x=x*x%P) if(k&1) res=res*x%P;
	return res;
}

int C(int n,int m){ return 1ll*J[n]*I[m]%P*I[n-m]%P; }
ll C2(int n,int m){ return 1ll*J[n]*I[m]%P*I[n-m]; }
int Div2(int n){ return ((n&1)?n+P:n)>>1;}

int x,y,s;
int SC(int n,int m){
	cmin(m,n);
	while(y<m) s=(s+C2(x,++y))%P;
	while(y>m) s=(s-C2(x,y--))%P;
	while(x<n) s=(s*2-C2(x++,y))%P;
	while(x>n) s=Div2((s+C2(--x,y))%P);
	return s;
}

void Solve1(){
	int ans=0;
	rep(i,0,n+m) {
		int res=1ll*J[n+m]*I[n+m-i]%P*Pow[i]%P;
		ans^=res;
	}
	printf("%d ",ans);
}
void Solve2(){
	int ans=0;
	x=y=0,s=1;
	drep(i,n-1,0) T[i]=-SC(n+m-i,n-i-1);
	x=y=0,s=1;
	int t=1ll*J[n]*J[m]%P;
	drep(i,n+m,0) {
		T[i]=(T[i]+SC(n+m-i,n)+2ll*P)*I[n+m-i]%P*t%P*Pow[i]%P;
		ans^=T[i];
	}
	printf("%d\n",ans);
}

int main(){
	n=rd()-2,m=rd()-2;
	rep(i,*J=1,N-1) J[i]=1ll*J[i-1]*i%P;
	I[N-1]=qpow(J[N-1]);
	drep(i,N-1,1) I[i-1]=1ll*I[i]*i%P;
	rep(i,*Pow=1,N-1) Pow[i]=Pow[i-1]*2,Mod1(Pow[i]);
	Solve1(),Solve2();
}




