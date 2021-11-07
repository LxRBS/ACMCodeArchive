#include <bits/stdc++.h>

using namespace std;

const int N = 5000;

int fail_list[N + 10], vis[N + 10];
vector<int>factor[N + 10];

// wrong pairs: (19, 33) ok, but (27, 34) failed

int main() {
	memset(fail_list, -1, sizeof(fail_list));
	for (int i = 1; i <= N; i++)
		for (int j = i; j <= N; j += i) 
			factor[j].push_back(i);
	fail_list[0] = 0;
	for(int i = 1; i <= N; i++) {
		if(fail_list[i] != -1)continue;
		memset(vis, 0, sizeof(vis));
		for(int j = 0; j < i; j++) {
			if(fail_list[j] == -1)continue;
			for(int k = fail_list[j]; k <= N; k += i - j) {
				vis[k] = 1;
			}
			// jsb add
			for (int k = 0; k < factor[i-j].size() && fail_list[j] + factor[i-j][k] <= N; k++)
				vis[fail_list[j] + factor[i-j][k]] = 1;
		}
		
		for(int k = i + 1; k <= N; k++)
			if(!vis[k]) {
				fail_list[i] = k;
				fail_list[k] = i;
				break;
			}
	}
	int T;
	scanf("%d", &T);
	while(T--) {
		int n, m;
		scanf("%d%d", &n, &m);
		if(fail_list[n] == m)puts("Bob");
		else puts("Alice");
	}
}