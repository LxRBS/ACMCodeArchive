#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#define MAXN 200005

using namespace std;

int main() {
	static int a[MAXN];

	int N;
	scanf("%d",&N);

	int i;
	for (i = 0; i < N; i++) {
		scanf("%d",&a[i]);
	}
	sort(a, a+N);

	double res = 1.0;

	for (i = 0; i < N; i++) {
		if (a[i] > (i+1)) {
			printf("impossible\n");
			return 0;
		}
		res = min(res, (double)(a[i]) / (double)(i+1));
	}
	printf("%.9lf\n",res);
	
	return 0;
}
