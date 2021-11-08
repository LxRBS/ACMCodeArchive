#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rep(i,a,b) for(int i=a,i##end=b;i<=i##end;++i)
#define drep(i,a,b) for(int i=a,i##end=b;i>=i##end;--i)

char buf[200000],*p1,*p2;
#define getchar() (((p1==p2)&&(p2=(p1=buf)+fread(buf,1,200000,stdin))),*p1++)
char IO;
template <class T=int> T rd(){
	T s=0; int f=0;
	while(!isdigit(IO=getchar())) f|=IO=='-';
	do s=(s<<1)+(s<<3)+(IO^'0');
	while(isdigit(IO=getchar()));
	return f?-s:s;
}

const int N=1e5+10;
const ll INF=1e18;
bool Mbe;

int n,m;
int A[N];
int X[N],T1;
int Y[N],T2;
int S[N],G[N],T3;
int gcd(int a,int b) { return b==0?a:gcd(b,a%b); }

struct Node{
	ll mi;
	int c;
	Node(){ mi=INF,c=0; }
	Node operator + (const Node _) const {
		Node res; res.mi=min(mi,_.mi);
		res.c=(res.mi==mi)*c;
		res.c+=(res.mi==_.mi)*_.c;
		return res;
	}
	void operator += (const Node _) {
		if(_.mi<mi) *this=_;
		else if(_.mi==mi) c+=_.c;
	}
	void operator += (const ll x) { mi+=x; }
} s[N<<2];

ll t[N<<2];
int bit;
void Add(int p,ll x){ t[p]+=x,s[p]+=x; }
void Up(int p){ s[p]=s[p<<1]+s[p<<1|1];s[p]+=t[p]; }
void Add(int l,int r,ll x){
	//cout<<"Add "<<l<<' '<<r<<' '<<x<<endl;
	if(l==r) {
		s[l+=bit].c=1,Add(l,x);
		for(;l>1;) Up(l>>=1);
	} else {
		for(Add(l+=bit,x),Add(r+=bit,x);l^r^1;) {
			if(~l&1) Add(l^1,x);
			if(r&1) Add(r^1,x);
			Up(l>>=1),Up(r>>=1);
		}
		while(l>1) Up(l>>=1);
	}
}
Node Que(int l,int r){
	if(l==r) {
		Node res=s[l+=bit];
		for(;l>1;) res+=t[l>>=1];
		return res;
	} else {
		Node L=s[l+=bit],R=s[r+=bit];
		for(;l^r^1;) {
			if(~l&1) L+=s[l^1];
			if(r&1) R+=s[r^1];
			L+=t[l>>=1],R+=t[r>>=1];
		}
		L+=R;
		while(l>1) L+=t[l>>=1];
		return L;
	}
}
// segment tree , maintain { max - min + gcd * i }

bool Med;
int main(){
	fprintf(stderr,"%.2lf\n",(&Med-&Mbe)/1024./1024.0);
	rep(_,1,rd()) {
		ll ans=n=rd();
		for(bit=1;bit<=n;bit<<=1);
		rep(i,1,bit*2) s[i]=Node(),t[i]=0;
		T1=T2=T3=0;
		rep(i,1,n) {
			A[i]=rd();
			while(T1 && A[X[T1]]<=A[i]) Add(X[T1-1]+1,X[T1],-A[X[T1]]),T1--;
			while(T2 && A[Y[T2]]>=A[i]) Add(Y[T2-1]+1,Y[T2],A[Y[T2]]),T2--;
			Add(X[T1]+1,i,A[i]),X[++T1]=i;
			Add(Y[T2]+1,i,-A[i]),Y[++T2]=i;
			if(i==1) continue;
			int x=abs(A[i]-A[i-1]);
			G[++T3]=x,S[T3]=i-1;
			Add(i-1,i-1,1ll*x*(i-1)-INF);
			drep(i,T3-1,1) {
				if(G[i+1]%G[i]!=0) {
					int t=G[i];
					G[i]=gcd(G[i],G[i+1]);
					rep(j,S[i-1]+1,S[i]) Add(j,j,1ll*j*(G[i]-t));
				}
			}
			int t=T3; T3=0;
			rep(j,1,t) {
				if(G[j]!=G[j-1]) G[++T3]=G[j];
				S[T3]=S[j];
			}
			rep(j,1,T3) {
				Node t=Que(S[j-1]+1,S[j]);
				ans+=(t.mi==1ll*i*G[j])*t.c;
			}
		}
		printf("%lld\n",ans);
	}
}

