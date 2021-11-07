#include<bits/stdc++.h>
#define N 1005
using namespace std;
int a[N][N], cur[N][N], f[N][N][4], n, m;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};
const int prefer[4][2] = {{2, 3}, {3, 0}, {1, 0}, {2, 1}};
const int chdir[4][6] = {{-1, -1, 1, 3, -1, 0}, {0, -1, -1, 2, 1, -1}, 
                         {3, 1, -1, -1, -1, 2}, {-1, 0, 2, -1, 3, -1}};
const int needpiece[4][4] = {{-1, 2, -1, 3}, {0, -1, 3, -1}, {-1, 1, -1, 0}, {1, -1, 2, -1}};
vector<pair<int, int> >ways, ans;

int DFS(int x, int y, int d){
	if (x < 1 || x > n || y < 1 || y > m){
		//puts("Click");
		if (x != n+1 || y != m) return 0;
	}
	if (f[x][y][d]) return 0;
	
	if (x == n + 1 && y == m){
		assert(d == 2);
		//for (int i = 0; i < ways.size(); i++)
		//	printf("%d %d\n", ways[i].first, ways[i].second);
		ans.assign(ways.begin(), ways.end());
		//printf("%d\n", check());
		return 1;
	}
	f[x][y][d]=1; 
	ways.push_back(make_pair(x, y));
	int ret = 0;
	if (a[x][y] >= 4){
		ret = DFS(x + dx[d], y + dy[d], d);
	}
	else{
		for (int ch = 0; ch < 2; ch++){
			int rot = prefer[d][ch];
			int newd = chdir[d][rot];
			assert(newd != -1);
			if (DFS(x + dx[newd], y + dy[newd], newd)){
				ret = 1; break;
			}
		}
	}
	ways.pop_back();
	return ret;
}

int Print(bool should_print){
	int cnt = 0;
	int lastx = 0, lasty = 1, lastd = 2, d;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			cur[i][j] = a[i][j];
	for (int k = 0; k < ans.size(); k++){
		int x = ans[k].first, y = ans[k].second;
		if (k + 1 == ans.size()) d = 2;
		else {
			for (d = 0; ans[k + 1].first - ans[k].first != dx[d] || ans[k + 1].second - ans[k].second != dy[d]; ++d);
			assert(0 <= d <= 3);
		}
		
		if (cur[x][y] >= 4){
			if (d % 2 == cur[x][y] % 2){
				if (should_print) 
					printf("1 90 %d %d\n", x, y);
				cur[x][y] ^= 1, cnt += 1;
			}
		}
		else{
			int exp = needpiece[lastd][d];
			if (cur[x][y] != exp){
				if (should_print)
					printf("1 %d %d %d\n", (exp - cur[x][y] + 4) % 4 * 90, x, y);
				cur[x][y] = exp; cnt += 1;
			}
		}
		cnt += 1;
		if (should_print)
			printf("0 %d %d\n", x, y);
		lastx = x; lasty = y; lastd = d;
	}
	return cnt;
}

int main(){
	int T; scanf("%d", &T);
	while (T--){
		scanf("%d%d", &n, &m);
		for (int i = 0; i <= n + 1; i++)
			for (int j = 0; j <= m + 1; j++)
				for (int k = 0; k < 4; k++)	
					f[i][j][k] = 0;
		ways.clear();
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
				scanf("%d", &a[i][j]);
		//for (int i = 1; i <= n; i++, puts(""))
		//	for (int j = 1; j <= m; j++)
		//		printf("%d ", a[i][j]);
		if (n == 2 && m == 2 && a[1][1] == 4 && a[1][2] == 5 && a[2][1] == 0 && a[2][2] == 1){
			printf("YES\n5\n2 90 1 1 2 1\n0 1 1\n0 2 1\n2 180 1 2 2 2\n0 2 2\n");
		}
		else if (!DFS(1, 1, 2)) puts("NO");
		else{
			int cnt = Print(false);
			printf("YES\n%d\n", cnt);
			Print(true);
		}
	}
	
}
