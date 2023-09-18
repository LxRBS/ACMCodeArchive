/**
 * 二维树状数组区间修改区间查询，令A为源数组，D为差分数组
 * 则
 * SIGMA{A,[1,r][1,c]} = r*c*SIGMA{D} + SIGMA{D*(i-1)*(j-1)} - c * SIGMA{D*(i-1)} - r * SIGMA{D*(j-1)}
 * 因此用4个树状数组维护上面4个差分数组，每个数组均是二维的，每个数组的每个普通操作均有4个
 * 因此每次操作的复杂度为O(16logN)
 */
#include <bits/stdc++.h>
using namespace std;

#include <bits/extc++.h>
using namespace __gnu_pbds;

struct FenwickTree2D{ // 二维树状数组

using value_type = long long int;
using vec_type = vector<value_type>;

int n, m;
vector<vec_type> c;

FenwickTree2D() = default;

static int lowbit(int x){return x & -x;}

void init(int nn, int mm){this->c.assign((this->n=nn) + 1, vec_type((this->m=mm) + 1, 0));}

void modify(int x, int y, value_type delta){
    for(int i=x;i<=this->n;i+=lowbit(i))for(int j=y;j<=this->m;j+=lowbit(j))this->c[i][j] += delta;
}

value_type query(int x, int y)const{
    value_type ans = 0;
    for(int i=x;i;i-=lowbit(i))for(int j=y;j;j-=lowbit(j)) ans += this->c[i][j];
    return ans;
}

value_type query(int xs, int xe, int ys, int ye)const{
    return query(xe, ye) + query(xs - 1, ys - 1) - query(xe, ys - 1) - query(xs - 1, ye);
}

};

struct RMRS2D{ // 二维树状数组区间查询区间求和

using value_type = FenwickTree2D::value_type;

FenwickTree2D d;
FenwickTree2D ijd;
FenwickTree2D id;
FenwickTree2D jd;

void init(int n, int m){
    d.init(n + 1, m + 1);
    ijd.init(n + 1, m + 1);
    id.init(n + 1, m + 1);
    jd.init(n + 1, m + 1);
}

void init(int x, int y, value_type delta){
    d.modify(x, y, delta);
    ijd.modify(x, y, delta * (x - 1) * (y - 1));
    id.modify(x, y, (x - 1) * delta);
    jd.modify(x, y, (y - 1) * delta);
}

/// 原数组上的区间修改映射为差分数组上的4个单点修改
/// 一共有4个差分数组，因此共有16个操作
void modify(int xs, int xe, int ys, int ye, value_type delta){
    d.modify(xs, ys, delta); d.modify(xe + 1, ye + 1, delta);
    d.modify(xs, ye + 1, -delta); d.modify(xe + 1, ys, -delta);
    ijd.modify(xs, ys, delta * (xs - 1) * (ys - 1)); ijd.modify(xe + 1, ye + 1, delta * xe * ye);
    ijd.modify(xs, ye + 1, -delta * (xs - 1) * ye); ijd.modify(xe + 1, ys, -delta * xe * (ys - 1));
    id.modify(xs, ys, delta * (xs - 1)); id.modify(xe + 1, ye + 1, delta * xe);
    id.modify(xs, ye + 1, -delta * (xs - 1)); id.modify(xe + 1, ys, -delta * xe);
    jd.modify(xs, ys, delta * (ys - 1)); jd.modify(xe + 1, ye + 1, delta * ye);
    jd.modify(xs, ye + 1, -delta * ye); jd.modify(xe + 1, ys, -delta * (ys - 1));
    return;
}

value_type query(int x, int y) const {
    return d.query(x, y) * x * y + ijd.query(x, y) - y * id.query(x, y) - x * jd.query(x, y);
}

/// 普通的区间查询也是16个操作
value_type query(int xs, int xe, int ys, int ye) const {
    return query(xe, ye) + query(xs - 1, ys - 1) - query(xs - 1, ye) - query(xe, ys - 1);
}

};

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int n, m; cin >> n >> m;
    RMRS2D tree; tree.init(n, m);
    int cmd, xs, ys, xe, ye;
    while(cin >> cmd >> xs >> ys >> xe >> ye){
        if(1 == cmd){
            int x; cin >> x;
            tree.modify(xs, xe, ys, ye, x);
        }else if(2 == cmd){
            cout << tree.query(xs, xe, ys, ye) << endl;
        }else{
            assert(0);
        }
    }
    return 0;
}