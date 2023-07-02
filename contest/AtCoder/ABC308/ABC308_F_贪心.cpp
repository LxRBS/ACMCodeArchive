/**
 * 给定N个东西的价格。再给定M个满减券，即价格大于等于L则可以少D元钱
 * 每个满减券显然只能用一次，一个商品只能用一张券
 * 问买下所有商品最少花费
 * 答案显然是原价求和，然后再减去满减之和即可。因此满减越多越好
 * 再考虑到某张满减券如果能用，用到哪件商品上其实并不重要。
 * 因此，D越大的券越要优先使用。而L和价格则是券使用的限制性条件
 * 将价格从小到大排序，将满减券按L从小到大排序
 * for 每一个价格P:
 *     将所有L<P的券的D放入优先队列q
 *     此时q的顶端就是本商品最该使用的满减券
 */
#include <bits/stdc++.h>
using namespace std;

using llt = long long;
using pii = pair<int, int>;
using pll = pair<llt, llt>;
using vi = vector<int>;
using vvi = vector<vi>;
using int128 = __int128_t;

int N, M;
vector<llt> P, L, D;
vector<pair<llt, llt>> LD;

llt proc(){
    sort(LD.begin(), LD.end());
    sort(P.begin(), P.end());
    priority_queue<llt> q;

    llt ans = accumulate(P.begin(), P.end(), 0LL);
    int k = 0;
    for(auto p : P){
        while(k < M and LD[k].first <= p){
            q.push(LD[k].second);
            ++k;
        }

        if(!q.empty()){
            auto h = q.top(); q.pop();
            ans -= h;
        }
    }
    return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> M;
    P.assign(N, 0LL);
    for(auto & i : P) cin >> i;

    L.assign(M, 0LL);
    for(auto & i : L) cin >> i;

    D.assign(M, 0LL);
    for(auto & i : D) cin >> i;

    for(int i=0;i<M;++i){
        LD.emplace_back(L[i], D[i]);
    }

    cout << proc() << endl;
    return 0;
}