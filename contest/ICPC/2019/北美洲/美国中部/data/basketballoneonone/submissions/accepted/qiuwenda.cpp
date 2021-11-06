#include <bits/stdc++.h>
using namespace std;
char s[205];
int a[2];
int main() {
	scanf("%s", s);
	int l = strlen(s), winner = -1, id = 0;
	for (int i = 0; i < l; ++ i) {
		if (s[i] == 'A') {
			id = 0;
		}
		else if (s[i] == 'B') {
			id = 1;
		}
		else {
			a[id] += s[i] - '0';
			if (a[id] >= 11 && a[id] - a[id ^ 1] > 1) {
				assert(i == l - 1);
				winner = id;
			}
		}
	}
	assert(winner != -1);
	puts(winner == 0 ? "A" : "B");
}

