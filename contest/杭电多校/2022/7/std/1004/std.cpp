#pragma comment(linker, "/STACK:1024000000,1024000000")
/*
	Author: elfness@UESTC
*/
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <queue>

using namespace std;
typedef long long LL;
typedef pair<int, int> PII;
#define PB push_back
#define fi first
#define se second
#define MP make_pair
const int oo = 1000000000;
const int P = 1000000007;

int _, ca, E, L, R, B;
int main() {
	scanf("%d", &_);
	for (int ca = 1; ca <= _; ++ca) {
		scanf("%d%d%d%d", &E, &L, &R, &B);
		int n = E + L + R + B;
		int mi = min(L, R);
		if (max(L, R) > 0) mi += B;
		else mi += max(0, B - 1);
		mi = n - mi;
		int mx = max(B - E - 1, 0);
		mx = n - mx;
		// printf("Case #%d: %d %d\n", ca, mi, mx);
		printf("%d %d\n", mi, mx);
	}
	return 0;
}

/*
E L R B
3
1 1 1 1
1 2 3 4
3 4 5 6
*/
