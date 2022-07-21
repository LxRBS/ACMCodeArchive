#include<bits/stdc++.h>
#define N 1000009
using namespace std;
typedef long long ll;
int x[N],y[N],n,a[N],b[N]; 
inline ll rd(){
	ll x=0;char c=getchar();bool f=0;
	while(!isdigit(c)){if(c=='-')f=1;c=getchar();}
	while(isdigit(c)){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
	return f?-x:x;
}
inline bool pd(int x,int y){
	if(x==0||y==0||x==y||x+y==0)return 1;
	return 0;
}
inline bool check(int xx,int yy){
	for(int i=1;i<=n;++i)if(!pd(xx-x[i],yy-y[i]))return 0;
	return 1;
}
inline bool ch(){
	int tag=1;
	for(int i=2;i<=n;++i){
		if(x[i]==x[1])continue;
		tag=0;
		if(check(x[1],y[i]))return 1;
		if(check(x[1],y[i]+(x[i]-x[1])))return 1;
		if(check(x[1],y[i]-(x[i]-x[1])))return 1;
		break;
    }
    if(tag)return 1;
    return 0;
}
int ps=0;
inline bool check(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i)scanf("%d%d",&a[i],&b[i]);
	for(int i=1;i<=n;++i)x[i]=a[i],y[i]=b[i];
	if(ch())return 1;
	for(int i=1;i<=n;++i)x[i]=b[i],y[i]=a[i];
	if(ch())return 1;
	for(int i=1;i<=n;++i)x[i]=a[i]+b[i],y[i]=a[i]-b[i];
	if(ch())return 1;
	for(int i=1;i<=n;++i)x[i]=a[i]-b[i],y[i]=a[i]+b[i];
	if(ch())return 1; 
    return 0;
}
int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		if(check())puts("YES");
		else puts("NO"); 
	} 
    return 0;
}

