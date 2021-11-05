
#include <list>
#include <map>
#include <set>
#include <stack>
#include <queue>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <cfloat>
#include <numeric>
#include <cassert>
#include <unordered_set>
#include <unordered_map>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef vector<string> vs;
typedef pair<int, int> pii;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;

#define sz(c) int((c).size())
#define all(c) (c).begin(), (c).end()
#define FOR(i,a,b) for (int i = (a); i < (b); i++)
#define FORD(i,a,b) for (int i = int(b)-1; i >= (a); i--)
#define FORIT(i,c) for (__typeof__((c).begin()) i = (c).begin(); i != (c).end(); i++)
#define mp(a,b) make_pair(a,b)
#define pb(a) push_back(a)

int V[2024], N, D;
int dp[2024][64];
int round10(int v){
	return ((v + 5) / 10) * 10;
}
int calc(int n, int d){
	if(d == 0)return round10(V[n]);
	if(n == 0)return 0;
	int & res = dp[n][d];
	if(res == -1){
		res = oo;
		FOR(i,0,n){
			res  = min(res, calc(i, d - 1) + round10(V[n] - V[i]));
		}
	}
	return res;
}

int main() {
	cin >> N >> D;
	FOR(i,0,N)cin >> V[i+1];
	V[0] = 0;
	FOR(i,1,N+1)V[i] += V[i-1];
	memset(dp,-1,sizeof(dp));
	cout << calc(N,D) << endl;
	return 0;
}
