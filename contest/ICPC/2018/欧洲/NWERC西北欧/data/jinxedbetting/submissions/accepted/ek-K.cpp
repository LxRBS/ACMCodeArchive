#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#define MAXN 100005

using namespace std;

int main() {
	static long long a[MAXN];
	static long long t[MAXN];

	t[1] = 0;
	long long z = 2;
	long long zcnt = 0;
	long long z2 = 2;
	while (z2 < MAXN) {
		z *= 2LL;
		zcnt++;
		while ((z2 < MAXN) && (z2 < z)) {
			t[z2] = zcnt;
			z2++;
		}
	}

	long long N;
	scanf("%lli",&N);
	N--;

	long long LIM;
	scanf("%lli",&LIM);
	long long i;
	for (i = 0; i < N; i++) {
		scanf("%lli",&a[i]);
	}

	sort(a,a+N);
	reverse(a,a+N);

	long long res = 0;

	long long pos = 1;
	while ((pos < N) && (a[pos] == a[pos-1])) pos++;

	while (true) {
		//Every t[pos]+1 turns we are advancing first pos numbers by t[pos] and everything later by t[pos]+1.

		bool isTransition = false;
		if (pos < N) {
			long long num = a[pos-1] + res + (a[pos-1] - a[pos]) * t[pos];
			if (num <= LIM) {
				isTransition = true;
			}
		}

		if (isTransition) {
			res += (a[pos-1] - a[pos]) * (t[pos] + 1LL);
			pos++;
			while ((pos < N) && (a[pos] == a[pos-1])) pos++;
		} else {
			long long cur = a[pos-1] + res;
			long long cycles = (LIM - cur) / t[pos];
			res += cycles * (t[pos] + 1);
			cur += cycles * t[pos];
			res += LIM - cur;
			break;
		}

	}

	printf("%lli\n",res);
	
	return 0;
}
