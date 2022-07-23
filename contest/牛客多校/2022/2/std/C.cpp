#include <cstdio>
#include <set>
#include <algorithm>
#define MN 100000

using std::max;
using std::min;
using std::set;

using ll = long long;

int n,a[MN+5];

void solve(){
	scanf("%d",&n);
	int xsum = 0;
	ll sum = 0;
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		xsum ^= a[i];
		sum += a[i];
	}
	if(xsum==0){
		set<int> s,t;
		for(int i=1;i<=n;i++){
			s.insert(a[i]^(a[i]-1));
		}
		for(int x:s){
			for(int i=1;i<=n;i++){
				if((a[i]^x)<a[i]&&(a[i]-(a[i]^x))>1){
					t.insert(x);
					break;
				}
			}
		}
		for(auto x:t) s.erase(x);
		int ansc = 0;
		for(int i=1;i<=n;i++){
			if(s.count(a[i]^(a[i]-1))){
				ansc++;
			}
		}
		printf("%lld %d\n",sum,ansc);
	}else{
		int maxRem = 0;
		int ansc = 0;
		for(int i=1;i<=n;i++){
			int vNext = (a[i]^xsum);
			if(vNext<a[i]){
				a[i] = a[i]-vNext;
				if(a[i]>maxRem){
					maxRem = a[i];
					ansc = 0;
				}
				if(a[i]==maxRem){
					ansc++;
				}
			}
		}
		printf("%lld %d\n",sum-maxRem+1,ansc);
	}
}

int main(){
	int T;
	scanf("%d",&T);
	while(T--) solve();
}
