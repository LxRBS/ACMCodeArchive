/**
 * 本质上就是分数排序
 */
#include <bits/stdc++.h>
using namespace std;

using llt = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;
using int128 = __int128_t;

struct _t{
    int pos;
    llt a;
    llt b;
};

int N;
vector<_t> A;

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N;
    A.assign(N, {});
    for(int i=0;i<N;++i){
        A[i].pos = i;
        cin >> A[i].a >> A[i].b;
    }

    sort(A.begin(), A.end(), [](const _t & u, const _t & v){
        auto uu = (int128)u.a * (int128)(v.a + v.b);
        auto vv = (int128)v.a * (int128)(u.a + u.b);
        if(uu != vv) return uu > vv;
        return u.pos < v.pos;
    });

    for(auto & i : A) cout << i.pos + 1 << " ";
    cout << endl;
    return 0;
}