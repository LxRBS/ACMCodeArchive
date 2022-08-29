//1012, std
#include <bits/stdc++.h>
using namespace std;

#define int long long

const int N = 2e6 + 5;

int n, k, cnt[N], m, ct = 0, d, all;

bool pd(int x) {
	int ct = k, dd = all, bas = cnt[x - 1];
	for(int i = x; ; ++ i) {
		int tt = (bas << (i - x + 1));
		if(tt > dd) {
			ct -= dd * i; dd = 0; break;
		} else {
			ct -= tt * i;
			dd -= tt;
		}
		
	}
	return ct >= 0;
}

void rmain() {
//	freopen("myout.txt", "w", stdout);
	cin >> k;
	for(int i = 0; i * (i - 1) / 2 <= k; ++ i) {
		cnt[i] = 0;
	}
	ct = d = all = n = 0;
	if(k & 1) {
		puts("-1");
		return;
	} else {
		if(!k) {
			puts("1 0");
			puts("1");
			return;
		}
		k /= 2;
		if(k == 2 || k == 4 || k == 7) return (void)puts("-1");
		int cxt = 0;
		d = 0;
		cnt[1] = 1;
		for(int i = 1; ; ++ i) {
			cxt += i;
			if(cxt > k) {
				d = i - 1;
				cxt -= i;
				break;
			}
		}
		if(cxt == k) {
			printf("%lld %lld\n", 2 * d + 1, d);
			printf("1 ");
			for(int i = 1; i < d; ++ i) printf("2 ");
			printf("2");
			puts("");
			return;
		}
		
		int lst = 1;
		
		all = d + 1;
		
		printf("%lld ", 2 * d + 3);
		
		for(int i = 1; k; ++ i) {
			for(int j = 1; j <= min(lst, all); ++ j) {
				all -= j; k -= j * i;
				cnt[i] = j;
				assert(k >= 0);
				if(pd(i + 1)) {
					cnt[i] = j;
					break;
				}
				all += j; k += j * i;
			}
			lst = cnt[i] * 2;
		}
		
		int tot = 0;
		for(int i = 1; cnt[i]; ++ i) {
			tot = i;
		} 
		printf("%lld\n", tot);
		printf("1");
		for(int i = 1; cnt[i]; ++ i) 
		printf(" %lld", cnt[i] * 2);
		puts("");
	}
}

main() {
	int T;
//	freopen("mid_ct.in", "r", stdin);
//	freopen("mid_ct.out", "w", stdout);
	for(cin >> T; T --;) {
		rmain();
	}
}
