#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
template<class T>inline void MAX(T &x,T y){if(y>x)x=y;}
template<class T>inline void MIN(T &x,T y){if(y<x)x=y;}
template<class T>inline void rd(T &x){
	x=0;char o,f=1;
	while(o=getchar(),o<48)if(o==45)f=-f;
	do x=(x<<3)+(x<<1)+(o^48);
	while(o=getchar(),o>47);
	x*=f;
}
template<class T>inline void print(T x,bool op=1){
	static int top,stk[105];
	if(x<0)x=-x,putchar('-');
	if(x==0)putchar('0');
	while(x)stk[++top]=x%10,x/=10;
	while(top)putchar(stk[top--]+'0');
	putchar(op?'\n':' ');
}
const int M=1e7+5;
ll cas,n;
int dp[M];
void check(int &x,int y){
	if(x==-1||y<x)x=y;
}
signed main(){
#ifndef ONLINE_JUDGE
//	freopen("jiedai.in","r",stdin);
//	freopen("jiedai.out","w",stdout);
#endif
	memset(dp,-1,sizeof(dp));
	dp[0]=0;
	for(int i=0;i<M;i++)if(~dp[i]){
		if(i+7<M)check(dp[i+7],dp[i]+1);
		if(i+31<M)check(dp[i+31],dp[i]+1);
		if(i+365<M)check(dp[i+365],dp[i]+1);
	}
	rd(cas);
	while(cas--){
		rd(n);
		ll tmp=0;
		if(n>M)tmp=(n-M)/365+1,n-=tmp*365;
		print(tmp+dp[n]);
	}
	return (0-0);
}
