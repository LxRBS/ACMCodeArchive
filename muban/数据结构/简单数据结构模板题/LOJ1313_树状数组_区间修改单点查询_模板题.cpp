/**
 * 使用树状数组维护差分数组可以实现源数组的区间修改单点查询
 * 区间修改映射为差分数组上的2个单点修改
 * 单点查询映射为差分数组上的1个区间查询
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


int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int n, q; cin >> n >> q;
    FenwickTree tree; tree.init(n + 1);
    int pre = 0;
    for(int a,i=1;i<=n;++i){
        cin >> a;
        tree.modify(i, a - pre);
        pre = a;
    }
    for(int cmd,x,y,d,qi=1;qi<=q;++qi){
        cin >> cmd >> x;
        if(1 == cmd){
            cin >> y >> d;
            tree.modify(x, d);
            tree.modify(y + 1, -d);
        }else if(2 == cmd){
            cout << tree.query(x) << endl; 
        }else{
            assert(0);
        }
    }
    return 0;
}