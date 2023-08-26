/**
 * 给定一个数组A，将Ai看作是高度可以得到一个柱状图
 * 问该柱状图是否关于直线 y=x 对称
 * 显然有O(N)的检测方法，没想明白
 * 使用成段更新，弄一个数组记作B
 * for Ai: B[1, Ai] 均 加1
 * for i: 检查 i是否等于 B[i] 即可
 * 需要用到成段更新单点查询，使用树状数组维护差分数组即可
 * O(NlogN) 
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

int N, M;
vi A, B;

struct bit_t{

int n;
vi c;

static int lowbit(int x) {return x & -x;}

void init(int nn){
    n = nn;
    c.assign(n + 1, 0);
}

void modify(int pos, int delta){
    for(int i=pos;i<=n;i+=lowbit(i)) c[i] += delta;
}

int query(int pos){
    int ans = 0;
    for(int i=pos;i;i-=lowbit(i)) ans += c[i];
    return ans;
}

int query(int s, int e){return query(e) - query(s - 1);}

}Tree;

void modify(int s, int e){
    Tree.modify(s, 1);
    Tree.modify(e + 1, -1);
}

inline int query(int pos){
    return Tree.query(1, pos);
}

bool isOK(){
    for(int i=1;i<=N;++i)if(A[i] != A[1]) return false;
    return true;
}

bool proc(){
    if(A[1] != N) return false;
    if(isOK()) return true;
    
    Tree.init(N + 1);
    for(int i=1;i<=N;++i){
        modify(1, A[i]);
    }

    for(int i=1;i<=N;++i){
        if(A[i] != query(i)) return false;
    }
    return true;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int nofkase; cin >> nofkase;
    while(nofkase--){
        cin >> N;
        A.assign(N + 1, 0);
        for(int i=1;i<=N;++i) cin >> A[i];
        cout << (proc() ? "YES" : "NO") << endl;
    }
    return 0;
}