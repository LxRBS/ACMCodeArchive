/**
 * 给定一个二维矩阵，四邻域。
 * 每个格子均有一个字母，要求走过的字母按照"snukesnukesnuke..."往复循环
 * 问是否能够从左上走到右下
 * 经典广搜
 * 虽然有额外的限制条件，但这个条件是无后效的，因此搜过的点仍然可以不用再搜
 */
#include <bits/stdc++.h>
using namespace std;

using llt = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;
using int128 = __int128_t;

int const DR[] = {-1, 1, 0, 0};
int const DC[] = {0, 0, -1, 1};

int H, W;
vector<string> Board;
const string S("snuke");

bool proc(){
    if(Board[0][0] != 's') return false;

    vector<vector<bool>> flag(H, vector<bool>(W, false));
    queue<pii> q;
    
    q.push({0, 0});
    flag[0][0] = true;

    int k = 1;
    int sz;
    while(sz = q.size()){
        const char expect = S[k++];
        if(k == S.length()) k = 0;

        while(sz--){
            auto h = q.front(); q.pop();
            for(int nr,nc,i=0;i<4;++i){
                nr = h.first + DR[i];
                nc = h.second + DC[i];
                if(0 <= nr and nr < H and 0 <= nc and nc < W and !flag[nr][nc] and expect == Board[nr][nc]){
                    if(H - 1 == nr and W - 1 == nc) return true;

                    flag[nr][nc] = true;
                    q.push({nr, nc});
                }
            }
        }
    }
    return false;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> H >> W;
    Board.assign(H, "");
    for(auto & i : Board) cin >> i;
    cout << (proc() ? "Yes" : "No") << endl;
    return 0;
}