#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

#define MAXN 100000
#define INF 10000000000
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define ABS(a) ((a) < 0 ? -(a) : (a))

int64_t x[MAXN], y[MAXN];
int64_t sortx[MAXN], sorty[MAXN];

int64_t xline(int64_t x, int64_t y) {
	return x - y;
}

int64_t yline(int64_t x, int64_t y) {
	return x + y;
}

int compare_int64(const void *_a, const void *_b) {
	int64_t a = *(int64_t *)_a;
	int64_t b = *(int64_t *)_b;
	if(a < b) return -1;
	if(a > b) return 1;
	return 0;
}

int main() {
	int n, i;
	int64_t d, minx, maxx, miny, maxy, dx, dy, xt, yt, ans, amount;
	bool xup, yup;
	scanf("%d\n", &n);
	for(i = 0; i < n; i++)
		scanf("%lld %lld\n", &x[i], &y[i]);
	scanf("%lld\n", &d);

	// Construct bounding box	
	minx = miny = -INF;
	maxx = maxy = INF;
	for(i = 0; i < n; i++) {
		minx = MAX(minx, xline(x[i] - d, y[i]));
		maxx = MIN(maxx, xline(x[i] + d, y[i]));
		miny = MAX(miny, yline(x[i], y[i] - d));
		maxy = MIN(maxy, yline(x[i], y[i] + d));
	}

	// Check if bounding box is nonempty
	if(minx > maxx || miny > maxy) {
		printf("impossible\n");
		return 0;
	}

	// Find optimal point (median)
	memcpy(sortx, x, sizeof(x));
	memcpy(sorty, y, sizeof(y));
	qsort(sortx, n, sizeof(int64_t), compare_int64);
	qsort(sorty, n, sizeof(int64_t), compare_int64);
	xt = sortx[n/2];
	yt = sorty[n/2];
	
	// Move point such that it falls in the bounding box
	// (should take no more than 3 iterations)
	while(!(minx <= xline(xt,yt) && xline(xt,yt) <= maxx
		   && miny <= yline(xt,yt) && yline(xt,yt) <= maxy)) {
		dx = MAX(0, MAX(minx - xline(xt,yt), xline(xt,yt) - maxx));
		dy = MAX(0, MAX(miny - yline(xt,yt), yline(xt,yt) - maxy));
		xup = xline(xt,yt) <= minx;
		yup = yline(xt,yt) <= miny;
		amount = MAX(1,MIN(dx,dy));
		if(dx == 0 && dy > 1) {
			xt += yup ? dy / 2 : -(dy / 2);
			yt += yup ? dy / 2 : -(dy / 2);
		}
		else if(dy == 0 && dx > 1) {
			xt += xup ? dx / 2 : -(dx / 2);
			yt -= xup ? dx / 2 : -(dx / 2);
		}
		else if(xup && yup)
			xt += amount;
		else if(xup && !yup)
			yt -= amount;
		else if(!xup && yup)
			yt += amount;
		else
			xt -= amount;
	}

	// Construct and print answer
	ans = 0;
	for(i = 0; i < n; i++)
		ans += ABS(x[i] - xt) + ABS(y[i] - yt);
	printf("%lld\n", ans);

	return 0;
}
