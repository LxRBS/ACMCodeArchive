#include<bits/stdc++.h>
#define eb emplace_back
using namespace std;
const int mod=998244353;
const int M=1e5+9;
int n,m,num;
int b[M],ans[M],inv[M];
int kp[M],g[M];
int mu[M],pri[M],vis[M],w[M];
int kpow(int x,int y,int rex=1){
	for(;y;y>>=1,x=1ll*x*x%mod)if(y&1)rex=1ll*rex*x%mod;
	return rex;
}
vector<int>v[M];
void work(){
	scanf("%d%d",&n,&m);
	kp[0]=1;
	for(int i=1;i<=n;++i){
		ans[i]=0;
		kp[i]=1ll*kp[i-1]*m%mod;
		g[i]=__gcd(i,m);
	}
	for(int i=1;i<=n;++i){
		for(auto o:v[i]){
			int x=1ll*kp[o-1]*g[i/o]%mod*inv[o]%mod;
			ans[i]=(ans[i]+1ll*x*w[i/o]%mod)%mod;
		}
	}
	for(int i=1;i<=n;++i)printf("%d%c",ans[i]," \n"[i==n]);
}
int main(){
	freopen("1.in","r",stdin);
	freopen("1.out","w",stdout);
	for(int i=1;i<M;++i){
		for(int j=i;j<M;j+=i){
			v[j].eb(i);
		}
	}
	inv[0]=inv[1]=1;
	for(int i=2;i<M;++i)inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;
	mu[1]=1;
	for(int i=2;i<M;++i){
		if(!vis[i])mu[i]=-1,pri[++num]=i;
		for(int j=1;j<=num&&1ll*pri[j]*i<M;++j){
			vis[pri[j]*i]=1;
			if(i%pri[j]==0){
				mu[i*pri[j]]=0;
				break;
			}
			mu[pri[j]*i]=-mu[i];
		}
	}
	for(int i=1;i<M;++i)mu[i]=(mu[i]+mod)%mod;
	for(int i=1;i<M;++i){
		for(auto o:v[i]){
			w[i]=(w[i]+1ll*mu[o]*inv[o]%mod)%mod;
		}
	}
	int T;
	scanf("%d",&T);
	while(T--)work();
	return 0;
}