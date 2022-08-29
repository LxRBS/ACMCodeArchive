#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
#define N 1000 + 5
#define M (N) * (N)

int A[N][N], X[M], Y[M];
bool Flag[M];

int main(int argc, char *argv[])
{
	registerTestlibCmd(argc, argv);
	
	int n = inf.readInt();
	inf.readSpace();
	int m = inf.readInt();
	inf.readEoln();
	
	string str = ouf.readLine("[a-zA-Z]{2,3}", "res");
	if (str != "Yes")
		quitf(_wa, "First Line not Yes");
	for (int i = 1; i <= n; i ++)
		for (int j = 1; j <= m; j ++)
		{
			A[i][j] = ouf.readInt(1, n * m, "A[i][j]");
			X[A[i][j]] = i, Y[A[i][j]] = j;
			if (Flag[A[i][j]])
				quitf(_wa, "Duplicated Entry");
			Flag[A[i][j]] = true;
			//if (j < m)
			//	ouf.readSpace();
			//else ouf.readEoln();
		}
	for (int i = 1; i < n * m; i ++)
	{
		int d = abs(X[i] - X[i + 1]) + abs(Y[i] - Y[i + 1]);
		if (d != 1)
			quitf(_wa, "Adjacent Integers not Near");
	}
	
	int cnt = 0;
	for (int i = 2; i < n * m; i ++)
	{
		bool is_turn = true;
		if (X[i - 1] == X[i] && X[i] == X[i + 1])
			is_turn = false;
		if (Y[i - 1] == Y[i] && Y[i] == Y[i + 1])
			is_turn = false;
		if (is_turn)
			cnt ++;
	}
	
	if (cnt * 2 != n * m)
		quitf(_wa, (to_string(cnt) + " Turning Integers Found, but " + to_string(n * m / 2) + " Expected").c_str());
	
	inf.readEof();
	//ouf.readEof();
	
	quitf(_ok, "OK, Accepted.");
}

