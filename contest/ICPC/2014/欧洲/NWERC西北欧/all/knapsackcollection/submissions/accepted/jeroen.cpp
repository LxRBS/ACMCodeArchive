/*
 * NWERC'14 - Solution by Jeroen Bransen
 */

#include <iostream>
#include <set>
#include <cstring>

using namespace std;

long long P, R;

// Solve for a certain begin position, O(N log N)
long long solve(multiset<long long> luggage, long long pos) {
	long long ret = 0;
	while(!luggage.empty()) {
		// Find next bag >= pos
		multiset<long long>::iterator it = luggage.lower_bound(pos);

		// Or first bag if there is no such bad
		if(it == luggage.end()) it = luggage.begin();

		// Add time it takes to wait for this bag
		ret += R + ((*it - pos + P) % P);

		// Now we're at that position and wait another R time units
		pos = (*it + R) % P;

		// We've picked up this bad
		luggage.erase(it);
	}
	return ret;
}

long long gcd(long long a, long long b) {
	return a == 0 ? b : gcd(b%a, a);
}

int main() {
	int N;
	cin >> N >> P >> R;
	multiset<long long> luggage;
	long long maxl = 0;
	for(int i = 0; i < N; i++) {
		long long li;
		cin >> li;
		luggage.insert(li);
		maxl = max(maxl, li);
	}

	long long prev = maxl - P;
	long long sum = 0;
	long long minimum = 0;
	long long maximum = 0;

	// Solve for each different starting position
	for(multiset<long long>::iterator it = luggage.begin(); it != luggage.end(); it++) {
		if(*it == prev) continue;
		multiset<long long> lug2 = multiset<long long>(luggage.begin(), luggage.end());
		long long cur = solve(lug2, *it);

		// Update maximum and minimum, be smart about previous positions (since last bag)
		minimum = it == luggage.begin() ? cur : min(minimum, cur);
		maximum = max(maximum, cur + (*it - prev - 1));

		// Add to sum, also be smart about previous positions without a bag
		sum += cur * (*it - prev);
		sum += (*it - prev) * (*it - prev - 1) / 2;
		prev = *it;
	}

	// Print the answers and make sure to reduce the fraction
	cout << minimum << endl;
	cout << maximum << endl;
	long long g = gcd(sum, P);
	cout << (sum / g) << '/' << (P / g) << endl;

	return 0;
}
