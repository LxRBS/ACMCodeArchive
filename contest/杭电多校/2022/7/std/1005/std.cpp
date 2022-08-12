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
const int N = 320;
const int V = N + 10;

int Pow(int x, int y) {
	int res = 1;
	while (y) {
		if (y & 1) res = (LL) res * x % P;
		x = (LL) x * x % P; y /= 2;
	}
	return res;
}

const int maskU = 8;
const int maskR = 4;
const int maskD = 2;
const int maskL = 1;
vector<int> LU, RU, RD, LD, VEC, HOR;
int C[V * V][V * 2];
int fac[V * V], pt[V * V];

int _, n, m, a[30], b[30], c[30];
int main() {
	scanf("%d", &_);
	for (int i = 0; i < (1 << 4); ++i) {
		bool hasU = (i & maskU) != 0;
		bool hasR = (i & maskR) != 0;
		bool hasD = (i & maskD) != 0;
		bool hasL = (i & maskL) != 0;
		if (hasL && hasU) LU.PB(i);
		if (hasR && hasU) RU.PB(i);
		if (hasR && hasD) RD.PB(i);
		if (hasL && hasD) LD.PB(i);
		if (hasU && hasD) VEC.PB(i);
		if (hasL && hasR) HOR.PB(i);
	}
	for (int i = 0; i <= N * N; ++i) {
		C[i][0] = 1;
		if (i <= 2 * N) C[i][i] = 1;
		for (int j = 1; j < min(2 * N + 1, i); ++j) C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % P;
	}
	fac[0] = 1;
	for (int i = 1; i <= N * N; ++i) fac[i] = (LL) fac[i - 1] * i % P;
	pt[0] = 1;
	for (int i = 1; i <= N * N; ++i) pt[i] = pt[i - 1] * 2 % P;
	for (int ca = 1; ca <= _; ++ca) {
		scanf("%d%d", &n, &m);
		for (int i = 0; i < (1 << 4); ++i) scanf("%d", &a[i]);
		int ans = 0;
		for (int lu = 0; lu < LU.size(); ++lu) {
			for (int ru = 0; ru < RU.size(); ++ru) {
				for (int rd = 0; rd < RD.size(); ++rd) {
					for (int ld = 0; ld < LD.size(); ++ld) {
						int xs = 1;
						for (int i = 0; i < 16; ++i) c[i] = 0;
						++c[LU[lu]];
						++c[RU[ru]];
						++c[RD[rd]];
						++c[LD[ld]];
						for (int i = 0; i < 16; ++i) if (a[i] < c[i]) xs = 0;
						if (xs == 0) continue;
						for (int i = 0; i < 16; ++i) {
							xs = (LL) xs * C[a[i]][c[i]] % P;
							xs = (LL) xs * fac[c[i]] % P;
							b[i] = a[i] - c[i];
						}
						int hor = 0, vec = 0, cross = b[15];
						//printf("Cal %d %d %d %d\n", xs, hor, vec, cross);
						for (int i = 0; i < HOR.size(); ++i) if (HOR[i] != 15) hor += b[HOR[i]];
						for (int i = 0; i < VEC.size(); ++i) if (VEC[i] != 15) vec += b[VEC[i]];
						for (int L = 0; L <= min(n, m) - 2; ++L) {
							int tmp = 0;
							for (int cro = 0; cro <= 2 * L; ++cro) {
								int v_cnt = 2 * L - cro;
								int h_remain = cross - cro + hor;
								if (v_cnt > vec || h_remain < 2 * L) continue;
								tmp += (LL) C[cross][cro] * C[vec][v_cnt] % P * C[h_remain][2 * L] % P;
								tmp %= P;
							}
							tmp = (LL) tmp * fac[2 * L] % P * fac[2 * L] % P;
							ans += (LL) tmp * fac[n * m - 4 * (L + 1)] % P * (n - L - 1) % P * (m - L - 1) % P * xs % P;
							ans %= P;
						}
					}
				}
			}
		}
		ans = (LL) ans * Pow(fac[n * m], P - 2) % P;
// 		printf("Case #%d: %d\n", ca, ans);
        printf("%d\n", ans);
	}
    return 0;
}

/*
URDL
3
2 2
0 0 0 0
0 0 0 0
0 0 0 0
0 0 0 4
2 2
0 0 0 1
0 0 1 0
0 1 0 0
1 0 0 0
316 316
6241 6241 6241 6241
6241 6241 6241 6241
6241 6241 6241 6241
6241 6241 6241 6241
*/
