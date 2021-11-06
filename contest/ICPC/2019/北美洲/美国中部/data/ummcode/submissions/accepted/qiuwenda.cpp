#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 5;
char s[N];
bool isword[128];
int main() {
	fgets(s, sizeof(s), stdin);
	int n = (int) strlen(s);
	string um, tmp;
	for (char i = 'a'; i <= 'z'; ++ i) isword[i] = 1;
	for (char i = 'A'; i <= 'Z'; ++ i) isword[i] = 1;
	for (char i = '0'; i <= '9'; ++ i) isword[i] = 1;
	bool gg = 0;
	for (int i = 0; i < n; ++ i) {
		if (isword[s[i]]) {
			tmp += s[i];
			if (s[i] != 'u' && s[i] != 'm') {
				gg = 1;
			}
		}
		else if (s[i] == ' ') {
			if (!gg) um += tmp;
			tmp = "";
			gg = 0;
		}
	}
	if (!gg) um += tmp;
	assert(um.length() % 7 == 0);
	for (int i = 0; i < (int) um.length(); i += 7) {
		int c = 0;
		for (int j = 0; j < 7; ++ j) c = c * 2 + (um[i + j] == 'u' ? 1 : 0);
		putchar((char) c);
	}
	puts("");
}

