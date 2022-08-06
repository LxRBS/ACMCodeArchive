#include<bits/stdc++.h>
#define LL unsigned long long
using namespace std;

const int maxn = 1e5 + 5;
int n;
int a;
int bcnt[25];
LL sum, ea2;

LL gcd(LL a, LL b) {
	return b ? gcd(b, a % b) : a;
}

int main() {
	scanf("%d", &n);
	//n = 100000;
	for(int i = 1; i <= n; ++i) {
		scanf("%d", &a);
		//a = 32767;
		sum += a;
		for(int j = 0, p = 1; j <= 15; ++j, p <<= 1) 
			bcnt[j] += ((a & p) != 0);
	}
	LL tmp = 0;
	for(int i = 1; i <= n; ++i) {
		tmp = 0;
		for(int j = 0, p = 1; j <= 15; ++j, p <<= 1)
			if(i <= bcnt[j]) tmp += p;
		ea2 += tmp * tmp;
	}
	LL ans = n * ea2 - sum * sum;
	LL div = 1ull * n * n;
	LL d = gcd(ans, div);
	printf("%llu/%llu", ans / d, div / d);
	return 0;
}