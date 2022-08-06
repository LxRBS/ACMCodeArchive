#include<cmath>
#include<queue>
#include<cstdio>
#include<cstring>
#include<assert.h>
#include<iostream>
#include<algorithm>
using namespace std;
#define LL long long
const int mod=998244353;
const int inv2=(mod+1)/2;
inline int mul(int a,int b){return 1ll*a*b%mod;}
inline int dec(int a,int b){return a>=b?a-b:a+mod-b;}
inline int add(int a,int b){return a+b>=mod?a+b-mod:a+b;}
inline int qkpow(int a,int b){
	int ans=1,base=a;
	while(b){
		if(b&1)ans=mul(ans,base);
		base=mul(base,base);
		b>>=1;
	}
	return ans;
}
namespace IO{
	const int sz=1<<22;
	char a[sz+5],b[sz+5],*p1=a,*p2=a,*t=b,p[105];
	inline char gc(){
		return p1==p2?(p2=(p1=a)+fread(a,1,sz,stdin),p1==p2?EOF:*p1++):*p1++;
	}
	template<class T> void gi(T& x){
		x=0; char c=gc();
		for(;c<'0'||c>'9';c=gc());
		for(;c>='0'&&c<='9';c=gc())
			x=x*10+(c-'0');
	}
	inline void flush(){fwrite(b,1,t-b,stdout),t=b; }
	inline void pc(char x){*t++=x; if(t-b==sz) flush(); }
	template<class T> void pi(T x,char c='\n'){
		if(x==0) pc('0'); int t=0;
		for(;x;x/=10) p[++t]=x%10+'0';
		for(;t;--t) pc(p[t]); pc(c);
	}
	struct F{~F(){flush();}}f; 
}
using IO::gi;
using IO::pi;
using IO::pc;
bool vis[1000005];
int T,n,m,ans,fac[1000005],P[1000005],pre[1000005],tr[1000005],t[2][1000005],nxt[1000005],s1[1000005],s2[1000005],s3[1000005],len,lef[1000005];
int lowbit(int x){return x&-x;}
void modify(int x,int y){
	while(x<=n)tr[x]+=y,x+=lowbit(x);
}
int query(int x){
	int s=0;
	while(x>0)s+=tr[x],x-=lowbit(x);
	return s;
}
void modify2(int op,int x,int y){
	while(x<=len)t[op][x]=add(t[op][x],y),x+=lowbit(x);
}
int query2(int x){
	int s1=0,s2=0,l=x;
	while(x>0)s1=add(s1,t[0][x]),s2=add(s2,t[1][x]),x-=lowbit(x);
	return dec(1ll*s1*l%mod,s2);
}
void solve(){
	len=0;
	fac[0]=1;
	for(int i=1;i<=n;i++)fac[i]=1ll*fac[i-1]*i%mod;
	int cnt=0;
	for(int i=1;i<=n;i++){
		cnt+=(!vis[i]);
		if(!vis[i])lef[++len]=i;
	}
	for(int i=1;i<=n;i++)pre[i]=pre[i-1]+(!vis[i]);
	for(int i=n;i>=1;i--)nxt[i]=nxt[i+1]+(!vis[i]);
	for(int i=2;i<=n;i++){
		if(!P[i]&&!P[i-1]){
			if(cnt>=2)ans=add(ans,1ll*fac[cnt-2]*cnt%mod*(cnt-1)%mod*inv2%mod); 
		}else if(!P[i]&&P[i-1]){
			if(cnt>=1)ans=add(ans,1ll*fac[cnt-1]*pre[P[i-1]]%mod);
		}else if(P[i]&&!P[i-1]){
			if(cnt-pre[P[i]]>=1)ans=add(ans,1ll*fac[cnt-1]*(cnt-pre[P[i]])%mod);
		}else if(P[i]&&P[i-1]&&P[i-1]>P[i])ans=add(ans,fac[cnt]); 
	}
	int Sum=0;
	for(int i=1;i<=n;i++)
		if(!vis[i]){
			if(cnt>=3){
				Sum=add(Sum,1ll*fac[cnt-3]*pre[i-1]%mod*(pre[i]-1)%mod);
				Sum=dec(Sum,1ll*fac[cnt-3]*pre[i]%mod*(nxt[i]-1)%mod);
			}
		}
	for(int i=1;i<=n;i++){
		s1[i]=s1[i-1];
		if(!vis[i])s1[i]=add(s1[i],pre[i]);
	}
	for(int i=n;i;i--){
		s2[i]=s2[i+1];
		if(!vis[i])s2[i]=add(s2[i],pre[i-1]);
	}
	for(int i=n;i>=1;i--){
		s3[i]=s3[i+1];
		if(!vis[i])s3[i]=add(s3[i],dec(pre[i],nxt[i]));
	}
	int now=0,ns=0;
	for(int i=3;i<=n;i++){
		if(P[i-2]){
			modify(P[i-2],1),ns=add(ns,s3[P[i-2]]);
			if(len>=1){
				int id=lower_bound(lef+1,lef+len+1,P[i-2])-lef;
				modify2(0,id,1);
				modify2(1,id,id-1);	
			}
		}
		else now++;
		if(!P[i]&&!P[i-1]){
			ans=add(ans,1ll*Sum*now%mod);
			if(cnt>=2)ans=add(ans,1ll*fac[cnt-2]*ns%mod);
		}else if(!P[i]&&P[i-1]){
			int x=query(P[i-1]);
			int id;
			if(len)id=upper_bound(lef+1,lef+len+1,P[i-1]-1)-lef-1;
			if(cnt>=1&&len)ans=dec(ans,1ll*fac[cnt-1]*query2(id)%mod);
			if(cnt>=2)ans=dec(ans,1ll*fac[cnt-2]*s1[P[i-1]-1]%mod*now%mod);
			if(cnt>=1)ans=add(ans,1ll*fac[cnt-1]*x%mod*pre[P[i-1]-1]%mod);
			if(cnt>=2)ans=add(ans,1ll*fac[cnt-2]*pre[P[i-1]-1]%mod*now%mod*pre[P[i-1]-1]%mod);
		}else if(P[i]&&!P[i-1]){
			int x=query(P[i]);
			int id;
			if(len)id=lower_bound(lef+1,lef+len+1,P[i]+1)-lef;
			if(cnt>=1&&len)ans=add(ans,1ll*fac[cnt-1]*dec(query2(len),query2(id-1))%mod);
			if(cnt>=2)ans=add(ans,1ll*fac[cnt-2]*s2[P[i]+1]%mod*now%mod);
			if(cnt>=1)ans=dec(ans,1ll*fac[cnt-1]*x%mod*nxt[P[i]+1]%mod);
			if(cnt>=2)ans=dec(ans,1ll*fac[cnt-2]*nxt[P[i]+1]%mod*now%mod*pre[P[i]]%mod);
		}else if(P[i]&&P[i-1]&&P[i-1]>P[i]){
			ans=add(ans,1ll*fac[cnt]*(query(P[i-1])-query(P[i]))%mod);
			if(cnt>=1)ans=add(ans,1ll*fac[cnt-1]*(pre[P[i-1]-1]-pre[P[i]])%mod*now%mod);
		} 
	}
} 
signed main(){
	gi(T);
	while(T--){
		ans=0;
		gi(n),gi(m);
		for(int i=1;i<=n;i++)P[i]=vis[i]=0;
		for(int i=0;i<=n+1;i++)pre[i]=nxt[i]=s1[i]=s2[i]=s3[i]=tr[i]=t[0][i]=t[1][i]=0;
		for(int i=1;i<=m;i++){
			int u,v;
			gi(u),gi(v);
			P[u]=v,vis[v]=1;
		}
		if(n==1){pi(0,'\n');continue;}
		solve(); 
		pi(ans,'\n');	
	}
	return 0;
}
