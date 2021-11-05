/**
    给定一个01串，问能否删除若干个不相邻的位置使得串变为(不严格)升序
*/
#include <bits/stdc++.h>
using namespace std;

#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define hash_t unordered_map

typedef pair<int,int> pii;
typedef vector<pii> vpii;

char A[110];
char B[2][12] = {"NO","YES"};

inline bool f(vpii const&v){
    for(auto pp:v){
		if(1!=pp.se) return false;
	}
    return true;
}
inline bool f(){
    vpii v0,v1;
	char *p = A;
    while(*p){
		if('0'==*p){
			v0.pb(mp(p-A,0));
			int k = 0;
			while('0'==*p) ++p,++k;
			(--v0.end())->se = k;
		}else if('1'==*p){
			v1.pb(mp(p-A,0));
			int k = 0;
			while('1'==*p)++p,++k;
			(--v1.end())->se = k;
		}
	}

    // cout<<"v0: ";
	// for(auto pp:v0)cout<<"("<<pp.fi<<", "<<pp.se<<")";
	// cout<<endl;
	// cout<<"v1: ";
	// for(auto pp:v1)cout<<"("<<pp.fi<<", "<<pp.se<<")";
	// cout<<endl;

	if(f(v0)||f(v1)) return true;

	if(v0.empty()||v1.empty()) return true;

	if(1==v0.size()&&0==v0.begin()->fi) return true;

    int k0 = v0.size()-1;
	while(k0>=0){
		if(v0[k0].se>1) break;
		--k0;
	}

    k0 = v0[k0].fi;
	for(auto pp:v1){
		if(pp.se>1&&pp.fi<k0) return false;
		if(pp.fi>k0) break;
	}
    return true;
}
int main(){
    // freopen("1.txt","r",stdin);
    // freopen("2.txt","w",stdout);
    int nofkase;
	scanf("%d",&nofkase);
	while(nofkase--){
		scanf("%s",A);
        puts(B[f()?1:0]);
	}
    return 0;
}
