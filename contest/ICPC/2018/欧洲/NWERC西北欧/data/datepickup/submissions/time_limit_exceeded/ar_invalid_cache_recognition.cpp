// Author Alexander Rass
#include <bits/stdc++.h>
using namespace std;

#define READYNESS_ON_INTEGER 0

const int MAXN = 1.1e5;
const int MAXM = MAXN;

vector<int> adj[MAXN][2]; // edge id's [0]->forward, [1]->backward
int xo[MAXM];
long long cost[MAXM];
long long dist[2][MAXN];
long long A, B;
int N, M;

vector<int> active;
int marked[MAXN];
vector<int> sub_adj[MAXN]; // edge id's
int indegree[MAXN];
long long latest_arrival[MAXN];

void init(int n, long long allowedWaitingTime){
    if(marked[n] != allowedWaitingTime){
        marked[n] = allowedWaitingTime;
        sub_adj[n].clear();
        active.push_back(n);
        indegree[n] = 0;
    }
}
bool check(long long allowedWaitingTime){
    assert(marked[N] != allowedWaitingTime);
    if(dist[0][N] > allowedWaitingTime + A)return false;
    if(dist[0][N] <= allowedWaitingTime)return true;
    active.clear();
    for(int i = 0; i <= N; i++){
        if(dist[0][i] + dist[1][i] <= A + allowedWaitingTime && dist[1][i] <= allowedWaitingTime){
            init(i, allowedWaitingTime);
            latest_arrival[i] = A + allowedWaitingTime - dist[1][i];
        }
    }
    for(unsigned int i = 0; i < active.size(); i++){
        auto n = active[i];
        for(auto eid: adj[n][0]){
            auto to = xo[eid]^n;
            auto c = cost[eid];
#if READYNESS_ON_INTEGER
            if(dist[1][to] + max(0, c-1) <= allowedWaitingTime){
#else
            if(dist[1][to] + c <= allowedWaitingTime){
#endif
                init(to, allowedWaitingTime);
                indegree[to]++;
                sub_adj[n].push_back(eid);
                latest_arrival[to] = 0;
            }
        }
    }
    queue<int> q;
    for(auto n: active)if(indegree[n] == 0)q.push(n);
    while(!q.empty()){
        int n = q.front();
        q.pop();
        for(auto eid: sub_adj[n]){
            int to = xo[eid] ^ n;
            if(--indegree[to] == 0)q.push(to);
            latest_arrival[to] = max(latest_arrival[to], latest_arrival[n] + cost[eid]);
        }
        if(n == N)assert(q.empty());
        if(n == N){
            return latest_arrival[n] >= B;
        }
    }
    // Here: node with id n is in a cycle!
    return true;
}

int main(){
    cin >> A >> B >> N >> M;
    for(int i = 0; i <= N; i++)
        for(int j = 0; j < 2; j++)
            adj[i][j].clear();
    for(int i = 0; i < M; i++){
        int a,b;
        long long c;
        cin >> a >> b >> c;
        xo[i] = a^b;
        cost[i] = c;
        adj[a][0].push_back(i);
        adj[b][1].push_back(i);
    }
    for(int flag = 0; flag < 2; flag++){//forward from node 1 or backward from node n
        //dijkstra:
        for(int n = 1; n <= N; n++)dist[flag][n] = 1e18;
        int start = ((flag==0)?1:N);
        dist[flag][start] = 0;
        priority_queue<pair<long long,int>, vector<pair<long long,int> >, greater<pair<long long,int> > > pq;
        pq.push(make_pair(0,start));
        while(!pq.empty()){
            auto nn = pq.top();
            pq.pop();
            if(dist[flag][nn.second] != nn.first)continue;
            int n = nn.second;
            for(auto eid: adj[n][flag]){
                int to = xo[eid]^n;
                long long c = cost[eid];
                if(dist[flag][to] > dist[flag][n] + c){
                    dist[flag][to] = dist[flag][n] + c;
                    pq.push(make_pair(dist[flag][to], to));
                }
            }
        }
    }
    if(dist[0][N] >= B){
        cout << dist[0][N] - A << endl;
        return 0;
    }
    for(int i = 0; i <= N; i++)marked[i] = -1;
    long long lo = 0, hi = B - A;
    while(lo != hi){
        long long m = lo + (hi - lo) / 2;
        bool tmp = check(m);
        if(tmp)hi = m;
        else lo = m + 1;
    }
    cout << lo << endl;
	return 0;
}
