/*
 * NWERC'14 - Solution by Jeroen Bransen
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double p, s, v;
int n;

double f(double c) {
	return (n * pow(log(n) / log(2), c * sqrt(2))) / (p * pow(10,9)) + s * (1 + 1 / c) / v;
}

int main() {
	double low, high, a1, a2;

	scanf("%d %lf %lf %lf\n", &n, &p, &s, &v);

	low = 1e-9;
	high = 100;
	
	for(int i = 0; i < 10000; i++) {
		a1 = (low + low + high) / 3;
		a2 = (low + high + high) / 3;
		if(f(a1) < f(a2))
			high = a2;
		else
			low = a1;
	}

	printf("%.11lf %.11lf\n", f(low), low);

	return 0;
}
