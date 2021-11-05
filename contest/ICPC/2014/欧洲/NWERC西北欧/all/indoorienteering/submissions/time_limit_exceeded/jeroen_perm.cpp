#include <iostream>
#include <vector>
#include <algorithm>

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

	vector<int> nodes;
	for(int i = 0; i < N; i++)
		nodes.push_back(i);

	do {
		long long dist = 0;
		for(int i = 0; dist <= L && i < N; i++)
			dist += dst[nodes[i]][nodes[(i+1)%N]];
		if(dist == L) {
			cout << "possible" << endl;
			return 0;
		}
	} while(next_permutation(nodes.begin()+1,nodes.end()));
	
	cout << "impossible" << endl;
	return 0;
}
