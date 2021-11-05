#include <bits/stdc++.h>
using namespace std;

int N;
char S[110];
char S2I[256];

void proc(){
	for(char const *p=S;*p;++p){
		putchar(S2I[*p]);
	}
	putchar('\n');
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    S2I['U'] = 'D';
	S2I['D'] = 'U';
	S2I['L'] = 'L';
	S2I['R'] = 'R';

    int nofkase;
	scanf("%d", &nofkase);
	while(nofkase--){
		scanf("%d%s", &N, S);
		proc();
	}
	return 0;
}