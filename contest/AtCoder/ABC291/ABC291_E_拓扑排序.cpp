/**
 * 有一个N长度排列未知。现在给定M对偏序关系，问根据M对关系是否能唯一确定该排列
 * 做一个拓扑排序，用队列进行成批扩展。每批有且只有一个节点。
 * 最后如果所有节点都入过队。则入队顺序就是排列。
 */
#include <bits/stdc++.h>
using namespace std;

#include <bits/extc++.h>
using namespace __gnu_pbds;

char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)
 

int getInt(){
	int sgn = 1;
	char ch = __hv007();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = __hv007();
	if ( '-' == ch ) {sgn = 0;ch=__hv007();}
 
	int ret = (int)(ch-'0');
	while( '0' <= (ch=__hv007()) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return sgn ? ret : -ret;
}



#ifndef ONLINE_JUDGE
int const SIZE = 21;
#else
int const SIZE = 2e5+5;
#endif

using llt = long long;
using vi = vector<int>;
using vll =vector<llt>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vpii = vector<pii>;

llt const MOD = 998244353LL;

int N, M;
vpii A;
vector<set<int>> G, IG;
vi Deg;
vi Ans;

bool proc(){
    G.assign(N+1, set<int>());
	IG.assign(N+1, set<int>());
	Deg.assign(N + 1, 0);
	for(const auto & p : A){
		G[p.first].insert(p.second);
		IG[p.second].insert(p.first);
	}

    queue<int> q;
	for(int i=1;i<=N;++i){
		Deg[i] = IG[i].size();
		if(0 == Deg[i]){
            q.push(i);
		}
	}

    Ans.clear(); Ans.reserve(N);
	int sz = 0;
	while(sz = q.size()){
		int k = sz;
		if(k != 1) return false;
		while(sz--){
			auto h = q.front(); q.pop();
			Ans.push_back(h);
			for(int i : G[h]){
				if(0 == --Deg[i]){
					q.push(i);
				}
			}
		}
	}
	return true;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	// int nofkase; cin >> nofkase;
    N = getInt(); M = getInt();
	A.assign(M, {});
	for(auto & p : A) p.first = getInt(), p.second = getInt();
	bool b = proc();
	if(b && Ans.size() == N){
		printf("Yes\n");
		vi p(N + 1, 0);
		for(int i=0;i<N;++i){
			p[Ans[i]] = i + 1;
		}
		for(int i=1;i<=N;++i)printf("%d ", p[i]);
		printf("\n");
	}else{
		printf("No\n");
	}
    return 0; 
}