#include <bits/stdc++.h>

#define N 2005

using namespace std;

int n, m, ans;

char A[N][N], B[N];

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i)
	{
		scanf("%s", A[i] + 1);
	}
	scanf("%s", B + 1);
	for (int i = 1; i <= n; ++i)
	{
		int j, k;
		for (j = 1; j <= n; j = k)
			if (A[i][j] == '0')
			{
				for (k = j; k <= n && A[i][k] == '0'; ++k);
				ans += max(0, k - j - m + 1);
			}
			else k = j + 1;
	}
	printf("%d\n", ans);
}
