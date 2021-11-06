#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#define MAXN 1005

using namespace std;

static char a[MAXN][MAXN];
static double x[MAXN];
static double y[MAXN];
static int sz[MAXN];
int N;

int DFS0(int point, int par) {
	int cnt = 1;
	int i;
	for (i = 0; i < N; i++) {
		if ((a[point][i]) && (i != par)) {
			cnt += DFS0(i, point);
		}
	}
	sz[point] = cnt;
	return cnt;
}

void DFS(int point, int par, long double X, long double Y, long double XL, long double XR) {
	x[point] = X;
	y[point] = Y;

	int cur = 0;
	for (int i = 0; i < N; i++) {
		if ((a[point][i]) && (i != par)) {
			long double xl = XL + (long double)(cur) * ((XR - XL) / (long double)(sz[point] - 1));
			long double xr = XL + (long double)(cur + sz[i]) * ((XR - XL) / (long double)(sz[point] - 1));
			long double XP = (xl + xr) / 2.0;
			long double YP = (2.0 * Y + sqrt(4.0 - 4.0 * (XP - X) * (XP - X))) / 2.0;
			cur += sz[i];
			DFS(i, point, XP, YP, xl, xr);
		}
	}
}

int main() {

	scanf("%d",&N);
	int M = N-1;

	memset(a,0,sizeof(a));

	int i;
	for (i = 0; i < M; i++) {
		int x, y;
		scanf("%d %d",&x,&y);
		x--; y--;
		a[x][y] = 1;
		a[y][x] = 1;
	}

	DFS0(0, -1);
	DFS(0, -1, 0, 0, -1, 1);

	for (i = 0; i < N; i++) {
		printf("%.12lf %.12lf\n",(double)(x[i]),(double)(y[i]));
	}
	
	return 0;
}
