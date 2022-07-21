#include <cstdio>
#include <algorithm>
 
using namespace std;
 
const int N = 2e5 + 5;
 
int n;
long long x[N], r[N];
long long ans, pr;
int p[N];
 
bool cmp(int a, int b)
{
	return x[a] - r[a] < x[b] - r[b];
}
 
int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%lld%lld", &x[i], &r[i]);
		p[i] = i;
	}
	sort(p + 1, p + n + 1, cmp);
	pr = x[p[1]] - r[p[1]];
	for (int i = 1; i <= n; i++)
	{
		if (pr < x[p[i]] - r[p[i]])
			ans += x[p[i]] - r[p[i]] - pr;
		pr = max(pr, x[p[i]] + r[p[i]]);
	}
	printf("%lld\n", ans);
	return 0;
}