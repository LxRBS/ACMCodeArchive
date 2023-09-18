/**
 * 树状数组，区间修改区间查询
 * 保持2个树状数组，分别维护差分数组和(i-1)*差分数组
 * 原数组的前缀和
 * SIGMA{Ai} = n * SIGMA{Di} - SIGMA{(i - 1) * Di}
 */
#include <bits/stdc++.h>
using namespace std;

#include <bits/extc++.h>
using namespace __gnu_pbds;

struct FenwickTree{ // 树状数组

using value_type = long long int;
using vec_type = vector<value_type>;

int n;
vec_type c;

FenwickTree() = default;

static int lowbit(int x){return x & -x;}

void init(int nn){this->c.assign((this->n=nn) + 1, 0);}

void modify(int pos, value_type delta){
    for(int i=pos;i<=this->n;i+=lowbit(i)) this->c[i] += delta;
}

value_type query(int pos)const{
    value_type ans = 0;
    for(int i=pos;i;i-=lowbit(i)) ans += this->c[i];
    return ans;
}

value_type query(int s, int e)const{return this->query(e) - this->query(s - 1);}

};


struct RMRS{ // 区间修改区间求和

using value_type = FenwickTree::value_type;

FenwickTree d;  // 差分数组
FenwickTree id; // (i - 1) * 差分数组

void init(int n){
    d.init(n + 1);
    id.init(n + 1);
}

void init(int pos, value_type delta){
    d.modify(pos, delta);
    id.modify(pos, (pos - 1) * delta);
}

void modify(int s, int e, value_type delta){
    d.modify(s, delta); d.modify(e + 1, -delta);
    id.modify(s, (s - 1) * delta);
    id.modify(e + 1, e * - delta);
}

value_type query(int pos) const {
    return pos * d.query(pos) - id.query(pos);
}

value_type query(int s, int e) const {
    return query(e) - query(s - 1);
}

};

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int n, q; cin >> n >> q;
    RMRS tree; tree.init(n);
    int pre = 0;
    for(int a,i=1;i<=n;++i){
        cin >> a;
        tree.init(i, a - pre); // 此处不能用modify(i, i, x)
        pre = a;
    }
    for(int cmd,qi=1;qi<=q;++qi){
        cin >> cmd;
        if(1 == cmd){
            int s, e, x; cin >> s >> e >> x;
            tree.modify(s, e, x);
        }else if(2 == cmd){
            int s, e; cin >> s >> e;
            cout << tree.query(s, e) << endl;
        }else{
            assert(0);
        }
    }
    return 0;
}