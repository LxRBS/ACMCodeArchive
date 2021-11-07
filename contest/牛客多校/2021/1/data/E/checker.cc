#include "testlib.h"
#include<bits/stdc++.h>

using namespace std;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};
const int changedir[4][6] = {{-1, -1, 1, 3, -1, 0}, {0, -1, -1, 2, 1, -1}, 
                         {3, 1, -1, -1, -1, 2}, {-1, 0, 2, -1, 3, -1}};

int a[1005][1005];

void skip_ans(int n, int m){
	int steps = ans.readInt(0, 20 * n * m);
	while (steps--){
		int opt = ans.readInt(0, 20 * n * m);
  		if (opt == 0){
  			ans.readInt(1, n), ans.readInt(1, m);
  		}
  		else{
  			int degree = ans.readInt(0, 270);
  			while (opt--)
  				ans.readInt(1, n), ans.readInt(1, m);
  		}
	}
}

int main(int argc, char** argv) {
	registerTestlibCmd(argc, argv);
	int T = inf.readInt();
	for (int cas = 1; cas <= T; ++cas) {
		int n = inf.readInt(2, 1000);
		int m = inf.readInt(2, 1000);
		
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
				a[i][j] = inf.readInt(0, 5);
		
		string token_out = ouf.readToken(), token_ans = ans.readToken();
		if (token_out != token_ans)
			quitf(_wa, "Case #%d: Judge error for whether you can reach the destination.", cas);
		
		if (token_ans == "NO") continue;
		
		skip_ans(n, m);
		
		int steps = ouf.readInt(0, 20 * n * m), total_steps = 0;
		
		int lastx = 0, lasty = 1, lastd = 2;
		bool rotate = false;
    	while (steps--){
      		int opt = ouf.readInt(0, 20 * n * m);
      		if (opt == 0){
      			rotate = false;
      			total_steps += 1;
      			int x = ouf.readInt(1, n), y = ouf.readInt(1, m);
      			if (lastx + dx[lastd] != x || lasty + dy[lastd] != y)
					quitf(_wa, "Case #%d: You can not go from (%d, %d) to (%d, %d)\n", cas, lastx, lasty, x, y);
      			int d = changedir[lastd][a[x][y]];
      			if (d == -1)
					quitf(_wa, "Case #%d: You are not walk along the pipe after stepping in (%d, %d)", cas, x, y);
      			lastx = x; lasty = y; lastd = d;
      		}
      		else{
      			if (rotate)
					quitf(_wa, "Case #%d: You have consecutive rotation requests.", cas);
      			rotate = true;
      			int degree = ouf.readInt(0, 270);
      			if (degree != 0 && degree != 90 && degree != 180 && degree != 270)
					quitf(_wa, "Case #%d: The degree must in {0, 90, 180, 270}.", cas);
      			total_steps += opt;
      			while (opt--){
      				int x = ouf.readInt(1, n), y = ouf.readInt(1, m);
      				if (a[x][y] >= 4) a[x][y] = a[x][y] ^ (degree == 90 || degree == 270);
      				else a[x][y] = (a[x][y] + degree / 90) % 4;
      			}
      		}
      		if (total_steps > 20 * n * m)
				quitf(_wa, "Case #%d: Total number of cells exceeds 20nm.", cas);
      	}
      	if (lastx != n || lasty != m)
			quitf(_wa, "Case #%d: Your endpoint is not (%d, %d)", cas, n, m);
      	if (lastd != 2)
			quitf(_wa, "Case #%d: The final direction is wrong!", cas);
    }
	quitf(_ok, "Your route is correct!");
	return 0;
}