#include <iostream>
#include <set>

using namespace std;

#define MAXN 14

long long dst[MAXN][MAXN];

int main() {
	int N;
	long long L;
	cin >> N >> L;
	for(int i = 0; i < N; i++)
		for(int j = 0; j < N; j++)
			cin >> dst[i][j];

	long long target = (L<<14) + (1<<N) - 1;
	set<long long> cur;
	cur.insert(0);
	for(int i = 0; i < N; i++) {
		set<long long> next;
		for(set<long long>::iterator it = cur.begin(); it != cur.end(); it++) {
			for(int j = 0; j < N; j++) {
				if(i == j) continue;
				if(*it > target) continue;
				if((*it) & (1<<j)) continue;
				next.insert(*it + (dst[i][j]<<14) + (1<<j));
			}
		}
		cur = next;
	}

	cout << (cur.find(target) != cur.end() ? "possible" : "impossible") << endl;
	
	return 0;
}
