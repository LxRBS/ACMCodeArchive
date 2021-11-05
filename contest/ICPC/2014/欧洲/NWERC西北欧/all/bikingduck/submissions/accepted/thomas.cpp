// Solution to Lucky Bikes
// Author: Thomas Beuman

// Time complexity: O(n^2)
// Memory: O(n)

// Expected result: accepted

/* Solution method: Binary search
 *
 * Let alpha be the angle (with respect to the normal) at which you walk to a bound,
 *   and beta the angle at which you bike away from it.
 * Then, for the optimal location, sin(alpha)/sin(beta) = vw/vb  (Snell's law)
 */

#include <algorithm>
#include <cstdio>
#include <cmath>
using namespace std;

const int N = 1000;

double vw, vb, xmax, ymax, xs, ys, xd, yd;
double ttime, idx, critangle;
double X[N], Y[N];

double dis (double x1, double y1, double x2, double y2)
{	return sqrt(pow(x1-x2,2) + pow(y1-y2,2));
}

// Calculates travel time S->1->2->D and updates minimum
void update_time (double x1, double y1, double x2, double y2)
{	ttime = min(ttime, (dis(xs,ys, x1,y1) + dis(x2,y2, xd,yd)) / vw + dis(x1,y1, x2,y2) / vb);
}

// Finds x that minimizes the time needed to walk from (x1,y1) to (x,0) and bike to (x2,y2)
// Calculates the time, adds t0 and updates minimum
void singlebound (double x1, double y1, double x2, double y2, double t0)
{	if (x1 > x2)
		return;
	int t;
	double x, lb, ub, walkangle, bikeangle;
	// Binary search over the angle
	lb = 0;
	ub = min(atan2(x2-x1, y1), critangle);
	for (t = 0; t < 100; t++)
	{	walkangle = (lb+ub)/2; // Incoming angle at bound 1
		bikeangle = asin(sin(walkangle)/idx); // Outgoing angle at bound 1
		x = x1 + y1 * tan(walkangle); // Location at bound 1 (= (x,0))
		if (y2 * tan(bikeangle) < x2-x) // Compare with bikeangle
			lb = walkangle;
		else
			ub = walkangle;
	}
	ttime = min(ttime, t0 + dis(x1,y1, x,0) / vw + dis(x,0, x2,y2) / vb);
}

// Rotate coordinates counterclockwise by 90 degrees
void rotate (double& x, double& y)
{	double x0 = x, y0 = y;
	x = ymax - y0;
	y = x0;
}

int main()
{	int n, i, j, s, t;
	double xmin, ymin, x, y;
	scanf("%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %d",
	      &vw, &vb, &xmin, &ymin, &xmax, &ymax, &xs, &ys, &xd, &yd, &n);
	// Translate system so that (xmin,ymin) = (0,0)
	xmax -= xmin; xs -= xmin; xd -= xmin;
	ymax -= ymin; ys -= ymin; yd -= ymin;
	for (i = 0; i < n; i++)
	{	scanf("%lf %lf", &x, &y);
		X[i] = x - xmin;
		Y[i] = y - ymin;
	}
	/*** Direct path ***/
	ttime = dis(xs,ys, xd,yd) / vw;
	if (vw < vb)
	{	double lb, ub, walk1angle, walk2angle, bikeangle;
		idx = vw/vb; // Refraction index
		critangle = asin(idx); // Largest possible incoming angle
		/*** Via two stations ***/
		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
				update_time(X[i], Y[i], X[j], Y[j]);
		// Try all orientations of the system (so that we can always use the south bound w.l.o.g.)
		for (s = 0; s < 8; s++)
		{	/*** Bike between station and south bound ***/
			for (i = 0; i < n; i++)
			{	singlebound(xs,ys, X[i],Y[i], dis(X[i],Y[i], xd,yd)/vw); // from bound to station
				singlebound(xd,yd, X[i],Y[i], dis(X[i],Y[i], xs,ys)/vw); // from station to bound
			}
			/*** Bike along south bound ***/
			// (equivalent to going from (xs,ys+yd) to (xd,0))
			if (xs < xd)
			{ // Come in at critangle
				x = xs + (ys+yd)*tan(critangle);
				if (x < xd)
					ttime = min(ttime, dis(xs,ys+yd, x,0) / vw + (xd-x) / vb);
			}
			/*** Bike from south bound to west bound ***/
			// Binary search over the angle
			lb = 0;
			ub = min(atan2(xs, ys), critangle);
			for (t = 0; t < 100; t++)
			{	walk1angle = (lb+ub)/2; // Incoming angle at south bound
				bikeangle = asin(sin(walk1angle)/idx); // Outgoing angle at south bound
				walk2angle = asin(cos(bikeangle)*idx); // Outgoing angle at west bound
				x = xs - ys * tan(walk1angle); // Location at south bound (= (x,0))
				y = yd - xd * tan(walk2angle); // Location at west bound (= (0,y))
				if (y * tan(bikeangle) < x) // Compare with bikeangle
					lb = walk1angle;
				else
					ub = walk1angle;
			}
			update_time(x,0, 0,y);
			/*** Bike from south bound to north bound ***/
			// (equivalent to going from (xs,ys+ymax-yd) to (xd,ymax))
			singlebound(xs,ys+ymax-yd, xd,ymax, 0);
			// Rotate system
			rotate(xs, ys);
			rotate(xd, yd);
			for (i = 0; i < n; i++)
				rotate(X[i], Y[i]);
			swap(xmax, ymax);
			if (s == 3)
			{	// Flip sytem horizontally
				xs = xmax - xs;
				xd = xmax - xd;
				for (i = 0; i < n; i++)
					X[i] = xmax - X[i];
			}
		}
	}
	printf("%lf\n", ttime);
	return 0;
}
