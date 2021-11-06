#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#define MAXN 500005

using namespace std;

int main() {
	static char a[MAXN];
	memset(a,0,sizeof(a));

	int N, C, B;
	scanf("%d %d %d",&N,&C,&B);

	int i;
	for (i = 0; i < B; i++) {
		int j;
		scanf("%d",&j);
		j--;
		a[j] = '0';
	}

	if (C % 2) {
		C--;
		a[0] = '1';
	}

	i = N-2;
	while (C) {
		if (a[i] == '0') {
			i--;
		} else {
			a[i] = '1';
			a[i-1] = '0';
			i -= 2;
			C -= 2;
		}
	}

	while (i >= 0) {
		if (a[i] != '1') {
			a[i] = '0';
		}
		i--;
	}

	printf("%s\n",a);
	
	return 0;
}
