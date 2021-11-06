#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define FOR(i,a,b) for(ll i = (a); i < (b); i++)
#define FORD(i,a,b) for(ll i = ll(b) - 1; i >= (a); i--)

int main() {
	ios_base::sync_with_stdio(false);
  
  ll n, m;
  string hint, cipher;
  cin >> n >> m >> hint >> cipher;
  string plain(m, ' ');
  FOR(i, 0, n) {
    plain[m - n + i] = hint[i];
  }
  FORD(i,0, m - n) {
    ll b = (cipher[i + n] - 'a');
    ll a = (plain[i + n] - 'a');
    ll k = (b - a + 26) % 26;
    plain[i] = (char)(k + 'a');
  }
  cout << plain << endl;
	return 0;
}
