/**
 * 判断给定的字符串是否存在`a`、`b`相邻的情况
 */
#include <bits/stdc++.h>
using namespace std;

using llt = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;

int N;
string S;

bool proc(){
    for(int i=1;i<N;++i){
        if('a' == S[i - 1] and 'b' == S[i]) return true;
        if('b' == S[i - 1] and 'a' == S[i]) return true;
    }
    return false;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> S;
    cout << (proc() ? "Yes" : "No") << endl;
    return 0;
}