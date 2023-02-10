/**
 * 本质上就是给定两个无向图，对于边(u, v)，如果在两个图上，都能属于u到N的最短路，则通过该边代价为0
 * 如果只有一个是最短路，则为1，否则为2。问从1到N的最小代价是多少。
 * 首先对两个图从N跑出最短路。然后对每一条边(u, v)进行检查即可。注意检查的时候(u, v)和(v, u)是不同的。
 * 根据检查结果建出新图，再跑一次最短路即可。
 */
#include <bits/stdc++.h>
using namespace std;

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

using llt = long long;
using vi = vector<int>;
using vll =vector<llt>;
using edge_t = tuple<int, int, int, int>;
using ve = vector<edge_t>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vpii = vector<pii>;

int const INF = 2000000000;

struct q_t : public priority_queue<pii, vpii, function<bool(pii, pii)>>{
void clear(){c.clear();}
q_t(function<bool(pii, pii)> f):priority_queue<pii, vpii, function<bool(pii, pii)>>(f){}
};

int N, M;
vvi G;
ve Edges;
vi Jiyi, Ditu;

q_t Q([](pii a, pii b){
    if(a.second != b.second) return a.second > b.second;
    return a.first > b.first; 
});

int proc(){
    Jiyi.assign(N + 1, INF);
    vi flag(N + 1, 0);
    Q.clear();
    Q.push({N, Jiyi[N] = 0});
    while(1){
        while(!Q.empty() && flag[Q.top().first]) Q.pop();
        if(Q.empty()) break;
        auto h = Q.top(); Q.pop();        
        int u = h.first;
        flag[u] = true;
        for(int i : G[u]){
            const auto & e = Edges[i];
            int v = get<0>(e) ^ get<1>(e) ^ u;
            if(flag[v] || Jiyi[v] <= h.second + get<2>(e)) continue;
            Q.push({v, Jiyi[v] = h.second + get<2>(e)});
        } 
    }

    Ditu.assign(N + 1, INF);
    flag.assign(N + 1, Ditu[N] = 0);
    Q.clear();
    Q.push({N, 0});
    while(1){
        while(!Q.empty() && flag[Q.top().first]) Q.pop();
        if(Q.empty()) break;
        auto h = Q.top(); Q.pop();        
        int u = h.first;
        flag[u] = true;
        for(int i : G[u]){
            const auto & e = Edges[i];
            int v = get<0>(e) ^ get<1>(e) ^ u;
            if(flag[v] || Ditu[v] <= h.second + get<3>(e)) continue;
            Q.push({v, Ditu[v] = h.second + get<3>(e)});
        }         
    }

    auto isOK = [](int u, int v, int w, const vi & d){
        return d[v] + w == d[u];
    };

    auto f = [isOK](int u, int v, int jiyi, int ditu){
        int flagjiyi = isOK(u, v, jiyi, Jiyi);
        int flagditu = isOK(u, v, ditu, Ditu);
        int st = (flagjiyi << 1) | flagditu;
        if(3 == st) return 0;
        if(0 == st) return 2;
        return 1;
    };

    vector<vpii> g(N + 1);
    for(const auto & e : Edges){  
        auto [u, v, jiyi, ditu] = e;      
        auto tmp = f(u, v, jiyi, ditu);
        g[u].emplace_back(v, tmp);
        tmp = f(v, u, jiyi, ditu);
        g[v].emplace_back(u, tmp);
    }

    vi d(N + 1, INF);
    flag.assign(N + 1, 0);
    Q.clear();
    Q.push({1, d[1] = 0});
    while(1){
        while(!Q.empty() && flag[Q.top().first]) Q.pop();
        if(Q.empty()) break;
        auto h = Q.top(); Q.pop();        
        int u = h.first;
        flag[u] = true;
        for(const auto & p : g[u]){
            int v = p.first;
            if(flag[v] || d[v] <= h.second + p.second) continue;
            Q.push({v, d[v] = h.second + p.second});
        }         
    }    
    return d[N];
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    N = getInt(); M = getInt();
    Edges.reserve(M);
    G.assign(N + 1, {});
    for(int u,v,a,b,i=0;i<M;++i){
        u = getInt(); v = getInt();
        a = getInt(); b = getInt();
        G[u].push_back(Edges.size());
        G[v].push_back(Edges.size());
        Edges.emplace_back(u, v, a, b);
    } 
    printf("%d\n", proc());
    return 0;
}