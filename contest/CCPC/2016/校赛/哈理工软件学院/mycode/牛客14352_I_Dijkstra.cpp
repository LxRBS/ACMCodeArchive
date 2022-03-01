/**
    无向图，选三个点ABC，使得A到B到C的最短距离最大
    for B就行了
*/
#include <bits/stdc++.h>
using namespace std;

char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)

typedef long long llt;

llt getUnsigned(){
	char ch = __hv007();
	while( ch < '0' || ch > '9' ) ch = __hv007();

	llt ret = (llt)(ch-'0');
	while( '0' <= ( ch = __hv007() ) && ch <= '9' ) ret = (ret<<1) + (ret<<3) + (llt)(ch-'0');
	return ret;
}


#ifndef ONLINE_JUDGE
int const SIZE = 12;
#else
int const SIZE = 1010;
#endif

typedef pair<int, int> pii;
typedef vector<pii> vpii;
typedef priority_queue<pii, vpii, greater<pii> > _queue_t;
int const INF = 0x3FFFFFFF;

_queue_t Q;
int N, M;
vpii G[SIZE];
int D[SIZE];
bool Flag[SIZE];

int proc(int s){
	while(!Q.empty()) Q.pop();
    fill(D, D+N+1, INF);
    fill(Flag, Flag+N+1, false);

	D[s] = 0;
    Q.push({0, s});

	while(1){
		while(!Q.empty() && Flag[Q.top().second]) Q.pop();
		if(Q.empty()) break;

		auto h = Q.top(); Q.pop();
		Flag[h.second] = true;

		for(auto e: G[h.second]){
			if(Flag[e.second]) continue;
			int tmp = e.first + D[h.second];
			if(tmp < D[e.second]){
				D[e.second] = tmp;
				Q.push({tmp, e.second});
			}
		}
	}

	int m1 = -1, m2 = -1;
	for(int i=1;i<=N;++i){
		if(i == s || D[i] == INF) continue;
		if(m1 < D[i]){
			m2 = m1;
			m1 = D[i];
		}else if(m2 < D[i]){
			m2 = D[i];
		}

	}
	if(m1 == -1 || m2 == -1) return -1;
	return m1 + m2;
}

int proc(){
	int ans = -1;
	for(int i=1;i<=N;++i){
        ans = max(ans, proc(i));
	}
	return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
#endif
    int nofkase = getUnsigned();
	while(nofkase--){
        N = getUnsigned();
		M = getUnsigned();
		for(int i=1;i<=N;++i) G[i].clear();
		for(int a,b,c,i=0;i<M;++i){
			a = getUnsigned();
			b = getUnsigned();
			c = getUnsigned();
			G[a].emplace_back(c, b);
			G[b].emplace_back(c, a);
		}
		printf("%d\n", proc());
	}
    return 0;
}