
#include <string>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <string.h>
#include <utility>
#include <queue>
#include <stack>
#include <iomanip>
#include <ctype.h>
#include <map>
#include <set>
#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <sstream>
#include <math.h>
#include <time.h>
#include <iostream>
#include <iomanip>
#include <unordered_set>
#include <unordered_map>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

using namespace std;

typedef long long LL;
typedef unsigned long long ULL;

#define FOR(i,n) for(int i = 0;i < n;i++)
#define MP make_pair
#define PB push_back
#define ALL(a) (a).begin(),(a).end()
#define PII pair<int, int>
#define PLL pair<long long, long long>
#define CLEAR(a) memset(a, 0, sizeof(a))
#define INF 2000000007
#define y1 uu1
#define y2 uu2
#define hash mash
const double EPS = 1E-12;
const double PI = acos(-1.0);
const LL mod = 1000000007;

using namespace std;

int n;
double x;
vector<double> l,r;

int main() {
    ios_base::sync_with_stdio(0);
    cin >> n;
    
    if (n < 1 || n > 100000) {
        cout << "FAIL1" << endl;
        return 0;
    }
    
    FOR(i, n) {
        cin >> x;
        
        if (i > 0 && x < l.back()) {
            cout << "FAIL2" << endl;
            return 0;
        }
        
        if (x < 1 || x > 1000000) {
            cout << "FAIL3" << endl;
            return 0;
        }
        
        l.push_back(x);
        
        cin >> x;
        
        if (x < 1 || x > 1000000) {
            cout << "FAIL4" << endl;
            return 0;
        }
        
        if (i > 0 && x < r.back()) {
            cout << "FAIL5" << endl;
            return 0;
        }
        
        r.push_back(x);
        
        if (l.back() > r.back())
        {
            cout << "FAIL6" << endl;
            return 0;
        }
        
    }
    return 42;
}
