// Solution to Luggage coordination
// Author: Thomas Beuman

// Time complexity: O(n^2*log(n))
// Memory: O(n)

// Expected result: accepted

#include <algorithm>
#include <cstdio>
#include <set>
#include <utility>
using namespace std;

const int nmax = 2000;

int Slot[nmax];
multiset<int> S;

long long gcd (long long a, long long b)
{	return b ? gcd(b, a%b) : a;
}

int main()
{	int n, p, r, i, j, s;
	long long tmin = 1ll<<60, tmax = 0, tsum = 0, t, d;
	multiset<int>::iterator it;
	scanf("%d %d %d\n", &n, &p, &r);
	for (i = 0; i < n; i++)
		scanf("%d", &Slot[i]);
	sort(Slot, Slot+n);
	for (i = 0; i < n; i++)
		if (i == 0 || Slot[i] > Slot[i-1])
		{	S.clear();
			for (j = 0; j < n; j++)
				S.insert(Slot[j]);
			s = Slot[i];
			t = -s;
			while (!S.empty())
			{	it = S.lower_bound(s);
				if (it == S.end())
				{	it = S.begin();
					t += p;
				}
				s = *it + r;
				t += p*(s/p);
				s %= p;
				S.erase(it);
			}
			t += s;
			d = (i == 0 ? p + Slot[0] - Slot[n-1] : Slot[i] - Slot[i-1]);
			tmin = min(tmin, t);
			tmax = max(tmax, t+d-1);
			tsum += d*t + (d*(d-1))/2;
		}
	d = gcd(tsum, p);
	printf("%lld\n%lld\n%lld/%lld\n", tmin, tmax, tsum/d, p/d);
	return 0;
}
