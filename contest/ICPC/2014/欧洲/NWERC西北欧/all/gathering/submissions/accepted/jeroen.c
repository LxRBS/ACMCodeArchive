/*
 * NWERC'14 - Solution by Jeroen Bransen
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

#define MAXN 100000
#define INF 1000000000000000000
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define ABS(a) ((a) < 0 ? -(a) : (a))

int n;
int64_t x[MAXN], y[MAXN];
int64_t sortx[MAXN], sorty[MAXN];
int64_t minx, maxx, miny, maxy;

// Convert between coordinates and line index. We number lines from bottom-left
// to right-top with the x-coordinate at which they intersect with the x-axis,
// and the lines from left-top to bottom-right with the y
int64_t xline(int64_t x, int64_t y) {
	return x - y;
}

int64_t yline(int64_t x, int64_t y) {
	return x + y;
}

int64_t getx(int64_t xline, int64_t yline, bool up) {
	return (xline + yline + (up ? 1 : 0)) / 2;
}

int64_t gety(int64_t xline, int64_t yline) {
	return yline - getx(xline, yline, false);
}

// For sorting
int compare_int64(const void *_a, const void *_b) {
	int64_t a = *(int64_t *)_a;
	int64_t b = *(int64_t *)_b;
	if(a < b) return -1;
	if(a > b) return 1;
	return 0;
}

int64_t getans(int64_t xt, int64_t yt) {
	int i;
	// Check if within boundaries (makes ternary search easier)
	if(!(minx <= xline(xt,yt) && xline(xt,yt) <= maxx
			 && miny <= yline(xt,yt) && yline(xt,yt) <= maxy)) return INF;

	// Compute answer
	int64_t ans = 0;
	for(i = 0; i < n; i++)
		ans += ABS(x[i] - xt) + ABS(y[i] - yt);
	return ans;
}


// Main
int main() {
	int i;
	int64_t d, xt, yt, ans, up, low, act1, act2, ans1, ans2, x1, y1, x2, y2;

	// Input reading
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
	
	// If it falls in bounding box we're done
	if(minx <= xline(xt,yt) && xline(xt,yt) <= maxx
		 && miny <= yline(xt,yt) && yline(xt,yt) <= maxy) {
		printf("%lld\n", getans(xt,yt));
		return 0;
	}

	// The optimal answer must be somewhere on border of the bounding box
	ans = INF;

	// Ternary search over each border:
	// i == 0: left-bottom
	// i == 1: right-top
	// i == 2: left-top
	// i == 3: right-bottom
	for(i = 0; i < 4; i++) {
		low = (i < 2 ? minx : miny);
		up = (i < 2 ? maxx : maxy) + 2;
		do {
			act1 = (low + low + up) / 3;
			act2 = (low +  up + up) / 3;
			x1 = i < 2 ? act1 : i == 2 ? minx : maxx;
			y1 = i > 1 ? act1 : i == 0 ? miny : maxy;
			ans1 = getans(getx(x1,y1,i>1),gety(x1,y1));
			x2 = i < 2 ? act2 : i == 2 ? minx : maxx;
			y2 = i > 1 ? act2 : i == 0 ? miny : maxy;
			ans2 = getans(getx(x2,y2,i>1),gety(x2,y2));
			if(ans1 < ans2) {
				up = act2;
				ans = MIN(ans, ans1);
			} else {
				low = act1;
				ans = MIN(ans, ans2);
			}
		} while(up - low > 2);
	}

	printf("%lld\n", ans);
	return 0;
}
