// [NWERC'14] Orienteering, by Jan Kuipers

#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

int N;
long long L;
vector<vector<long long> > d;

int bit_count(int msk) {
  int cnt=0;
  while (msk > 0) {
    if (msk & 1) cnt++;
    msk >>= 1;
  }
  return cnt;
}

set<long long> get_distances(int start, int mask, int end) {
  vector<int> x;
  set<long long> distances;
  if (mask == 0) {
    distances.insert(d[start][end]);
    return distances;
  }
  for (int i=0; i<N; i++) {
    if (mask & (1<<i)) x.push_back(i);
  }
  do {
    long long dist = d[start][x[0]];
    for (int i=0; i+1<x.size(); i++) {
      dist += d[x[i]][x[i+1]];
    }
    dist += d[x.back()][end];
    distances.insert(dist);
  } while (next_permutation(x.begin(), x.end()));
  return distances;
}

int main() {
  cin >> N >> L;
  d = vector<vector<long long> >(N, vector<long long>(N));
  for (int i=0; i<N; i++) {
    for (int j=0; j<N; j++) {
      cin >> d[i][j];
    }
  }
  bool possible = false;
  for (int center=1; center<N; center++) {
    for (int mask_left=0; mask_left<(1<<N); mask_left++) {
      if (mask_left & (1<<0)) continue;
      if (mask_left & (1<<center)) continue;
      if (bit_count(mask_left) != (N-2)/2)  continue;
      int mask_right = (1<<N) - 1 - mask_left - (1<<0) - (1<<center);
      set<long long> distances_left = get_distances(0, mask_left, center);
      set<long long> distances_right = get_distances(center, mask_right, 0);
      for (set<long long>::iterator it = distances_left.begin(); it != distances_left.end(); it++) {
	if (distances_right.find(L - *it) != distances_right.end()) {
	  possible = true;
	}
      }
    }
  }
  cout << (possible ? "possible" : "impossible") << endl;    
  return 0;
}
