/**
 * H*W的矩阵，从左上走到右下，双方轮流走
 * 只能往右走一格或者往下走一格。
 * 走到'+'得一分，走到'-'扣一分，问结果
 * 令Dij为从(i, j)走到终点的先手得分
 * 做一个负值最大函数的深搜即可
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
int const SZ = 2E5+10;
#endif

int const INF = 100000000;

void mymax(int & a, int b){
    if(a < b) a = b;
}

inline int get(char ch){
    if('+' == ch) return 1;
    if('-' == ch) return -1;
    assert(0);
    return 0;
}

int H, W;
vector<string> Board;
vvi D;

int dfs(int r, int c){
    if(D[r][c] != -INF) return D[r][c];

    int ans = - INF;
    if(c < W - 1){
        auto tmp = get(Board[r][c+1]) - dfs(r, c + 1);
        mymax(ans, tmp);
    }
    if(r < H - 1){
        auto tmp = get(Board[r+1][c]) - dfs(r + 1, c);
        mymax(ans, tmp);
    }
    return D[r][c] = ans;
}

int proc(){
    D.assign(H, vi(W, -INF));
    D[H - 1][W - 1] = 0;
    auto ans = dfs(0, 0);
    if(ans > 0) return 1;
    if(ans < 0) return 2;
    return 0;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> H >> W;
    Board.assign(H, "");
    for(auto & s : Board) cin >> s;
    static const array<string, 3> Name = {"Draw", "Takahashi", "Aoki"}; 
    cout << Name[proc()] << endl;
    return 0;
}