#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <set>
#include <vector>
#define MAXN 105
#define LIM 1000000000

using namespace std;

int main() {
	static char s[MAXN];
	int N;
	scanf("%s",s);
	N = strlen(s);

	static pair<int, int> a[MAXN];
	int ac = 0;

	int x1 = -LIM;
	int y1 = -LIM;
	int x2 = LIM;
	int y2 = LIM;

	int x = 0; int y = 0;
	int i = N-1;

	while (i >= 0) {
		if (s[i] == 'D') {
			a[ac] = make_pair(x, y-1);
			ac++;
			y1 = y + 1;
			y = (y1 + y2) / 2;
			int j = i-1;
			if ((j >= 0) && (s[j] == 'U')) {
				a[ac] = make_pair(x, y+1);
				ac++;
				y2 = y - 1;
				y = (y1 + y2) / 2;
				j--;
				if ((j >= 0) && (s[j] == 'D') && (i == (N-1))) {
					printf("impossible\n");
					return 0;
				}
				while ((j >= 0) && ((s[j] == 'D') || (s[j] == 'U'))) {
					j--;
				}
			}
			i = j;
		} else if (s[i] == 'U') {
			a[ac] = make_pair(x, y+1);
			ac++;
			y2 = y - 1;
			y = (y1 + y2) / 2;
			int j = i-1;
			if ((j >= 0) && (s[j] == 'D')) {
				a[ac] = make_pair(x, y-1);
				ac++;
				y1 = y + 1;
				y = (y1 + y2) / 2;
				j--;
				if ((j >= 0) && (s[j] == 'U') && (i == (N-1))) {
					printf("impossible\n");
					return 0;
				}
				while ((j >= 0) && ((s[j] == 'D') || (s[j] == 'U'))) {
					j--;
				}
			}
			i = j;
		} else if (s[i] == 'L') {
			a[ac] = make_pair(x-1, y);
			ac++;
			x1 = x + 1;
			x = (x1 + x2) / 2;
			int j = i-1;
			if ((j >= 0) && (s[j] == 'R')) {
				a[ac] = make_pair(x+1, y);
				ac++;
				x2 = x - 1;
				x = (x1 + x2) / 2;
				j--;
				if ((j >= 0) && (s[j] == 'L') && (i == (N-1))) {
					printf("impossible\n");
					return 0;
				}
				while ((j >= 0) && ((s[j] == 'L') || (s[j] == 'R'))) {
					j--;
				}
			}
			i = j;
		} else if (s[i] == 'R') {
			a[ac] = make_pair(x+1, y);
			ac++;
			x2 = x - 1;
			x = (x1 + x2) / 2;
			int j = i-1;
			if ((j >= 0) && (s[j] == 'L')) {
				a[ac] = make_pair(x-1, y);
				ac++;
				x1 = x + 1;
				x = (x1 + x2) / 2;
				j--;
				if ((j >= 0) && (s[j] == 'R') && (i == (N-1))) {
					printf("impossible\n");
					return 0;
				}
				while ((j >= 0) && ((s[j] == 'L') || (s[j] == 'R'))) {
					j--;
				}
			}
			i = j;
		}
	}

	printf("%d %d\n",x,y);
	printf("%d\n",ac);
	for (int z = 0; z < ac; z++) {
		printf("%d %d\n",a[z].first,a[z].second);
	}

	return 0;
}
