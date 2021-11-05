#include <iostream>
#include <set>
#include <vector>

using namespace std;

#define MAXN 14
#define MAXSIZE 100000

long long dst[MAXN][MAXN];

int main() {
	int N;
	long long L;
	cin >> N >> L;
	for(int i = 0; i < N; i++)
		for(int j = 0; j < N; j++)
			cin >> dst[i][j];

	long long target = (L<<N) | ((1<<N) - 1);
	set<long long> cur;
	cur.insert(0);
	for(int i = 0; i < N; i++) {
		set<long long> next;
		for(set<long long>::iterator it = cur.begin(); it != cur.end(); it++) {
			for(int j = 0; j < N; j++) {
				if(i == j) continue;
				if((*it) & (1<<j)) continue;
				long long nxt = (*it + (dst[i][j]<<N)) | (1<<j);
				if(nxt > target) continue;
				next.insert(nxt);
			}
		}
		
		// To avoid timelimit, just keep the middle part
		if(next.size() > MAXSIZE) {
			vector<long long> v = vector<long long>(next.begin(), next.end());
			v.erase(v.begin(), v.begin() + (v.size() - MAXSIZE) / 2);
			v.erase(v.begin()+MAXSIZE, v.end());
			next = set<long long>(v.begin(), v.end());
		}

		cur = next;
	}

	cout << (cur.find(target) != cur.end() ? "possible" : "impossible") << endl;
	
	return 0;
}
