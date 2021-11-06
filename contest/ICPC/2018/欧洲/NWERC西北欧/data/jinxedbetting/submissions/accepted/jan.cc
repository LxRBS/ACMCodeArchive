// [NWERC'18] Betting, by Jan Kuipers

#include <algorithm>
#include <climits>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  int n;
  cin >> n;
  long long x;
  cin >> x;
  vector<long long> y(n-1);
  for (int i=0; i<n-1; i++) {
    cin >> y[i];
  }
  sort(y.begin(), y.end());
  long long res=0;
  int cnt=1;
  while (y.back()!=x || cnt==1) {
    while(y.size()>1 && y.back()==y[y.size()-2]) {
      y.pop_back();
      cnt++;
    }

    //2^n -> n steps in n+1 time
    int pow2 = (int) (log(cnt) / log(2.0) + 1e-9);
    long long s1 = (cnt==1 ? LONG_LONG_MAX
		    : (x-y.back())/pow2*(pow2+1) + (x-y.back())%pow2);
    if (y.size() == 1) {
      res += s1;
      break;
    } else {      
      long long s2 = (y.back()-y[y.size()-2])*(pow2+1);
      if (s1 < s2) {
	res += s1;
	break;
      } else {
	res += s2;
	x -= s2;
	y.back() = y[y.size()-2];
      }
    }    
  }
  cout << res << endl;  
  return 0;
}
