/**
 * 给定8个数判断是否满足一定的条件。 
 */
#include <bits/stdc++.h>
using namespace std;

using llt = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;

bool proc(const vi & v){
    for(int i=1;i<8;++i){
        if(v[i - 1] > v[i]) return false;
    }
    for(auto i : v){
        if(!(100 <= i and i <= 675)) return false;
        if(i % 25) return false;
    }
    return true;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    vi a(8, 0);
    for(auto & i : a) cin >> i;
    cout << (proc(a)?"Yes":"No") << endl;
    return 0;
}