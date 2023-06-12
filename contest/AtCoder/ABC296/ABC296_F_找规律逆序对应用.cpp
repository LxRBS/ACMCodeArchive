/**
 * 给定数组A和B，可以做如下操作，选择i,j,k三个位置，swap(Ai, Aj), swap(Bi, Bk)
 * 问允许任意次操作，能否将A、B变得相同。
 * 首先显然可以用一个简单方法判断肯定无法达成目标的情况
 * 其次考虑存在存在Ai==Aj的情况，则利用这两个位置可以更改B中任意两个位置的元素的顺序，因此必然可以
 * 再次考虑从A到B的映射的角度考虑，则上述操作可以等价于Bijk变为Bkij。这个操作是不改变逆序对数量的。
 * 因此，只需检查A和B的逆序对数量的奇偶性即可
 */
#include <bits/stdc++.h>
using namespace std;

using llt = long long;
using vi = vector<int>;

struct Bit{

int n;
vi C;

Bit() = delete;
Bit(int nn):n(nn),C(nn+1, 0){}

static int lowbit(int x){return x & -x;}

void modify(int pos){
    for(int i=pos;i<=n;i+=lowbit(i))C[i] += 1;
}

int query(int pos){
    int s = 0;
    for(int i=pos;i;i-=lowbit(i)) s += C[i];
    return s;
}

int query(int a, int b){return query(b) - query(a - 1);}

};

llt f(vi & vec){
    static int const n = 200001;
    Bit bit(n);

    llt ans = 0;
    for(auto i : vec){
        ans += bit.query(i + 1, n);
        bit.modify(i);
    }
    return ans;
}

int N;
vi A, B;

bool proc(){
    bool flag = false;
    map<int, int> ma, mb;
    for(auto i : A) ++ma[i];
    for(auto i : B) ++mb[i];
    if(ma.size() != mb.size()) return false;

    for(const auto & p : ma){
        auto it = mb.find(p.first);
        if(it == mb.end()) return false;
        if(p.second != it->second) return false;
        if(p.second > 1) flag = true;
    }

    if(flag) return true;

    auto ia = f(A) % 2;
    auto ib = f(B) % 2;
    return ia == ib;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N;
    A.assign(N, 0);
    for(auto & i : A) cin >> i;
    B.assign(N, 0);
    for(auto & i : B) cin >> i;
    cout << (proc()?"Yes":"No") << endl;
    return 0;
}