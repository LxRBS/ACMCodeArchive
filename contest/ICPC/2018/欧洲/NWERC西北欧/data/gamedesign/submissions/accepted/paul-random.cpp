#include <bits/stdc++.h>
using namespace std;

// Tries to find a solution by creating a random grid filled
// with around 5% of walls and simulating the given sequence
// from an arbitrary starting point, then checking whether
// this gives a valid solution.

#ifndef WALL_PROB
#define WALL_PROB 0.05
#endif

#ifndef MAX_ATTEMPTS
#define MAX_ATTEMPTS 500
#endif

#ifndef RAND_SEED
#define RAND_SEED 42
#endif

const int N = 300;
bool wall[N][N];

int main() {
	string moves; cin >> moves;
	
	srand(RAND_SEED);
	int attempts = MAX_ATTEMPTS;
	
	while (attempts--) {
		int count = 0;
		for (int x = 0; x < N; x++) {
			for (int y = 0; y < N; y++) {
				wall[x][y] = min(x,y) == 0 || max(x,y) == N-1 || double(rand())/RAND_MAX < (double)(WALL_PROB);
				count += wall[x][y];
			}
		}
		
		int sx = 0, sy = 0;
		while (wall[sx][sy]) sx = rand() % N, sy = rand() % N;
		
		bool ok = true;

		int x = sx, y = sy;
		for (char c: moves) {
			int dx = (c == 'R') - (c == 'L');
			int dy = (c == 'U') - (c == 'D');
			
			// we are already at a wall, so we cannot move
			if (wall[x+dx][y+dy]) ok = false;

			while (!wall[x+dx][y+dy]) x += dx, y += dy;
		}
		
		int tx = x, ty = y;
		
		// do a second pass to check if we already passed over the hole 
		
		x = sx, y = sy;
		for (char c: moves) {
			int dx = (c == 'R') - (c == 'L');
			int dy = (c == 'U') - (c == 'D');
			
			while (!wall[x+dx][y+dy]) {
				if (x == tx && y == ty) ok = false;
				x += dx, y += dy;
			}
		}
		
		if (ok) {
			cerr << "Found solution with " << attempts << " attempts left." << endl;
			cerr << "Attempts: " << MAX_ATTEMPTS - attempts << endl;
			cout << sx-tx << " " << sy-ty << endl;
			cout << count << endl;
			for (int x = 0; x < N; x++) {
				for (int y = 0; y < N; y++) {
					if (wall[x][y]) cout << x-tx << " " << y-ty << endl;
				}
			}
			return 0;
		}
	}
	cout << "impossible" << endl;
}
