#include<bits/stdc++.h>
#define N 2000009
using namespace std;
typedef long long ll;
const int mod=998244353;
int n,k,z[N],tag[N];
char s[N];
inline void MOD(ll &x){x=x>=mod?x-mod:x;}
inline ll power(ll x,ll y){
	ll ans=1;
	while(y){
		if(y&1)ans=ans*x%mod;
		x=x*x%mod;
		y>>=1;
	}
	return ans;
}
inline ll rd(){
	ll x=0;char c=getchar();bool f=0;
	while(!isdigit(c)){if(c=='-')f=1;c=getchar();}
	while(isdigit(c)){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
	return f?-x:x;
}
inline void solve(){
    scanf("%s",s+1);n=strlen(s+1);
    scanf("%d",&k);
    int l=0;
    for(int i=2;i<=n;++i){
		if(l+z[l]>i)z[i]=min(z[i-l+1],l+z[l]-i);
		while(i+z[i]<=n&&s[z[i]+1]==s[i+z[i]])z[i]++;
		if(i+z[i]>l+z[l])l=i;
    }
    z[1]=n;
    for(int i=0;i<n;++i){
    	int len=z[i+1];
    	if(len>=i+k){
    		len-=i;
    		len=(len/k)*k;
    		tag[2*i+k]++;
    		if(2*i+len+k<=n)tag[2*i+len+k]--;
		}
	}
	ll Ans=1;
	ll sum=0;
	for(int i=1;i<=n;++i){
		if(i+k<=n)tag[i+k]+=tag[i]; 
		Ans=Ans*(tag[i]+1)%mod;
		sum+=tag[i];
	}
	for(int i=0;i<=n;++i)z[i]=tag[i]=0;
	printf("%lld\n",Ans);
}
int main(){  
    int T;scanf("%d",&T);
	while(T--)solve(); 
    return 0;
}

