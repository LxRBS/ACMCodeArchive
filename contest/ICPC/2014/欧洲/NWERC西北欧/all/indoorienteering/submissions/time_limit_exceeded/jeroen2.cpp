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
		set<pair<long long,int> > found;
			
		int half1 = (N - 2) / 2;
		int half2 = (N - 1) / 2;
		for(int mask = 0; mask < (1<<N); mask++) {
			if(mask & 1)                         continue; // Contains start
			if(mask & (1<<midpoint))             continue; // Contains midpoint
			if(__builtin_popcount(mask) != half1
				&& __builtin_popcount(mask) != half2) continue; // Number of nodes not correct

			vector<int> curroute;
			curroute.push_back(0);
			for(int i = 1; i < N; i++) {
				if(i == midpoint) continue;
				if((mask & (1<<i)) > 0)
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
					

				if(__builtin_popcount(mask) == half1) {
					// Insert into list of found lengths
					found.insert(pair<long long,int>(len, mask));
				}
				if(__builtin_popcount(mask) == half2) {
					// Check if we can match this with an opposite route
					int rest = ((1<<N)-1) ^ mask ^ 1 ^ (1<<midpoint);
					if(found.find(pair<long long,int>(L - len,rest)) != found.end())
						possible = true;
				}
					
			} while(next_permutation(curroute.begin() + 1, curroute.end() - 1));
		}
	}

	cout << (possible ? "possible" : "impossible") << endl;
	
	return 0;
}
