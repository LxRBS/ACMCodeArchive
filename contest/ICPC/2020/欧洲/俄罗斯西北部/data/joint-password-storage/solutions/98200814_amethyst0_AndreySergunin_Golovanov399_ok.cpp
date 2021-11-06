#pragma GCC optimize("Ofast", "unroll-loops", "no-stack-protector")
 
#include <bits/stdc++.h>
 
using namespace std;

#define all(a) (a).begin(), (a).end()
#define sz(a) (int)(a).size()

using ll = long long;
using ld = long double; 
// using ld = __float128;
using pii = pair<int, int>;
using uint = unsigned int;
using ull = unsigned long long;

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
default_random_engine generator;

void solve();

int main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);  
#endif 

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cout << setprecision(6) << fixed;
    cerr << setprecision(6) << fixed;

    int tests = 1;
    cin >> tests;

    for (int test = 1; test <= tests; ++test) {
        // cout << "Case #" << test << ": ";
        solve();
    }

#ifdef LOCAL
    cerr << "Time: " << double(clock()) / CLOCKS_PER_SEC << endl;
#endif
}

// ----------------------------------------------------------------- 

vector<string> ans;

void add(vector<int> &arr, string t) {
    ans.push_back(t);
    assert(sz(arr) == sz(t));
    // cout << t << endl;
    for (int i = 0; i < sz(t); ++i) {
        arr[i] ^= int(t[i]);
    }
}

string f(int n, int k, string c, string d) {
    bool rev = false;
    if (2 * k >= n - 2) {
        k = n - 3 - k;
        rev = true;
    }

    string res;

    if (k == 0) {
        res = c + "0" + d + "*" + string(n - 6, '1') + "=0";
    } else if (k == 1) {
        assert(false);
    } else {
        res = string(k - 1, '1') + "*" + c + "0" + d + "*" + string(n - k - 6, '1') + "=0";
    }

    assert(sz(res) == n);
    if (rev) {
        reverse(all(res));

        for (int i = 0; i < n; ++i) {
            if (res[i] == c[0]) {
                res[i] = d[0];
            } else if (res[i] == d[0]) {
                res[i] = c[0];
            }
        }
    }
    return res;
}

bool resolve_6(vector<int> &arr) {
    int n = sz(arr);
    vector<int> cnt(2);
    for (int i = 0; i < n; ++i) {
        if (arr[i] >= 64) {
            cnt[i & 1] ^= 1;
        }
    }

    if (cnt[0] != cnt[1]) {
        return false;
    }

    if (cnt[0] == 1) {
        add(arr, "{10}*0*" + string(n - 9, '1') + "=0");
    }

    for (int i = 0; i + 2 < n; ++i) {
        if (arr[i] < 64) {
            continue;
        }
        if (i != 1 && i != n - 4) {
            add(arr, f(n, i, "{", "}"));
        } else if (i == 1) {
            add(arr, "{{0}}*" + string(n - 8, '1') + "=0");
            add(arr, f(n, 0, "{", "}"));
            add(arr, f(n, 2, "{", "}"));
        } else if (i == n - 4) {
            add(arr, "0=" + string(n - 8, '1') + "*{{0}}");
            add(arr, f(n, n - 3, "{", "}"));
            add(arr, f(n, n - 5, "{", "}"));
        }
    }    
    return true;
}

bool resolve_5(vector<int> &arr, int bit) {
    int n = sz(arr);
    vector<int> cnt(2);
    for (int i = 0; i < n; ++i) {
        if (((arr[i] >> 5) & 1) ^ bit) {
            cnt[i & 1] ^= 1;
        }
    }

    if (cnt[0] != cnt[1]) {
        return false;
    }

    if (cnt[0] == 1) {
        add(arr, "{10}*0*" + string(n - 9, '1') + "=0");
        add(arr, "[10]*0*" + string(n - 9, '1') + "=0");
    }

    for (int i = 0; i + 2 < n; ++i) {
        if ((arr[i] >> 5) ^ !bit) {
            continue;
        }
        if (i != 1 && i != n - 4) {
            add(arr, f(n, i, "{", "}"));
            add(arr, f(n, i, "[", "]"));
        } else if (i == 1) {
            add(arr, "{{0}}*" + string(n - 8, '1') + "=0");
            add(arr, "[[0]]*" + string(n - 8, '1') + "=0");
            add(arr, f(n, 0, "{", "}"));
            add(arr, f(n, 0, "[", "]"));
            add(arr, f(n, 2, "{", "}"));
            add(arr, f(n, 2, "[", "]"));
        } else if (i == n - 4) {
            add(arr, "0=" + string(n - 8, '1') + "*{{0}}");
            add(arr, "0=" + string(n - 8, '1') + "*[[0]]");
            add(arr, f(n, n - 3, "{", "}"));
            add(arr, f(n, n - 3, "[", "]"));
            add(arr, f(n, n - 5, "{", "}"));
            add(arr, f(n, n - 5, "[", "]"));
        }
    }    

    // for (int i = 0; i < n; ++i) {
    //     cout << arr[i] << " ";
    // }
    // cout << endl;


    return true;
} 


 
void add_to_ans(const string& s, vector<int>& a) {
    ans.push_back(s);
    assert(sz(a) == sz(s));

    for (int i = 0; i < (int)a.size(); ++i) {
        a[i] ^= s[i];
    }
}
 
void replace_begin(string& s, const string& t) {
    for (int i = 0; i < (int)t.size(); ++i) {
        s[i] = t[i];
    }
}
 
void replace_end(string& s, const string& t) {
    for (int i = 0; i < (int)t.size(); ++i) {
        s[(int)s.length() - 1 - i] = t[(int)t.length() - 1 - i];
    }
}
 
bool resolve_4(vector<int>& a) {
    const int n = a.size();
    if (a[0] & 16) {
        string s(n, '1');
        replace_end(s, "*0=0");
        add_to_ans(s, a);
        s[0] = '(';
        s[n - 5] = ')';
        add_to_ans(s, a);
    }
    if (a[n - 1] & 16) {
        string s(n, '1');
        replace_begin(s, "0=0*");
        add_to_ans(s, a);
        s[4] = '(';
        s[n - 1] = ')';
        add_to_ans(s, a);
    }
    if (a[1] & 16) {
        string s(n, '1');
        replace_begin(s, "((0))*");
        replace_end(s, "=0");
        add_to_ans(s, a);
        replace_begin(s, "(0*0)*");
        add_to_ans(s, a);
    }
    if (a[n - 2] & 16) {
        string s(n, '1');
        replace_end(s, "*((0))");
        replace_begin(s, "0=");
        add_to_ans(s, a);
        replace_end(s, "*(0*0)");
        add_to_ans(s, a);
    }
    for (int i = 2; i < n - 2; ++i) {
        if (!(a[i] & 16)) {
            continue;
        }
        if (i < n - 6) {
            string s(n, '1');
            s[0] = '(';
            replace_end(s, ")*0=0");
            add_to_ans(s, a);
            s[i] = '+';
            add_to_ans(s, a);
        } else if (i > 6) {
            string s(n, '1');
            s[n - 1] = ')';
            replace_begin(s, "0=0*(");
            add_to_ans(s, a);
            s[i] = '+';
            add_to_ans(s, a);
        } else if (i < n - 5) {
            string s(n, '1');
            replace_begin(s, "0*");
            replace_end(s, "*0=0");
            add_to_ans(s, a);
            s[i] = '+';
            add_to_ans(s, a);
        } else {
            string s(n, '1');
            replace_begin(s, "0=0*");
            replace_end(s, "*0");
            add_to_ans(s, a);
            s[i] = '+';
            add_to_ans(s, a);
        }
    }
    assert(*max_element(all(a)) < 16);
    return true;
}
 
bool resolve_0123(vector<int>& a) {
    const int n = a.size();
    for (int i = 0; i < (int)a.size(); ++i) {
        assert(!(a[i] & ~15));
        for (int j = 0; j <= 3; ++j) {
            if (!(a[i] & (1 << j))) {
                continue;
            }
            if (i >= 3 && i + 2 < n) {
                string s(n, '1');
                replace_begin(s, "0*");
                replace_end(s, "=0");
                add_to_ans(s, a);
                s[i] ^= (1 << j);
                add_to_ans(s, a);
            } else if (i <= 2) {
                string s(n, '1');
                replace_end(s, "*0=0");
                add_to_ans(s, a);
                s[i] ^= (1 << j);
                if (j == 0) {
                    s[i] ^= 2;
                }
                add_to_ans(s, a);
            } else {
                string s(n, '1');
                replace_begin(s, "0=0*");
                add_to_ans(s, a);
                s[i] ^= (1 << j);
                add_to_ans(s, a);
            }
        }
    }
    assert(*max_element(all(a)) == 0);
    return true;
}

void solve() {   
    ans.clear();
    string s;
    cin >> s;
    int n = sz(s);
    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        arr[i] = s[i];
    }

    if (!resolve_6(arr)) {
        cout << "NO" << endl;
        return;
    }

    for (int i = 0; i < n; ++i) {
        assert(arr[i] < 64);
    }

    if (!resolve_5(arr, 0)) {
        if (!resolve_5(arr, 1)) {
            cout << "NO" << endl;
            return;
        }

        assert(n & 1);
        add(arr, string(n / 2, '1') + "=" + string(n / 2, '1'));
    }

    for (int i = 0; i < n; ++i) {
        assert(arr[i] < 32);
    }

    resolve_4(arr);
    resolve_0123(arr);

    assert(sz(ans) <= 1000);

    cout << "YES" << endl;
    cout << sz(ans) << endl;
    for (string t : ans) {
        cout << t << endl;
    }
}
    