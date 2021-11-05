// [NWERC'14] Not a single cent, by Jan Kuipers.

#include <iostream>
#include <vector>

using namespace std;

const int inf = 999999999;

int main() {
  int N,D;
  cin >> N >> D;
  D++;
  vector<int> x(N);
  vector<int> sum(N+1);
  for (int i=0; i<N; i++) {
    cin >> x[i];
    sum[i+1] = sum[i] + x[i];
  }
  vector<vector<int> > best(N+1, vector<int>(D+1, inf));
  best[0][0] = 0;
  for (int n=1; n<=N; n++) {
    for (int d=1; d<=D; d++) {
      for (int i=0; i<n; i++) {
	int pay = sum[n] - sum[i];
	int rem = pay % 10;
	pay -= rem;
	if (rem >= 5) {
	  pay += 10;
	}
	best[n][d] = min(best[n][d], best[i][d-1] + pay);
      }
    }
  }
  int res = inf;
  for (int d=1; d<=D; d++) {
    res = min(res, best[N][d]);
  }
  cout << res << endl;
  return 0;
}
