/**
 * 判断是否为合法的数独 
 */
#include <bits/stdc++.h>
using namespace std;

using llt = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;

array<array<int, 9>, 9> A;

bool procRow(int r){
    int cnt[10] = {0};
    for(auto i : A[r]){
        if(++cnt[i] > 1) return false;
    }
    return true;
}

bool procCol(int c){
    int cnt[10] = {0};
    for(int i=0;i<9;++i){
        if(++cnt[A[i][c]] > 1) return false;
    }
    return true;
}

bool procBlock(int r, int c){
    int cnt[10] = {0};
    for(int i=0;i<3;++i)for(int j=0;j<3;++j){
        if(++cnt[A[r+i][c+j]] > 1) return false;
    }
    return true;
}

bool proc(){
    for(int i=0;i<9;++i){
        if(not procRow(i)) return false;
        if(not procCol(i)) return false;
    }
    for(int i=0;i<9;i+=3)for(int j=0;j<9;j+=3){
        if(not procBlock(i, j)) return false;
    }
    return true;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    for(auto & a : A)for(auto & i : a) cin >> i;
    cout << (proc() ? "Yes" : "No") << endl;
    return 0;
}