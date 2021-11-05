#include <cstdio>
#include <cstdlib>
#include <vector>

using namespace std;
typedef vector<int> vi;
vi adj[1<<15];
int col[1<<15][2];
int n;

int nc() { return random() % (n*2); }

void assign(int a, int par) {
	col[a][0] = par == -1 ? nc() : col[par][1];
	//	col[a][1] = nc();
	col[a][1] = adj[a].size() > 1 ? nc() : col[par][0];
	for (auto b: adj[a])
		if (b != par) assign(b, a);
}

int main(void) {
	scanf("%d", &n);
	for (int i = 0; i < n-1; ++i) {
		int a, b;
		scanf("%d%d", &a, &b);
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	for (int i = 1; i < n; ++i)
		if (adj[i].size() == 1) {
			assign(i, -1);
			break;
		}
	for (int i = 1; i <= n; ++i)
		printf("%d %d\n", col[i][0], col[i][1]);
	return 0;
}
