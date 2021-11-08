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

const int N=1<<18,P=998244353;

int n,k;
char s[N];
typedef vector <int> V;
int w[N],I[N+1],J[N+1];
ll qpow(ll x,ll k=P-2){
	ll res=1;
	for(;k;k>>=1,x=x*x%P) if(k&1) res=res*x%P;
	return res;
}
void Init(){
	rep(i,*J=1,N) J[i]=1ll*J[i-1]*i%P;
	I[N]=qpow(J[N]);
	drep(i,N,1) I[i-1]=1ll*I[i]*i%P;
	w[N/2]=1; ll t=qpow(3,(P-1)/N);
	rep(i,N/2+1,N-1) w[i]=w[i-1]*t%P;
	drep(i,N/2-1,N-1) w[i]=w[i<<1];
}

int rev[N];
int Init(int n){
	int R=1,c=-1;
	while(R<=n) R<<=1,c++;
	rep(i,0,R-1) rev[i]=(rev[i>>1]>>1)|((i&1)<<c);
	return R;
}
void NTT(int n,V &A,int f){
	static ull a[N];
	rep(i,0,n-1) a[rev[i]]=A[i];
	for(int i=1;i<n;i<<=1){
		int *e=w+i;
		for(int l=0;l<n;l+=i*2) {
			for(int j=l;j<l+i;++j) {
				int t=a[j+i]*e[j-l]%P;
				a[j+i]=a[j]+P-t;
				a[j]+=t;
			}
		}
	}
	rep(i,0,n-1) A[i]=a[i]%P;
	if(f==-1) {
		reverse(A.begin()+1,A.end());
		ll base=1ll*I[n]*J[n-1]%P;
		rep(i,0,n-1) A[i]=A[i]*base%P;
	}
}

int C(int n,int m){ return 1ll*J[n]*I[m]%P*I[n-m]%P; }

V operator * (V a,V b){
	int n=a.size()+b.size()-1,R=Init(n);
	a.resize(R),b.resize(R),NTT(R,a,1),NTT(R,b,1);
	rep(i,0,R-1) a[i]=1ll*a[i]*b[i]%P;
	NTT(R,a,-1),a.resize(n);
	return a;
}

int a[N],m,sum;
V Solve(int l,int r) {
	if(l==r) {
		V A(a[l]+1);
		int t=1;
		//cout<<"$"<<l<<' '<<a[l]<<endl;
		rep(i,0,a[l]) {
			if(i) t=1ll*t*(2*i-1)%P;
			A[i]=1ll*C(a[l]+i,i*2)*t%P*I[i]%P;
		}
		return A;
	}
	int mid=(l+r)>>1;
	return Solve(l,mid)*Solve(mid+1,r);
}

int main(){
	scanf("%d%d%s",&n,&k,s+1),Init();
	rep(i,1,n) if(s[i]=='1') {
		int j=i;
		while(s[j]=='1' || s[j+1]=='1') j++;
		sum+=a[++m]=(j-i+1)/2,i=j;
	}
	if(sum<k) return puts("0"),0;
	int res=1ll*Solve(1,m)[k]*J[k]%P;
	printf("%d\n",res);
}






