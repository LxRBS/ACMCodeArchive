#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#define MAXN 1000005

using namespace std;

void process2(pair<int, pair<int, int> > a[MAXN], int &ac, char s[MAXN], int sc, int &pos) {
	if (s[pos] == '[') {
		while (s[pos] != ']') {
			pos++;
			int num = 0;
			while ((s[pos] != ',') && (s[pos] != ']')) {
				num = num * 10 + (int)(s[pos] - '0');
				pos++;
			}
			a[ac].first = num;
			a[ac].second.first = -1;
			a[ac].second.second = -1;
			ac++;
		}
		pos++;
	} else if (s[pos] == 'c') {
		pos += 7;
		process2(a, ac, s, sc, pos);
		pos++;
		process2(a, ac, s, sc, pos);
		pos++;
	} else if (s[pos+1] == 'o') {
		pos += 7;
		process2(a, ac, s, sc, pos);
		pos++;
	} else {
		pos += 8;
		process2(a, ac, s, sc, pos);
		pos++;
	}
}

void process(pair<int, pair<int, int> > a[MAXN], int &ac, char s[MAXN], int sc, int &pos) {
	if (s[pos] == '[') {
		while (s[pos] != ']') {
			pos++;
			int num = 0;
			while ((s[pos] != ',') && (s[pos] != ']')) {
				num = num * 10 + (int)(s[pos] - '0');
				pos++;
			}
			a[ac].first = num;
			a[ac].second.first = -1;
			a[ac].second.second = -1;
			ac++;
		}
		pos++;
	} else if (s[pos] == 'c') {
		pos += 7;
		process(a, ac, s, sc, pos);
		pos++;
		process(a, ac, s, sc, pos);
		pos++;
	} else if (s[pos+1] == 'o') {
		pos += 7;
		int cur = ac;
		process2(a, ac, s, sc, pos);
		sort(a+cur, a+ac);
		pos++;
	} else {
		pos += 8;
		int cur = ac;
		process2(a, ac, s, sc, pos);
		sort(a+cur, a+ac);
		if (a[cur] != a[ac-1]) {
			for (int i = cur; i < ac; i++) {
				a[i].second.first = cur;
				a[i].second.second = ac;
			}
		}
		pos++;
	}
}

int main() {
	static pair<int, pair<int, int> > a[MAXN];
	int ac = 0;
	static char sa[MAXN];
	int sac;
	static pair<int, pair<int, int> > b[MAXN];
	int bc = 0;
	static char sb[MAXN];
	int sbc;

	scanf("%s",sa);
	sac = strlen(sa);
	scanf("\n%s",sb);
	sbc = strlen(sb);

	int posa = 0;
	process(a, ac, sa, sac, posa);
	int posb = 0;
	process(b, bc, sb, sbc, posb);

	if (ac != bc) {
		printf("not equal\n");
		return 0;
	}

	for (int i = 0; i < ac; i++) {
		if ((a[i].first != b[i].first) || (a[i].second.first != b[i].second.first) || (a[i].second.second != b[i].second.second)) {
			printf("not equal\n");
			return 0;
		}
	}

	printf("equal\n");
	return 0;
}
