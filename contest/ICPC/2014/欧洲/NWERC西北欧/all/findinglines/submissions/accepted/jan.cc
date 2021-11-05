// [NWERC'14] Find line, by Jan Kuipers

#include <iostream>
#include <vector>

using namespace std;

int main() {
  int N, P;
  cin >> N >> P;
  vector<long long> x(N),y(N);
  for (int i=0; i<N; i++) {
    cin >> x[i] >> y[i];
  }
  bool possible = false;
  if (N == 1) {
    possible = true;
  } else {
    srandom(170681);
    for (int times = 0; times < 1000; times++) {
      int i1 = random() % N;
      int i2 = (i1 + 1 + random() % (N-1)) % N;
      int cnt = 0;
      for (int i=0; i<N; i++) {
	if ((x[i2]-x[i1])*(y[i]-y[i1]) == (x[i]-x[i1])*(y[i2]-y[i1])) {
	  cnt++;
	}
      }
      if (cnt * 100 >= P * N) {
	possible = true;
	break;
      }
    }    
  }
  cout << (possible ? "possible" : "impossible") << endl;
  return 0;  
}
