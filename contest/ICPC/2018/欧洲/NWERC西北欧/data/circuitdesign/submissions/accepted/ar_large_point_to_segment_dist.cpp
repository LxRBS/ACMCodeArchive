// Author Alexander Rass
#include <bits/stdc++.h>
using namespace std;
// TODO add minimal allowed distance between points
const double PI = acos(-1.0);
const int MAXN = 1024;
vector<int> adj[MAXN];
int depth[MAXN], angle[MAXN], max_angle_per_depth[MAXN];
long double x[MAXN], y[MAXN];
void rek_init(int n, int d = 0, int p=-1){
    depth[n] = d;
    bool first = true;
    for(auto to: adj[n])if(to != p){
        if(first)first = false;
        else max_angle_per_depth[d]++;
        angle[to] = max_angle_per_depth[d];
        rek_init(to, d+1, n);
    }
}
void rek_draw(int n, int d = 0, int p = -1){
    for(auto to: adj[n])if(to != p){
        double w = angle[to] * PI * 0.25 / max_angle_per_depth[d];
        long double dx = sin(w), dy = cos(w);
        long double dist = sqrt(dx*dx+dy*dy);
        x[to] = x[n] + dx / dist;
        y[to] = y[n] + dy / dist;
        rek_draw(to, d+1, n);
    }
}

int main(){
    int N;
    cin >> N;
    for(int i = 0; i < N; i++)adj[i].clear();
    for(int i = 0; i < N; i++)max_angle_per_depth[i] = 1;
    for(int i = 1; i < N; i++){
        int a,b;
        cin >> a >> b;
        adj[--a].push_back(--b);
        adj[b].push_back(a);
    }
    rek_init(0);
    x[0] = y[0] = 0;
    rek_draw(0);
    for(int i = 0; i < N; i++)printf("%.9lf %.9lf\n", (double)x[i], (double)y[i]);
	return 0;
}
