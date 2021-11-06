#include <bits/stdc++.h>

#define sz(c) ll((c).size())
#define FOR(i,a,b) for(ll i=(a); i<(b); i++)
#define xx first
#define yy second

using namespace std;

typedef long long ll;
typedef long double ld;
typedef vector<ll> vl;

vl parts;
vector<pair<ld, ld>> pos;

int dfs_part(int cur, int prev, vector<vl>& adj){
	parts[cur] = 1;
	for(auto& a : adj[cur]){
		if(a == prev) continue;
		parts[cur] += dfs_part(a, cur, adj);
	}
	return parts[cur];
}

void dfs_construct(int cur, int prev, ld fr, ld to, vector<vl>& adj){
	ld dist = to - fr;
	//cerr << cur << ": " << fr << "-" << to << endl;
	if(parts[cur] == 1) return;
	ld dist_p_child = dist / (parts[cur] - 1);
	ll done_c = 0;
	for(ll child : adj[cur]){
		if(child == prev) continue;
		ld nf = fr + (done_c * dist_p_child);
		ld nt = fr + ((done_c + parts[child]) * dist_p_child);
		pos[child] = {pos[cur].xx + cos(nf), pos[cur].yy + sin(nf)};
		dfs_construct(child, cur, nf, nt, adj);
		done_c += parts[child];
	}

}

int main(){
	ll n;
	cin >> n;
	vector<vl> adj(n);
	parts = vl(n);
	pos = vector<pair<ld, ld>>(n);
	FOR(i, 0, n-1){
		ll fr, to;
		cin >> fr >> to;
		fr--; to--;
		adj[fr].push_back(to);
		adj[to].push_back(fr);
	}

	dfs_part(0, -1, adj);

	dfs_construct(0, -1, 0, M_PI-0.01, adj);

	for(auto& p : pos){
		cout << setprecision(9) << fixed << p.xx << " " << p.yy << endl;
	}

}
