#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn=3e5+5;
struct nod{
	int t,v;
}a[maxn];
int n;
int main() {
	scanf("%d",&n);
	for(int i=0;i<n;i++) scanf("%d%d",&a[i].t,&a[i].v);
	sort(a,a+n,[](nod l,nod r){return l.v*(2*r.t+1)>r.v*(2*l.t+1);});
	ll ans=0;
	int now=0;
	for(int i=0;i<n;i++) {
		ans+=1ll*a[i].v*(now+a[i].t+i);
		now+=a[i].t*2;
	}
	cout<<ans<<endl;
	return 0;
}