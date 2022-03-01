/**
 * ���·ģ���⣬����ͼ����S��T�����·��
 * ʹ��pair����Ȩֵд��ǰ�棬����ֱ��ʹ��greater���бȽ�
*/
#include <bits/stdc++.h>
using namespace std;

#ifndef ONLINE_JUDGE
int const SIZE = 12;
#else
int const SIZE = 1012;
#endif

int const INF = 2000000000;

typedef pair<int, int> pii;
typedef vector<pii> vpii;
typedef priority_queue<pii, vpii, greater<pii> > _queue_t;

int N, M, S, T;
_queue_t Q;
vpii G[SIZE];
bool Flag[SIZE];
int D[SIZE];

int Dijkstra(){
	/// Dij�ĳ�ʼ��
    fill(Flag, Flag+N+1, false);
	fill(D, D+N+1, INF);

	Q.push({D[S]=0, S});
	while(1){
		while(!Q.empty() && Flag[Q.top().second]) Q.pop();
		if(Q.empty()) break;

		auto h = Q.top(); Q.pop();
		int v, u = h.second;
		int tmp, w = h.first; // w����Du
		Flag[u] = true;

		/// ��ΪֻҪ����T�����Կ�����ǰ�˳�
		if(u == T) break;

		for(const auto &p: G[u]){
			if(Flag[v=p.second] || D[v] <= (tmp=w+p.first)) continue;
			
			Q.push({D[v]=tmp, v});
		}
	}
	return D[T];
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    while(4 == scanf("%d%d%d%d", &N, &M, &S, &T)){
		/// ÿ��case�ĳ�ʼ������Ȼ���ﲢû�ж�case
        while(!Q.empty()) Q.pop();
		for(int i=1;i<=N;++i) G[i].clear();

		for(int a,b,w,i=0;i<M;++i){
            scanf("%d%d%d", &a, &b, &w);
			G[a].emplace_back(w, b);
			G[b].emplace_back(w, a);
		}

        int ans = Dijkstra();
		printf("%d\n", ans!=INF?ans:-1);
	}
	return 0;
}
