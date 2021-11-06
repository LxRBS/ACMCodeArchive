#include "validator.h"

void run() {
	int n = Int(1, 2500);
	Endl();

	for (int i = 0; i < n; i++) {
		Int(0, n);
		Space();
		vector<int> vec = SpacedInts(n+2, 1, 1000*1000*1000);
		vec.push_back(vec.front());
		vec.erase(vec.begin());
		assert(is_sorted(vec.begin(), vec.end(), greater<int>()));
	}
}
