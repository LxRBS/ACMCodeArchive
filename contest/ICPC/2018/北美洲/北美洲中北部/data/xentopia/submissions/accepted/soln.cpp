#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <cstring>
#include <climits>
#include <unordered_map>
#include <unordered_set>
#include <cassert>
#include <string>
#include <cstring>
#include <queue>
#include <cmath>
#include <cassert>
using namespace std;
#define fre freopen("0.in", "r", stdin), freopen("0.out", "w", stdout)
#define abs(x) ((x) > 0 ? (x) : -(x))
#define MOD 1000000007
#define ll signed long long int
#define ps(x) push_back(x)
#define scan(x) scanf("%d", &x)
#define print(x) printf("%d\n", x)
#define scanll(x) scanf("%lld", &x)
#define printll(x) printf("%lld\n", x)
#define rep(i,a,b) for(int i = a; i < b; i++)
#define pb push_back
#define mp make_pair
#define all(v) v.begin(),v.end()

typedef long long int64;
typedef unsigned long long uint64;
#define two(X) (1<<(X))
#define twoL(X) (((int64)(1))<<(X))
#define contain(S,X) (((S)&two(X))!=0)
#define containL(S,X) (((S)&twoL(X))!=0)

typedef pair<int, int> pii;
typedef pair<int, pii> tuple3;
typedef vector<int> vi;
typedef vector<pii> vpii;

// Print vectors with primitive types
template <typename T>
void printVector(vector<T> v) {
	for(T x: v) {
		cout << x << " ";
	}
	cout << "\n";
}

// Print vector of pair of primitive types
template <typename T, typename U>
void printVectorOfPairs(vector<pair<T, U> > v) {
	for(auto x: v) {
		cout << "{" << x.first << ", " << x.second << "}, ";
	}
	cout << "\n";
}

/* template ends */

const ll MAXN = 751;
const ll MAXK1 = 1002;
const ll MAXK2 = 1002;

struct edge {
	ll from, to, weight;
	edge(ll u, ll v, ll w) {
		from = u;
		to = v;
		weight = w;
	}
};

struct dijk_edge {
	ll to, length;
	dijk_edge(ll v, ll w) {
		to = v;
		length = w;
	}
};

vector<edge> redEdges, blueEdges, whiteEdges;

ll s, t;
ll n, m, k1, k2;
ll src, dest;

typedef vector<dijk_edge> adj_list;
typedef vector<adj_list> graphType;

graphType G;

// index goes from 0 to n*k1*k2 - 1
ll getIndex(ll i, ll j, ll k) {
	return (j*n*(k2+1)) + (k*n) + i;
}

void initialize() {
	G.clear();
	G.resize((n * (k1+1) * (k2+1)) + 42);
}

void input() {
	cin >> n >> m >> k1 >> k2;
	assert(n >= 1 and n <= 750);
	assert(m >= 1 and m <= 1250);
	assert(k1 >= 0 and k1 <= 1000);
	assert(k2 >= 0 and k2 <= 1000);
	for(ll i = 0 ; i < m ; i++) {
		ll c, u, v, w; cin >> u >> v >> w;
		assert(u >= 1 and u <= n);
		assert(v >= 1 and v <= n);
		assert(w >= 0 and w <= (ll)1e9);
		u--, v--;
		cin >> c;
		assert(c >= 0 and c <= 2);
		if(c == 0) {
			whiteEdges.pb(edge(u, v, w));
			whiteEdges.pb(edge(v, u, w));
		} else if(c == 1) {
			redEdges.pb(edge(u, v, w));
			redEdges.pb(edge(v, u, w));
		} else {
			blueEdges.pb(edge(u, v, w));
			blueEdges.pb(edge(v, u, w));
		}
	}
	cin >> s >> t;
	assert(s >= 1 and s <= n);
	assert(t >= 1 and t <= n);
	s--, t--;
}

void addEdge(ll u, ll v, ll w) {
	G[u].pb(dijk_edge(v, w));
}

void construct_layer(ll j, ll k) {
	for(auto edge: whiteEdges) {
		ll u = getIndex(edge.from, j, k);
		ll v = getIndex(edge.to, j, k);
		ll w = edge.weight;
		addEdge(u, v, w);
	}
}

void construct_intra_layer() {
	rep(j, 0, k1 + 1) {
		rep(k, 0, k2 + 1) {
			construct_layer(j, k);
		}
	}
}

void construct_inter_layer() {
	// add red edges
	rep(j, 0, k1) {
		rep(k, 0, k2 + 1) {
			for(auto edge: redEdges) {
				ll u = getIndex(edge.from, j, k);
				ll v = getIndex(edge.to, j + 1, k);
				ll w = edge.weight;
				addEdge(u, v, w);
			}
		}
	}

	// add blue adges
	rep(j, 0, k1 + 1) {
		rep(k, 0, k2) {
			for(auto edge: blueEdges) {
				ll u = getIndex(edge.from, j, k);
				ll v = getIndex(edge.to, j, k + 1);
				ll w = edge.weight;
				addEdge(u, v, w);
			}
		}
	}
}

void construct_graph() {
	construct_intra_layer();
	construct_inter_layer();
}

vector<ll> min_distance;
set<pair<ll,ll>> active_vertices;

ll dijkstra() {
	// source = (S, 0, 0)
	// dest = (T, k1, k2)
	ll source = getIndex(s, 0, 0);
	// cerr << "Source = " << source << "\n";
	ll target = getIndex(t, k1, k2);

	min_distance.resize( G.size(), LLONG_MAX );
  min_distance[ source ] = 0;
  
  active_vertices.insert( {0, source} );
      
  while (!active_vertices.empty()) {
      ll where = active_vertices.begin()->second;
       // cerr << "Processing vertex " << where << "\n";
       // cerr << min_distance[where] << "\n";
      if (where == target) {
      	// cerr << "Found destination.\n";
      	// cerr << "Returning " << min_distance[where] << "\n";
      	return min_distance[where];
      }
      active_vertices.erase( active_vertices.begin() );
      for (auto ed : G[where])  {
      	// cerr << "Seeing edge from " << where << " to " << ed.to << "\n";
    	  if (min_distance[ed.to] > min_distance[where] + ed.length) {
            active_vertices.erase( { min_distance[ed.to], ed.to } );
            min_distance[ed.to] = min_distance[where] + ed.length;
            active_vertices.insert( { min_distance[ed.to], ed.to } );
        }
      }
  }
  return -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
	input();
	initialize();
	construct_graph();
	cout << dijkstra() << "\n";
}
