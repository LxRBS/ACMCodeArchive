#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
#define N (100 + 5)

int T, n, m, A[N], Dp[N][2];
bool Flag[N];

int main(int argc, char *argv[])
{
	registerTestlibCmd(argc, argv);
	
	T = inf.readInt();
	inf.readEoln();
	int maxlen = 0;
	for (int Case = 1; Case <= T; Case ++)
	{
	    //setTestCase(Case);
		m = inf.readInt();
		inf.readEoln();
		
		n = ouf.readInt(1, 100, "n");
		
		maxlen = max(maxlen, n);
		//ouf.readEoln();
		for (int i = 1; i <= n; i ++)
			Flag[i] = false;
		for (int i = 1; i <= n; i ++)
		{
			A[i] = ouf.readInt(1, n, format("A_%d", i));
			ensuref(!Flag[A[i]], "Case %d : duplicated number %d", Case, A[i]);
			Flag[A[i]] = true;
		}
		//ouf.readEoln();
		
		A[0] = 0, A[n + 1] = n + 1;
		Dp[0][0] = 0, Dp[0][1] = 1;
		for (int i = 1; i <= n + 1; i ++)
		{
			Dp[i][0] = Dp[i][1] = 0;
			for (int j = 0; j < i; j ++)
				if (A[j] < A[i])
					Dp[i][0] = max(Dp[i][0], Dp[j][0] + 1);
			for (int j = 0; j < i; j ++)
				if (A[j] < A[i] && Dp[j][0] + 1 == Dp[i][0])
					Dp[i][1] = min(Dp[i][1] + Dp[j][1], m + 1);
		}
		
		if (Dp[n + 1][1] != m)
			quitf(_wa, "Case %d : the number of LISs not equal m", Case);
	}
	
	inf.readEof();
	//ouf.readEof();
	
	quitf(_ok, "OK, Accepted. Maximum length = %d", maxlen);
}
