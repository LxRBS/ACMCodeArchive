#include <cstdio>
#include <cmath>
#include <algorithm>
 
using namespace std;
 
const double pi = acos(-1.0);
const double eps = 1e-8;
 
double r;
double x, y, d;
 
void solve()
{
	scanf("%lf", &r);
	scanf("%lf%lf%lf", &x, &y, &d);
	double p = sqrt(x * x + y * y);
	double yl = sqrt(r * r - (p - d) * (p - d));
	double yr = sqrt(r * r - (p + d) * (p + d));
	double l = sqrt(4 * d * d + (yr - yl) * (yr - yl));
	double a = 2 * r * asin(l / 2 / r);
	printf("%.10lf\n", a);
}
 
int main()
{
	int T;
	scanf("%d", &T);
	while (T--)
		solve();
	return 0;
}
