#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<bool> vb;
typedef vector<vb> vvb;

vi convert(ll n, ll b) {
    vi ans;
    while (n) {
        ans.push_back(n % b);
        n /= b;
    }
    vi result(ans.rbegin(), ans.rend());
    return result;
}

bool palindrome(vi n) {
    for (ll i = 0, j = n.size()-1; i < n.size(); ++i, --j) {
        if (n[i] != n[j]) return false;
    }
    return true;
}

int main() {
    ll a, b, k;
    cin >> a >> b >> k;

    ll count = 0;
    for (ll i = a; i <= b; ++i) {
        bool works = true;
        for (ll j = 2; j <= k && works; ++j) {
            works = works && palindrome(convert(i, j));
        }
        if (works) {
            ++count;
        }
    }

    cout << count << endl;
}
