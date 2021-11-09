// checker.cpp: for checking the answer of 'delete-edges'
// Author: HeRaNO
#include "testlib.h"
#define MAXN 2005

bool a[MAXN][MAXN];

int main(int argc, char *argv[])
{
	registerTestlibCmd(argc, argv);
	int n = inf.readInt();
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
			a[i][j] = true;
		a[i][i] = false;
	}
	int m = ouf.readInt();
	for (int i = 1; i <= m; i++)
	{
		int x = ouf.readInt(1, n);
		int y = ouf.readInt(1, n);
		int z = ouf.readInt(1, n);
		if (x == y || x == z || y == z)
			quitf(_wa, "delete a self loop");
		if (!a[x][y] || !a[y][x])
			quitf(_wa, "delete an edge which deleted before");
		a[x][y] = a[y][x] = false;
		if (!a[y][z] || !a[z][y])
			quitf(_wa, "delete an edge which deleted before");
		a[z][y] = a[y][z] = false;
		if (!a[x][z] || !a[z][x])
			quitf(_wa, "delete an edge which deleted before");
		a[z][x] = a[x][z] = false;
	}
	int cnt = 0;
	for (int i = 1; i <= n; i++)
		for (int j = i + 1; j <= n; j++)
			cnt += a[i][j];
	if (cnt >= n)
		quitf(_wa, "remain >=n edges");
	quitf(_ok, "ok");
	return 0;
}