#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N=2e5+10;
int n,m,k;
int a[N],b[N];

struct node{
	int pos,id;
	node(int _p=0,int _i=0):pos(_p),id(_i){}
	bool operator <(const node&rhs)const{
		if(pos==rhs.pos) return id<rhs.id;
		return pos>rhs.pos;
	}
};
multiset<node>downa,downb,upa,upb;

int main(){
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=n;++i){
		scanf("%d%d",&a[i],&b[i]);
		if(a[i]>b[i]) downa.insert(node(a[i],i));
		else upb.insert(node(b[i],i));
	}
	ll ans=0;
	while(n){
		int mx=0;
		auto l=downa.begin(),r=upb.begin();
		if(l==downa.end()) mx=r->pos;
		else if(r==upb.end()) mx=l->pos;
		else mx=max(l->pos,r->pos);
		ans+=(mx-1)*2;

		for(int nowp=mx,cnt=0;;){
			while(cnt<m){
				auto t=upb.lower_bound(node(nowp,0));
				if(t==upb.end()) break;
				++cnt;--n;nowp=t->pos;
				upa.insert(node(a[t->id],t->id));
				upb.erase(t);
			}
			if(!upa.size()) break;
			auto t=upa.begin();
			nowp=t->pos;--cnt;
			upa.erase(t);
		}
		for(int nowp=mx,cnt=0;;){
			while(cnt<m){
				auto t=downa.lower_bound(node(nowp,0));
				if(t==downa.end()) break;
				++cnt;--n;nowp=t->pos;
				downb.insert(node(b[t->id],t->id));
				downa.erase(t);
			}
			if(!downb.size()) break;
			auto t=downb.begin();
			nowp=t->pos;--cnt;
			downb.erase(t);
		}
	}
	printf("%lld\n",ans);
	return 0;
}
/*
5 1 6
1 3
2 4
5 6
5 4
4 2

14
*/
