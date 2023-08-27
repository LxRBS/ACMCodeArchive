/**
 * H*W的迷宫，有一个起点一个终点，有障碍物，有守卫
 * 问从起点到终点的最短步数是多少
 * 首先预处理守卫，将守卫看到的地区全部打标记。
 * 最多将全图打上两遍标记，因此预处理是O(2HW)的
 * 然后就是基本的广搜，O(HW)
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

int const DR[] = {-1, 1, 0, 0};
int const DC[] = {0, 0, -1, 1};

int H, W;
vector<string> Board;
vvi Flag;
pii Start, Goal;

void proc(int r, int c, int dr, int dc){
    assert(0 == dr or 0 == dc);
    if(0 == dr){
        while(1){
            Flag[r][c] = 1;
            c += dc;
            if(c < 0 or c >= W) break;
            if(Board[r][c] != '.') break;
        }
        return;
    }

    while(1){
        Flag[r][c] = 1;
        r += dr;
        if(r < 0 or r >= H) break;
        if(Board[r][c] != '.') break;
    }
    return;
}

int proc(){
    Flag.assign(H, vi(W, 0));
    for(int i=0;i<H;++i){
        for(int j=0;j<W;++j){
            switch(Board[i][j]){
                case 'S': Start = {i, j}; break;
                case 'G': Goal = {i, j}; break;
                case '>': proc(i, j, 0, 1); break;
                case '<': proc(i, j, 0, -1); break;
                case '^': proc(i, j, -1, 0); break;
                case 'v': proc(i, j, 1, 0); break;
                case '#':
                case '.': break;
                default: assert(0);
            }
        }
    }

    queue<pii> q;
    q.push(Start);
    Flag[Start.first][Start.second] = 1;

    int k = 0, sz = 0;
    while(sz = q.size()){
        ++k;
        while(sz--){
            auto h = q.front(); q.pop();
            for(int nr,nc,i=0;i<4;++i){
                nr = h.first + DR[i];
                nc = h.second + DC[i];
                if(0 <= nr and nr < H and 0 <= nc and nc < W){
                    if(Board[nr][nc] == 'G'){
                        return k;
                    }     
                    if(Board[nr][nc] == '.' and 0 == Flag[nr][nc]){
                        Flag[nr][nc] = 1;
                        q.push({nr, nc});
                    }
                }
            }
        }
    }
    return -1;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> H >> W;
    Board.assign(H, "");
    for(auto & s : Board) cin >> s;
    cout << proc() << endl;
    return 0;
}