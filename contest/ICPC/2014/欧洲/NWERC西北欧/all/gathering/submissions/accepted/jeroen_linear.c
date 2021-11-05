/*
 * NWERC'14 - Solution by Jeroen Bransen
 *
 * This solution is O(N), which is much faster than necessary for the contest
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
#define SWAP(a,b) { typeof(a) tmp; tmp = a; a = b; b = tmp; }

int n;
int64_t x[MAXN], y[MAXN];
int64_t pts[MAXN*2];
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

int64_t gety(int64_t xline, int64_t yline, bool up) {
	return yline - getx(xline, yline, !up);
}

// Median computation in O(N^2), only used
// for lists with n <= 5
int64_t median_small(int64_t *nums, int left, int right) {
	int i, j, n;
	n = right - left + 1;
	for(i = left; i <= left + n / 2; i++)
		for(j = i + 1; j <= right; j++)
			if(nums[j] < nums[i])
				SWAP(nums[i], nums[j]);
	return left + n / 2;
}

// Median computation in O(N)
// From http://en.wikipedia.org/wiki/Quickselect
// and http://en.wikipedia.org/wiki/Median_of_medians
int partition(int64_t *nums, int left, int right, int pivotIdx) {
	int i, st;
	int64_t pivotVal;

	pivotVal = nums[pivotIdx];
	SWAP(nums[pivotIdx], nums[right]);
	st = left;
	for(i = left; i < right; i++) {
		if(nums[i] < pivotVal) {
			SWAP(nums[st], nums[i]);
			st++;
		}
	}
	SWAP(nums[right], nums[st]);
	return st;
}

int medianOfMedians(int64_t *nums, int left, int right);

int selectIdx(int64_t *nums, int left, int right, int k) {
	int pivotIdx;

	if(left == right) return k;

	pivotIdx = medianOfMedians(nums, left, right);
	pivotIdx = partition(nums, left, right, pivotIdx);
	if(pivotIdx == left || k == pivotIdx)
		return k;
	else if(k < pivotIdx)
		return selectIdx(nums, left, pivotIdx - 1, k);
	else
		return selectIdx(nums, pivotIdx + 1, right, k);
}

int medianOfMedians(int64_t *nums, int left, int right) {
	int numMedians, i, medianIdx, subLeft, subRight;
	numMedians = ((right - left) + 4) / 5;
	for(i = 0; i < numMedians; i++) {
		subLeft = left + i * 5;
		subRight = subLeft + 4;
		if(subRight > right) subRight = right;
		medianIdx = median_small(nums, subLeft, subRight);
		SWAP(nums[left+i], nums[medianIdx]);
	}
	return selectIdx(nums, left, left + numMedians - 1, left + numMedians / 2);
}

int64_t median(int64_t *nums, int n) {
	int idx = selectIdx(nums, 0, n - 1, n / 2);
	return nums[idx];
}

// Checking the answer, O(n)
int64_t ans;
void check(int64_t xt, int64_t yt) {
	int i;
	
	// Check if point is within boundaries
	if(!(minx <= xline(xt,yt) && xline(xt,yt) <= maxx
	     && miny <= yline(xt,yt) && yline(xt,yt) <= maxy)) return;

	// Compute answer
	int64_t curans = 0;
	for(i = 0; i < n; i++)
		curans += ABS(x[i] - xt) + ABS(y[i] - yt);

	// Update best found
	if(curans < ans)
		ans = curans;
}

// Main
int main() {
	int i, j;
	int64_t d, xm, ym;

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

	// Now check different interesting locations
	ans = INF;

	// Optimal point (median)
	xm = median(x, n);
	ym = median(y, n);
	check(xm,ym);

	// 8 corners
	check(getx(minx,miny,true ),gety(minx,miny,true ));
	check(getx(minx,miny,true ),gety(minx,miny,false));
	check(getx(minx,maxy,false),gety(minx,maxy,false));
	check(getx(minx,maxy,true ),gety(minx,maxy,false));
	check(getx(maxx,maxy,false),gety(maxx,maxy,true ));
	check(getx(maxx,maxy,false),gety(maxx,maxy,false));
	check(getx(maxx,miny,true ),gety(maxx,miny,true ));
	check(getx(maxx,miny,false),gety(maxx,miny,true ));

	// Do the following once for each border of the bounding box
	int border[4][3] = {
		{minx, 1, -minx}, // left top
		{maxx, 1, -maxx}, // right bottom
		{miny, -1, miny}, // left bottom
		{maxy, -1, maxy}  // right top
	};

	for(i = 0; i < 4; i++) {
		// Duplicate all points such that one point on the border shares
		// the x coordinate with point j and the other the y coordinate
		// with point j. This essentially converts the problem to a 1D variant
		for(j = 0; j < n; j++) {
			pts[j*2] = x[j];
			pts[j*2+1] = border[i][0] + border[i][1] * y[j];
		}

		// Find the median of those points on the line and check if this
		// is the best answer found so far
		xm = median(pts, n * 2);
		ym = border[i][1] * xm + border[i][2];
		check(xm,ym);
	}

	// Print answer
	printf("%lld\n", ans);
	return 0;
}
