/**
 * 判断给定的B是否等于某个 a^a
 * 注意到这种形式的数不会太多，一一列举出来然后查找即可
 */
#include <bits/stdc++.h>
using namespace std;

using llt = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;

vector<llt> A;

llt proc(llt b){
    for(int i=1;i<16;++i){
        if(A[i] == b) return i;
    }
    return -1;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    A.push_back(0);
    A.push_back(1);
    for(int i=2;i<20;++i){
        llt ans = 1;
        for(int j=0;j<i;++j) ans *= i;
        A.push_back(ans);
    }
    llt b; cin >> b;
    cout << proc(b) << endl;
    return 0;
}