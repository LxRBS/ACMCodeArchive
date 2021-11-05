// Testdata generator
// Author: Thomas

#include <algorithm>
#include <cstdio>
#include <queue>
#include <string>
#include <vector>
using namespace std;

#define update_min(a,b) if(b<a) a=b
#define update_max(a,b) if(b>a) a=b

const int nMax = 100000, xMax = 1000000000;
vector<int> L[nMax];

// RNG (modulo 2^31)
int randnr()
{	static int rseed = 42;
	return rseed = (1103515245 * rseed + 12345) & 0x7fffffff;
}

string itos (int n)
{	string s = "##";
	s[0] = '0'+n/10;
	s[1] = '0'+n%10;
	return s;
}

void makecase (int nr, string descr, int n, int d)
{	string filename = "secret/" + itos(nr) + (descr == "" ? "" : "-" + descr) + ".in";
	FILE* out = fopen(filename.c_str(), "w");
	fprintf(out, "%d\n", n);
	for (int i = 0; i < n; i++)
		fprintf(out, "%d %d\n", L[i][0], L[i][1]);
	fprintf(out, "%d\n", d);
	fclose(out);
}

void rotate (int n, int xmax)
{	int i, x, y;
	for (i = 0; i < n; i++)
	{	x = xmax - L[i][1];
		y = L[i][0];
		L[i] = {x,y};
	}
}

void flip (int n, int xmax)
{	int i;
	for (i = 0; i < n; i++)
		L[i][0] = xmax - L[i][0];
}

int main()
{	int nr, n, d, i, x, y;
	long long xplusy_min, xplusy_max, xminusy_min, xminusy_max, dmin, dmax;

	// Base cases
	nr = 1;
	L[0] = {0,0};
		L[1] = {0,0};
	makecase(nr++, "twopeople-sameloc", 2, 0);
		L[1] = {0,1};
	makecase(nr++, "twopeople-apart", 2, 1);
	makecase(nr++, "twopeople-toofar", 2, 0);
		L[1] = {0,10};
			L[2] = {10,0};
				L[3] = {10,10};
	makecase(nr++, "onepossibleloc", 4, 10);
			L[2] = {9,0};
				L[3] = {9,10};
					L[4] = {0,0};
	makecase(nr++, "twopossiblelocs", 5, 10);
					L[4] = {9,0};
	makecase(nr++, "twopossiblelocs", 5, 10);

	nr = 11;
	// Range of possible locations completely inside median "box"
	L[0] = {0,0};
	L[1] = {0,10};
	L[2] = {10,0};
	L[3] = {10,10};
	L[4] = {1,8};
	L[5] = {9,2};
	makecase(nr++, "", 6, 12);
	// Partial overlap between range and box
	makecase(nr++, "", 6, 15);
	// Ideal location not a trivial projection of the median
	L[0] = {0,0};
	L[1] = {0,100};
	L[2] = {100,0};
	L[3] = {100,100};
	L[4] = {0,0};
	L[5] = {10,10};
	L[6] = {23,28};
	makecase(nr++, "", 7, 150);

	// Several locations of median w.r.t. range
	nr = 21;
	L[0] = {0,0};
	L[1] = {0,100};
	L[2] = {100,0};
	L[3] = {100,100};
	L[4] = {50,20}; // On corner
	makecase(nr++, "", 5, 130);	
	L[4] = {50,10}; // Straight below corner
	makecase(nr++, "", 5, 130);	
	L[4] = {60,0}; // A bit off
	makecase(nr++, "", 5, 130);	
	L[4] = {60,10}; // On extension of diagonal
	makecase(nr++, "", 5, 130);	
	L[4] = {65,35}; // On diagonal
	makecase(nr++, "", 5, 130);	
	L[4] = {70,30}; // Close to diagonal
	makecase(nr++, "", 5, 130);	
	L[4] = {90,10}; // Far from diagonal
	makecase(nr++, "", 5, 130);

	// Ideal location on extremity of range (no matching coordinate in input)
	nr = 31;
	L[0] = {0,0};
	L[1] = {0,75};
	L[2] = {100,25};
	L[3] = {100,100};
	L[4] = {10,60};
	L[5] = {10,60};
	L[6] = {10,90};
	for (int s = 0; s < 8; s++)
	{	makecase(nr++, "location-on-corner-of-range" + string(1, '1'+s), 7, 125);
		rotate(7, 100);
		if (s == 3)
			flip(7, 100);
	}

	// Ideal location shares one coordinate with input
	nr = 41;
	L[0] = {0,0};
	L[1] = {0,75};
	L[2] = {100,25};
	L[3] = {100,100};
	L[4] = {20,20};
	L[5] = {20,30};
	L[6] = {10,80};
	for (int s = 0; s < 8; s++)
	{	makecase(nr++, "location-shares-single-coordinate" + string(1, '1'+s), 7, 125);
		rotate(7, 100);
		if (s == 3)
			flip(7, 100);
	}

	// Random
	for (nr = 51; nr <= 80; nr++)
	{	n = (nr > 70 ? nMax : 2 + randnr() % (nMax-1));
		priority_queue<int> Xheap, Yheap;
		xplusy_min = xminusy_min = 2*xMax;
		xplusy_max = xminusy_max = -xMax;
		for (i = 0; i < n; i++)
		{	x = randnr() % (xMax+1);
			y = randnr() % (xMax+1);
			L[i] = {x,y};
			update_min(xplusy_min, x+y);
			update_max(xplusy_max, x+y);
			update_min(xminusy_min, x-y);
			update_max(xminusy_max, x-y);
			Xheap.push(x);
			Yheap.push(y);
		}
		// Poor man's way of determining median without sorting
		for (i = 0; i < n/2; i++)
		{	Xheap.pop();
			Yheap.pop();
		}
		x = Xheap.top();
		y = Yheap.top();
		// Calculate smallest d that avoids "impossible"
		dmin = max((xplusy_max-xplusy_min+1)/2, (xminusy_max-xminusy_min+1)/2);
		// Calculate smallest d that makes median reachable by all
		dmax = max(max(x+y-xplusy_min, xplusy_max-x-y), max(x-y-xminusy_min, xminusy_max-x+y));
		if (randnr() % 5 == 0)
			d = dmin-1; // Create "impossible"
		else if (randnr() % 5 == 0)
			d = dmax; // Median in range
		else
			d = dmin + randnr() % (dmin==dmax ? 1 : dmax-dmin); // Median out of range
		makecase(nr, "random", n, d);
	}
	return 0;
}
