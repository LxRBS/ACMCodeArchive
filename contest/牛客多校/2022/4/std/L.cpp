#include<bits/stdc++.h>
using namespace std;

long double PI = acosl(-1);

void shrink(int &n, long double &a) {
	int N = -1; long double A;
	if(n == -1) return ;
	if(n == 4) {
		N = 4;
		A = a / 3;
	}
	if(n == 6) {
		N = 8;
		A = a / sqrtl(2);
	}
	if(n == 8) {
		N = 6;
		A = sqrtl(2) * a / 3;
	}
	if(n == 12) {
		N = 20;
		A = a * (3 * sqrtl(5) + 5) / 10;
	}
	if(n == 20) {
		N = 12;
		A = a * (sqrtl(5) + 1) / 6;
		//A = 2 * a * cosl(PI / 5) / 3;
	}
	n = N, a = A;
}

int n;
long double a;
int k, T;

int main() {
	scanf("%d", &T);
	while(T--) {
		scanf("%d%Lf%d", &n, &a, &k);
		while(k--)
			shrink(n, a);
		if(n == -1) printf("impossible\n");
		else printf("possible %d %.12Lf\n", n, a);
	}
	return 0;
}