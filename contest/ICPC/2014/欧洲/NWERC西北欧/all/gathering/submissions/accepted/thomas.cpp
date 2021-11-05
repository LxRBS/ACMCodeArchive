// Solution to Gathering
// Author: Thomas Beuman

// Time complexity: O(n*log(n))
// Memory: O(n)

// Expected result: accepted

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <map>
using namespace std;

const int nMax = 100000, xMax = 1000000000;

int X[nMax], Y[nMax];
int X2[3*nMax+6], Y2[3*nMax+6];
long long Xsum[3*nMax+6];
map<int,long long> Ysum;

int main()
{	int i, j, mx, my, n, x, y;
	long long d, xplusy_min, xplusy_max, xminusy_min, xminusy_max, xmin, xmax, ymin, ymax;
	long long s, mindis;
	// Read input
	scanf("%d", &n);
	for (i = 0; i < n; i++)
		scanf("%d %d", &X[i], &Y[i]);
	scanf("%lld", &d);
	// Determine limits based on distance threshold
	xplusy_min = xminusy_min = -xMax;
	xplusy_max = xminusy_max = 2*xMax;
	for (i = 0; i < n; i++)
	{	xplusy_min = max(xplusy_min, X[i]+Y[i]-d);
		xplusy_max = min(xplusy_max, X[i]+Y[i]+d);
		xminusy_min = max(xminusy_min, X[i]-Y[i]-d);
		xminusy_max = min(xminusy_max, X[i]-Y[i]+d);
	}
	// Check limits
	if (xplusy_min > xplusy_max || xminusy_min > xminusy_max)
	{	printf("impossible\n");
		return 0;
	}
	// Find ideal location
	sort(X, X+n);
	sort(Y, Y+n);
	x = X[n/2];
	y = Y[n/2];
	// Check if it's within bounds
	if (x+y >= xplusy_min && x+y <= xplusy_max && x-y >= xminusy_min && x-y <= xminusy_max)
	{	mindis = 0;
		for (i = 0; i < n; i++)
			mindis += abs(x-X[i]) + abs(y-Y[i]);
	}
	else // Investigate border
	{	// Determine all interesting coordinates
		memcpy(X2, X, n*sizeof(int));
		memcpy(Y2, Y, n*sizeof(int));
		mx = my = n;
		// Add border extrema
		X2[mx++] = (xplusy_min + xminusy_min + 1) / 2;
		X2[mx++] = (xplusy_max + xminusy_max) / 2;
		Y2[my++] = (xplusy_min - xminusy_max + 1) / 2;
		Y2[my++] = (xplusy_max - xminusy_min) / 2;
		// Find y-coordinates on border corresponding to each x-coordinate
		for (i = 0; i < n+2; i++)
		{	x = X2[i];
			ymin = max(xplusy_min-x, x-xminusy_max); // Lower border
			ymax = min(xplusy_max-x, x-xminusy_min); // Upper border
			if (ymin <= ymax)
			{	Y2[my++] = ymin;
				Y2[my++] = ymax;
			}
		}
		// Find x-coordinates on border corresponding to each y-coordinate
		for (i = 0; i < n+2; i++)
		{	y = Y2[i];
			xmin = max(xplusy_min-y, y+xminusy_min); // Lower border
			xmax = min(xplusy_max-y, y+xminusy_max); // Upper border
			if (xmin <= xmax)
			{	X2[mx++] = xmin;
				X2[mx++] = xmax;
			}
		}
		sort(X2, X2+mx);
		sort(Y2, Y2+my);
		// Calculate and store all relevant distance sums for the x-coordinates
		// Note that sum[|x-xi|+|y-yi|] = sum[|x-xi|] + sum[|y-yi|]
		Xsum[0] = 0;
		for (i = 0; i < n; i++)
			Xsum[0] += X[i] - X2[0];
		j = 0;
		for (i = 1; i < mx; i++)
		{	for (; j < n && X[j] < X2[i]; j++); // j = #locations with X[loc] < X2[i]
			Xsum[i] = Xsum[i-1] + (long long)(j - (n-j)) * (X2[i] - X2[i-1]);
		}
		// Same for y-coordinates
		Ysum.clear();
		s = 0;
		for (i = 0; i < n; i++)
			s += Y[i] - Y2[0];
		Ysum[Y2[0]] = s;
		j = 0;
		for (i = 1; i < my; i++)
		{	for (; j < n && Y[j] < Y2[i]; j++); // j = #locations with Y[loc] < Y2[i]
			Ysum[Y2[i]] = s += (long long)(j - (n-j)) * (Y2[i] - Y2[i-1]);
		}
		// Find minimum
		mindis = 1ll << 60;
		for (i = 0; i < mx; i++)
		{	x = X2[i];
			ymin = max(xplusy_min-x, x-xminusy_max); // Lower border
			ymax = min(xplusy_max-x, x-xminusy_min); // Upper border
			if (ymin <= ymax)
			{	if (Ysum.count(ymin))
					mindis = min(mindis, Xsum[i] + Ysum[ymin]);
				if (Ysum.count(ymax))
					mindis = min(mindis, Xsum[i] + Ysum[ymax]);
			}
		}
	}
	printf("%lld\n", mindis);
	return 0;
}
