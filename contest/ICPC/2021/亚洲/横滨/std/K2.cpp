/**
* copy from HNU-team4
*/
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 1005;
 
int n;
double D;
	
struct Node {
	double x, y, vx, vy;
}a[N];
struct Edge {
	int nxt, To; double metl, metr;
}e[N*N];
double dis[N];
int ls[N], cnt;
bool vis[N];

struct Code {
	int u; double w;
	bool friend operator< (Code a,Code b){return a.w>b.w;}
};
priority_queue<Code>q;

void Addedge(int p, int q) {
	double A = (a[p].vx-a[q].vx)*(a[p].vx-a[q].vx)+(a[p].vy-a[q].vy)*(a[p].vy-a[q].vy);
	double B = 2.0*(a[p].x-a[q].x)*(a[p].vx-a[q].vx)+2.0*(a[p].y-a[q].y)*(a[p].vy-a[q].vy);
	double C = (a[p].x-a[q].x)*(a[p].x-a[q].x)+(a[p].y-a[q].y)*(a[p].y-a[q].y)-D*D;
	double CT = B*B-4.0*A*C;
	double l, r;
	if (CT < 0) return;
	if (!A) {
		double DD = sqrt((a[p].x-a[q].x)*(a[p].x-a[q].x)+(a[p].y-a[q].y)*(a[p].y-a[q].y));
		if (DD <= D) l = 0, r = 1e18; else return;
	} else {
	    l = (-B-sqrt(CT))/(2.0*A);
	    r = (-B+sqrt(CT))/(2.0*A);
	    if (r < 0) return;
	    if (l < 0) l = 0;
	}
	e[++cnt].To = q, e[cnt].nxt = ls[p]; 
	e[cnt].metl = l, e[cnt].metr = r;
	ls[p] = cnt;
	e[++cnt].To = p; e[cnt].nxt = ls[q];
	e[cnt].metl = l, e[cnt].metr = r;
	ls[q] = cnt;
}

void dijkstra() {
	for (int i = 1; i <= n; i++) dis[i] = 1e18; 
	dis[0] = 0; 
	q.push((Code){0, 0});
	while (!q.empty()) {
		Code t = q.top(); q.pop();
		int u = t.u;
		if (vis[u]) continue;
		vis[u] = 1;
		for (int i = ls[u]; i; i = e[i].nxt) {
			int v = e[i].To; double w;
			if (dis[u] > e[i].metr || vis[v]) continue;
			if (dis[u] <= e[i].metl) w = e[i].metl; else w = dis[u];
			if (dis[v] > w) {
				dis[v] = w;
				q.push((Code){v, dis[v]});
			}
		}
	}
}

int main() {
   //freopen("data.in", "r", stdin); 
    cin>>n>>D;
    for (int i = 0; i <= n; i++) {
        cin>>a[i].x>>a[i].y>>a[i].vx>>a[i].vy; 
	}
    for (int i = 0; i <= n; i++) 
    	for (int j = i+1; j <= n; j++) Addedge(i, j);
  /*for (int i = 0; i <= n; i++) {
    	for (int j = ls[i]; j; j = e[j].nxt) cout<<i<<' '<<e[j].To<<' '<<e[j].metl<<" "<<e[j].metr<<endl;
	}
	*/ 
    dijkstra();
    for (int i = 1; i <= n; i++) 
	    if (dis[i] == 1e18) printf("-1\n"); else printf("%.10lf\n", dis[i]);
	return 0; 
}
