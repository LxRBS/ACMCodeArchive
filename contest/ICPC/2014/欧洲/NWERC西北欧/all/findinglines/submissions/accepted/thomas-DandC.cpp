// Solution to Line Drawing
// Author: Thomas Beuman

// Time complexity: O(n*log(n)/(p/100))
// Memory: O(n)

// Expected result: accepted

// Solution method: divide and conquer

#include <cstdio>
#include <cmath>
#include <set>
using namespace std;

const int N = 1000000;

int X[N], Y[N];

int gcd (int a, int b)
{	return b ? gcd(b, a%b) : a;
}

struct line
{	long long a, b, c; // ax+by=c
	line() {}
	// Construct line through (x1,y1) and (x2,y2)
	line (int x1, int y1, int x2, int y2)
	{	int d = gcd(abs(x1-x2), abs(y1-y2));
		if (x1-x2 < 0)
			d = -d;
		a = -(y1-y2)/d;
		b = (x1-x2)/d;
		c = a*x1 + b*y1;
	}
};

bool operator < (line L1, line L2)
{	return L1.a < L2.a || (L1.a == L2.a && (L1.b < L2.b || (L1.b == L2.b && L1.c < L2.c)));
}

set<line> findlines (int first, int last, int p)
{	int mid = (first+last)/2;
	int a, b, c, i, j, m;
	set<line> S, S1;
	if (p*(mid-first) <= 100) // Too few points left to split
	{	for (i = first; i < last; i++)
			for (j = i+1; j < last; j++)
				S1.insert(line(X[i], Y[i], X[j], Y[j]));
	}
	else
	{	S1 = findlines(first, mid, p);
		set<line> S2 = findlines(mid, last, p);
		S1.insert(S2.begin(), S2.end());
	}
	set<line>::iterator it;
	for (it = S1.begin(); it != S1.end(); it++)
	{	a = it->a;
		b = it->b;
		c = it->c;
		m = 0;
		for (i = first; i < last; i++)
			if (a*X[i] + b*Y[i] == c)
				m++;
		if (100*m >= p*(last-first))
			S.insert(*it);
	}
	return S;
}

int main()
{	int n, p, i;
	scanf("%d %d", &n, &p);
	for (i = 0; i < n; i++)
		scanf("%d %d", &X[i], &Y[i]);
	printf("%spossible\n", n == 1 || !findlines(0, n, p).empty() ? "" : "im");
	return 0;
}
