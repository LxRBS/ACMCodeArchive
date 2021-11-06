#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <ctime>
#include <cassert>
#include <complex>
#include <string>
#include <cstring>
#include <chrono>
#include <random>
#include <bitset>
using namespace std;

#ifdef LOCAL
	#define eprintf(...) fprintf(stderr, __VA_ARGS__);fflush(stderr);
#else
	#define eprintf(...) 42
#endif

using ll = long long;
using ld = long double;
using uint = unsigned int;
using ull = unsigned long long;
template<typename T>
using pair2 = pair<T, T>;
using pii = pair<int, int>;
using pli = pair<ll, int>;
using pll = pair<ll, ll>;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ll myRand(ll B) {
	return (ull)rng() % B;
}

#define pb push_back
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second

clock_t startTime;
double getCurrentTime() {
	return (double)(clock() - startTime) / CLOCKS_PER_SEC;
}

//using Int = __int128;

const ll B = (ll)1e18;
struct Int {
	vector<ll> a;

	Int() : a() {}
	Int(ll x) {
		a = {x};
	}

	Int operator + (const Int &A) const {
		Int R = Int();
		ll d = 0;
		for (int i = 0; i < (int)a.size() || i < (int)A.a.size() || d; i++) {
			if (i < (int)a.size()) d += a[i];
			if (i < (int)A.a.size()) d += A.a[i];
			R.a.push_back(d % B);
			d /= B;
		}
		return R;
	}

	bool operator < (const Int &A) const {
		if ((int)a.size() != (int)A.a.size()) return (int)a.size() < (int)A.a.size();
		for (int i = (int)a.size() - 1; i >= 0; i--) {
			if (a[i] != A.a[i])
				return a[i] < A.a[i];
		}
		return false;
	}

	void print() {
		if (a.empty()) {
			printf("0\n");
			return;
		}
		printf("%lld", a.back());
		for (int i = (int)a.size() - 2; i >= 0; i--)
			printf("%018lld", a[i]);
		printf("\n");
	}
};

const int A = 26;
Int dist[A][A][A];
bool used[A][A][A];
vector<pii> lft[A], rght[A];
vector<int> term[A];
int n, m;
int S, T;

void read() {
	cin >> n;
	while(n--) {
		string s;
		cin >> s;
		assert((int)s.length() == 1);
		int x = (int)(s[0] - 'A');
		assert(0 <= x && x < A);
		cin >> s;
		assert(s == "->");
		cin >> s;
		if ((int)s.length() == 1) {
			int y = (int)(s[0] - 'a');
			assert(0 <= y && y < A);
			term[y].push_back(x);
		} else {
			assert((int)s.length() == 2);
			int y = (int)(s[0] - 'A'), z = (int)(s[1] - 'A');
			assert(0 <= y && y < A);
			assert(0 <= z && z < A);
			lft[y].push_back(mp(x, z));
			rght[z].push_back(mp(x, y));
		}
	}
	cin >> n >> m >> S >> T;
	S--;T--;
	while(m--) {
		char w;
		int v, u;
		cin >> v >> u >> w;
		v--;u--;
		int c = (int)(w - 'a');
		//cerr << v << " " << u << " " << c << endl;
		for (int x : term[c]) {
			dist[x][v][u] = Int(1);
			used[x][v][u] = 1;
		}
	}
}

struct Item {
	int c, v, u;
	Int w;

	Item() : c(), v(), u(), w() {}
	Item(int _c, int _v, int _u, Int _w) : c(_c), v(_v), u(_u), w(_w) {}

	bool operator < (const Item &I) const {
		return tie(w, c, v, u) < tie(I.w, I.c, I.v, I.u);
	}
};

void printAns(Int x) {
	x.print();
}

int main()
{
	startTime = clock();
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);

	read();
	set<Item> setik;
	for (int c = 0; c < A; c++)
		for (int v = 0; v < n; v++)
			for (int u = 0; u < n; u++)
				if (used[c][v][u])
					setik.insert(Item(c, v, u, dist[c][v][u]));
	while(!setik.empty()) {
		Item I = *setik.begin();
		setik.erase(setik.begin());
		for (pii t : lft[I.c]) {
			for (int z = 0; z < n; z++) {
				if (!used[t.second][I.u][z]) continue;
				Int w = I.w + dist[t.second][I.u][z];
				int c = t.first;
				int v = I.v;
				int u = z;
				if (used[c][v][u] && !(w < dist[c][v][u])) continue;
				if (used[c][v][u])
					setik.erase(Item(c, v, u, dist[c][v][u]));
				used[c][v][u] = 1;
				dist[c][v][u] = w;
				setik.insert(Item(c, v, u, dist[c][v][u]));
			}
		}
		for (pii t : rght[I.c]) {
			for (int z = 0; z < n; z++) {
				if (!used[t.second][z][I.v]) continue;
				Int w = I.w + dist[t.second][z][I.v];
				int c = t.first;
				int v = z;
				int u = I.u;
				if (used[c][v][u] && !(w < dist[c][v][u])) continue;
				if (used[c][v][u])
					setik.erase(Item(c, v, u, dist[c][v][u]));
				used[c][v][u] = 1;
				dist[c][v][u] = w;
				setik.insert(Item(c, v, u, dist[c][v][u]));
			}
		}		
	}
	int c = (int)('S' - 'A');
	if (!used[c][S][T])
		printf("NO\n");
	else
		printAns(dist[c][S][T]);

	return 0;
}
