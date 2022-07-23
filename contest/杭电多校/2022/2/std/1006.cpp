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
const int M=105;
const int K=1005;
struct node{
	int a,b;
	double val;
	bool operator <(const node &A)const{
		return val<A.val;
	}
}book[M*M];
int cas,k,A,B;
double dp[K];

signed main(){
#ifndef ONLINE_JUDGE
//	freopen("jiedai.in","r",stdin);
//	freopen("jiedai.out","w",stdout);
#endif
	rd(cas);
	while(cas--){
		int tot=0;
		rd(k),rd(A),rd(B);
		for(int a=0;a<A;a++)for(int b=0;b<B;b++){
			tot++;
			book[tot].a=a;
			book[tot].b=b;
			if(a)book[tot].val=1.0*(A*b-a*b)/(a*B);
			else book[tot].val=1e9;
		}
		sort(book+1,book+1+tot);
		for(int i=1;i<=k;i++){
			double s1=0,s2=0;
			dp[i]=1e9;
			for(int j=1;j<=tot;j++){
				double a=1.0*book[j].a/A;
				double b=1.0*book[j].b/B;
				s1+=a+b-a*b;
				s2+=1-a;
				MIN(dp[i],(A*B+s1*dp[i-1])/(j-s2));
			}
		}
		printf("%.3lf\n",dp[k]);
	}
	return (0-0);
}
