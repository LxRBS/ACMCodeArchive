/**
 * 给定一个排列，Alice首先任选一个位置放下棋子，然后Bob、Alice轮流走
 * 对于当前位置i，如果其左边存在某个位置j且Pj < Pi，则可以将棋子走到位置j
 * 轮到某人，如果无法走动，则该人获胜
 * 问，Alice获胜的初始位置有多少个。
 * 将不能走的位置的集合记作C0，只能去C0的位置集合记作C1，于是C1为必胜位置。
 * 由于本题的规则，可以发现能去C1位置的点必然能去C0，且必然是必败位置。
 * 因此只要考虑C0和C1即可。
 * 对每一个Pi，只要左边没有出现过比它小的数，则i属于C0；
 * 如果左边比它小的数是C0里面的数，则i就属于C1。
 * 如果判断坐标比Pi小的数都是C0里面的数？注意到C0里面可能有很多数，但必然都是连续的，
 * 因此只需保留一个即可。
 * 因此对于每一个Pi，如果左边比它小的数只有一个，i位置就是必胜位置。
 * 典型的权值树状数组。O(NlogN)。
 * 标程是O(N)
 */
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
int const SZ = 200000 + 12;
#endif

struct bit_t{

int n;
vi c;

static int lowbit(int x){return x & -x;}

void init(int nn){this->c.assign((this->n=nn) + 1, 0);}

void modify(int pos, int delta){
    for(int i=pos;i<=n;i+=lowbit(i)) c[i] += delta;
}

int query(int pos) const {
    int ans = 0;
    for(int i=pos;i;i-=lowbit(i)) ans += c[i];
    return ans;
}

int query(int e, int s)const{return query(e) - query(s - 1);}

}Bit;

int N;
vi A;

int proc(){
    int ans = 0;
    int std = A[0];
    int level = 1;
    Bit.init(N);
    Bit.modify(A[0], 1);
    for(int i=1;i<N;++i){
        auto t = Bit.query(A[i] - 1);
        if(0 == t){
            Bit.modify(std, -1);
            std = A[i];
        }else if(1 == t){
            ++ans;
        }
        Bit.modify(A[i], 1);
    }
    return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int nofkase; cin >> nofkase;
    while(nofkase--){
        cin >> N;
        A.assign(N, 0);
        for(auto & i : A) cin >> i;
        cout << proc() << endl;
    }
    return 0;
}
