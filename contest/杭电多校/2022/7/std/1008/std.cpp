#include <cstdio>

void Solve()
{
	int a, b, c;
	scanf("%d %d %d", &a, &b, &c);
	puts(((a - 1) ^ (b - 1) ^ (c - 1)) ? "Win" : "Lose");
	return ;
}

int main()
{
	int T; scanf("%d", &T);
	while (T--) Solve();
	return 0;
}