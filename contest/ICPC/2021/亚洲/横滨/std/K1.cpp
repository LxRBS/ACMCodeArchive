#include<bits/stdc++.h>
#define double long double
#define P pair<double,int>
const double eps=1e-14;
using namespace std;
struct nod{
	int x,y;
	int vx,vy;
}a[1005];
int n,D;
double ans[1005];
bool vis[1005];
double dis2(double xx,double yy,double xxx,double yyy) {
	return (xx-xxx)*(xx-xxx)+(yy-yyy)*(yy-yyy);
}
double caldis(int u,int v,double t) {
	return dis2(a[u].x+t*a[u].vx,a[u].y+t*a[u].vy,a[v].x+t*a[v].vx,a[v].y+t*a[v].vy);
}
double cal(int u,int v,double st) {
	double l=st,r=1e9,mid;
	while(r-l>eps) {
		double mid1=(l+r)/2;
		double mid2=(mid1+r)/2;
		double d1=caldis(u,v,mid1);
		double d2=caldis(u,v,mid2);
		if(d1<d2) r=mid2;
		else l=mid1;
	}
	double tmp=caldis(u,v,r);
	if(tmp-D*D>1e-11) return 1e18;
	l=st;
	while(r-l>eps) {
		mid=(l+r)/2;
		double d=caldis(u,v,mid);
		if(d-D*D>1e-10) l=mid;
		else r=mid;
	}
	return l;
}
int main() {
	scanf("%d%d",&n,&D);
	for(int i=0;i<=n;i++) scanf("%d%d%d%d",&a[i].x,&a[i].y,&a[i].vx,&a[i].vy),ans[i]=1e18;
	ans[0]=0;
	priority_queue<P,vector<P>,greater<P> >q;
	q.push(P(0,0));
	while(!q.empty()) {
		P u=q.top();q.pop();
		if(vis[u.second]) continue;
		vis[u.second]=1;
		for(int i=1;i<=n;i++) {
			if(ans[i]<=u.first||i==u.second) continue;
			double t=cal(u.second,i,u.first);
			if(t<ans[i]) {
				ans[i]=t;
				q.push(P(t,i));
			}
		}
	}
	for(int i=1;i<=n;i++) {
		if(ans[i]==1e18) puts("-1");
		else printf("%.10Lf\n",ans[i]);
	}
	return 0;
}