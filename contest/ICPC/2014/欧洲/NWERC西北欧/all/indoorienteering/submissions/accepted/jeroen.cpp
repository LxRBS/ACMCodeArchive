/*
 * NWERC'14 - Solution by Jeroen Bransen
 */

#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

#define MAXN 14

long long dst[MAXN][MAXN];

int main() {
	// Read input
	int N;
	long long L;
	cin >> N >> L;
	for(int i = 0; i < N; i++)
		for(int j = 0; j < N; j++)
			cin >> dst[i][j];
	
	// Meet in the middle approach, try to make a route
	// from 0 to midpoint in two distinct ways
	bool possible = false;
	for(int midpoint = 1; midpoint < N; midpoint++) {
		// Loop over every set of (N-2)/2 nodes
		int half = (N - 2) / 2;
		for(int mask = 0; mask < (1<<N); mask++) {
			if(mask & 1)                         continue; // Contains start
			if(mask & (1<<midpoint))             continue; // Contains midpoint
			if(__builtin_popcount(mask) != half) continue; // Number of nodes not correct

			// For this set of half of the points, store all possible lengths
			set<long long> found;
			
			for(int k = 0; k < 2; k++) {
				// Find all current nodes (those in mask for k = 0,
				// or those not in mask for k = 1)
				vector<int> curroute;
				curroute.push_back(0);
				for(int i = 1; i < N; i++) {
					if(i == midpoint) continue;
					if((k == 0) == ((mask & (1<<i)) > 0))
						curroute.push_back(i);
				}
				curroute.push_back(midpoint);
				
				// Loop over all permutations
				do {
					// Find the length
					long long len = 0;
					for(int i = 0; len < L && i < (int)curroute.size() - 1; i++)
						len += dst[curroute[i]][curroute[i+1]];
					if(len > L) continue; // Can never lead to a correct route
					

					if(k == 0) {
						// Insert into list of found lengths
						found.insert(len);
					}
					else {
						// Check if we can match this with an opposite route
						if(found.find(L - len) != found.end())
							possible = true;
					}
					
				} while(next_permutation(curroute.begin() + 1, curroute.end() - 1));
			}
		}
	}

	cout << (possible ? "possible" : "impossible") << endl;
	
	return 0;
}
