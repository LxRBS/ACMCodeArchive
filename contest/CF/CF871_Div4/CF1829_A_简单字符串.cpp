#include <bits/stdc++.h>
using namespace std;

#include <bits/extc++.h>
using namespace __gnu_pbds;

using llt = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;

#ifndef ONLINE_JUDGE
int const SZ = 34;
#else
int const SZ = 200000 + 12;
#endif

string S;
int proc(){
    static const string a = "codeforces";
    int c = 0;
    for(int i=0;i<10;++i){
        if(S[i] != a[i]) ++c;
    }
    return c;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    
    int nofkase; cin >> nofkase;
    while(nofkase--){
        cin >> S;
        cout << proc() << endl;
    }
    return 0;
}

