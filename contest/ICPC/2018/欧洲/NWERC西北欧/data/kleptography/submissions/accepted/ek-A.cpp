#include <cstdio>
#include <cstring>
#include <cstdlib>
#define MAXN 105

using namespace std;

int main() {
	static char s[MAXN];
	static int a[MAXN];
	static int b[MAXN];

	int K, N;
	scanf("%d %d",&K,&N);

	scanf("%s",s);
	int i;
	for (i = 0; i < K; i++) {
		a[N-K+i] = (int)(s[i] - 'a');
	}

	scanf("%s",s);
	for (i = 0; i < N; i++) {
		b[i] = (int)(s[i] - 'a');
	}

	for (i = N-K-1; i >= 0; i--) {
		a[i] = (26 - a[i+K] + b[i+K]) % 26;
	}

	for (i = 0; i < N; i++) {
		s[i] = (char)(a[i] + 'a');
	}
	s[N] = 0;
	printf("%s\n", s);
	
	return 0;
}
