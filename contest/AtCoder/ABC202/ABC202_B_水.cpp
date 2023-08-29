#include <bits/stdc++.h>
using namespace std;

#include <bits/extc++.h>
using namespace __gnu_pbds;

using Real = long double;
using llt = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;

#ifndef ONLINE_JUDGE
int const SZ = 34;
#else
int const SZ = 2E5+10;
#endif


int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    char m[256];
    for(int i='0';i<='9';++i) m[i] = i;
    m['6'] = '9'; m['9'] = '6';
    string s; cin >> s;
    string t;
    for(char ch : s)  t += m[ch];
    reverse(t.begin(), t.end());
    cout << t << endl;
    return 0;
}