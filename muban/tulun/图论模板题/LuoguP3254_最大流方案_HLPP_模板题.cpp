/**
 * 建模跑最大流输出方案
 */
#include <bits/stdc++.h>
using namespace std;

#include <bits/extc++.h>
using namespace __gnu_pbds;

using Real = long double;
using llt = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;

#ifndef ONLINE_JUDGE
int const SZ = 101;
#else
int const SZ = 110;
#endif
struct MaxFlow_HLPP{ // 方案似乎没错


enum{INF=0x7F7F7F7F7F7F7F7F}; 

using vi = vector<int>;
using vvi = vector<vi>;

using weight_t = long long;
using edge_t = tuple<int, int, weight_t>;
using ve = vector<edge_t>;

vvi g; // 邻接表
ve edges; // 边表

MaxFlow_HLPP() = default;

/// 参数为题目给定的点数和边数
void init(int ncnt, int ecnt=0){
    this->g.assign(ncnt+1, vi());
    this->edges.clear();
    this->edges.reserve(ecnt+ecnt);
}

void mkDirectEdge(int a, int b, weight_t w){
    int t = this->edges.size();
    this->g[a].push_back(t);
    this->edges.push_back({a, b, w}); 
    /// 生成反向边
    this->g[b].push_back(t+1);
    this->edges.push_back({b, a, 0});
}

weight_t maxflow(int s, int t){
	int n = this->g.size() - 1;
	int mxh, szh;
	
    vi h(n+1, 0);
	vi cnt(n+1, 0);
	vi q(n+1, 0); // 队列
	vvi vvs(n+1, vi());
	
	vector<list<int>> gap(n+1, list<int>());
	vector<list<int>::iterator> ep(n+1);

	vector<weight_t> flow(n+1, 0LL);
	flow[t] = -(flow[s] = INF);

	auto initLabel = [&]()->void{
		h.assign(n+2, n+2);

		auto head = q.begin();
		auto tail = q.begin();

		int u, v;

		h[*tail++ = t] = 0; // 入队
		while(head < tail){
			for(auto i : this->g[u = *head++]){
				const auto & e = this->edges[i];
                if(h[v=get<1>(e)] == n + 2 && get<2>(this->edges[i^1]) != 0){
					++cnt[h[*tail++ = v] = h[u] + 1];
				}
			}
		}
		for(int i=0;i<=n;++i){
			gap[i].clear();
			vvs[i].clear();
		}
		for(int i=1;i<=n;++i){
		    if(h[i] > n) continue;

			ep[i] = gap[h[i]].insert(gap[h[i]].begin(), i);
			if(flow[i] > 0) vvs[h[i]].push_back(i);	
		}

        mxh = szh = h[*(tail - 1)];
	};

	auto pushEdge = [&](int u, int ei)->void{
		auto & e = this->edges[ei];
		int v = get<1>(e);
        auto w = min(get<2>(e), flow[u]);
		flow[u] -= w;
		get<2>(e) -= w;
		flow[v] += w;
		get<2>(this->edges[ei^1]) += w;
		if(0 < flow[v] && flow[v] <= w){
            vvs[h[v]].push_back(v);
		}
	};

    auto push = [&](int u)->void{
        int v, fx = n + 1, tmp = h[u];
		for(int i : this->g[u]){
			const auto & e = this->edges[i];
			if(get<2>(e) <= 0) continue;

			if(h[v = get<1>(e)] + 1 == h[u]){
				pushEdge(u, i);
				if(!flow[u]) return;
			}else{
				fx = min(fx, h[v] + 1);
			}
		}
		if(cnt[h[u]] <= 1){
			for(int i=tmp;i<=mxh;gap[i].clear(),++i){
				for(int j : gap[i]){
					--cnt[h[j]];
					h[j] = n + 1;
				}
			}
			mxh = tmp - 1;
			return;
		}
		--cnt[tmp];
		ep[u] = gap[tmp].erase(ep[u]);
		h[u] = fx;
		if(n + 1 == fx) return;
		++cnt[fx];
        ep[u] = gap[fx].insert(gap[fx].begin(), u);
		mxh = max(szh = fx, mxh);
		vvs[fx].push_back(u);
	};

	h[s] = (cnt[0]=n) + 1;
	for(int i=1;i<=n;++i){
		if(i==s) continue;
		ep[i] = gap[h[i]].insert(gap[h[i]].begin(), i);
	}
	for(int i : this->g[s]){
		pushEdge(s, i);
	}
	initLabel();
	while(szh > 0){
		if(vvs[szh].empty()) {
		    --szh;
		}else{
            int x = vvs[szh].back();
			vvs[szh].pop_back();
			push(x);
		}
	}
	return flow[t] + INF;
}


void forEachUsed(function<void(int index, weight_t usedw)> f){
    for(int i=0,n=edges.size();i<n;i+=2){
        if(get<2>(edges[i ^ 1]) > 0){
            f(i, get<2>(edges[i ^ 1]));
        }
    }
    return;
}

};


int Total;
int M, N, S, T;
MaxFlow_HLPP HLPP;

void proc(){
    auto ans = HLPP.maxflow(S, T);
    if(ans != Total) return (void)(cout << 0 << endl);

    cout << 1 << endl;
    vvi results(M + 1, vi());
    HLPP.forEachUsed([&](int index, MaxFlow_HLPP::weight_t usedw){
        int from, to;
        decltype(usedw) w;
        std::tie(from, to, w) = HLPP.edges[index];
        if(1 <= from and from <= M and M + 1 <= to and to <= N + M){
            assert(usedw == 1 and w == 0);
            results[from].push_back(to - M);
        }
    });
    for(int i=1;i<=M;++i){
        sort(results[i].begin(), results[i].end());
        for(auto j : results[i]) cout << j << " ";
        cout << endl;
    }
    return;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> M >> N;
    Total = 0;
    HLPP.init(T = 1 + (S = N + M + 1));
    for(int r,i=1;i<=M;++i){
        cin >> r;
        HLPP.mkDirectEdge(S, i, r);
        Total += r;
    }
    for(int r,i=1;i<=N;++i){
        cin >> r;
        HLPP.mkDirectEdge(i + M, T, r);
    }
    for(int i=1;i<=M;++i)for(int j=1;j<=N;++j){
        HLPP.mkDirectEdge(i, j + M, 1);
    }
    proc();
    return 0;
}