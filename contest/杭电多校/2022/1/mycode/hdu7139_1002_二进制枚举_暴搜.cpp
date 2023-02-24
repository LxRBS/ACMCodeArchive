/**
 *  N*M的方格，有K堵横平竖直的墙
 *  给定起点和终点，问从起点到终点最少要打掉几堵墙
 *  NMK都在15。
 *  最开始使用最短路，但是不对，因为打掉一堵墙可能会影响多个格子的连通性
 *  由于规模很小，暴搜就行，从0到Kfor每一个候选答案再for具体打墙的方案
 *  在格子上做一个深搜即可。用并查集也可以。
 */
#include <bits/stdc++.h>
using namespace std;

char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)

int getInt(){
    int sgn = 1;
    char ch = __hv007();
    while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = __hv007();
    if ( '-' == ch ) {sgn = 0;ch=__hv007();}

    int ret = (int)(ch-'0');
    while( '0' <= (ch=__hv007()) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
    return sgn ? ret : -ret;
}

#ifndef ONLINE_JUDGE
int const SIZE = 106;
#else
int const SIZE = 1E3+100;
#endif

using pii = pair<int, int>;
using vpii = vector<pii>;

int const DR[] = {-1, 1, 0, 0};
int const DC[] = {0, 0, -1, 1};

inline int ABS(int x){return x>=0?x:-x;}

using ppii = pair<pii, int>;
using vppii = vector<ppii>;
vppii Shu[22], Heng[22];
int N, M, K;
int XS, YS, XT, YT;
bool Flag[300];

/// 找横线
int findHeng(int y, int x1, int x2, int status){
    int ans = 0;
    for(const auto & p: Heng[y]){
        if(status & (1 << p.second)) continue;
        if(p.first.first <= x1 && x2 <= p.first.second){
            return 1;
        }
    }
    return 0;
}

int findShu(int x, int y1, int y2, int status){
    int ans = 0;
    for(const auto & p: Shu[x]){
        if(status & (1 << p.second)) continue;
        if(p.first.first <= y1 && y2 <= p.first.second){
            return 1;
        }
    }
    return 0;
}

inline int id(int x, int y){
    return x * M + y + 1;
}

bool isConn(int x1, int y1, int x2, int y2, int status){
    if(x1 == x2){
        if(y1 > y2) swap(y1, y2); assert(y1 + 1 == y2);
        int t = findHeng(y2, x1, x1+1, status);
        return 0 == t;
    }else if(y1 == y2){
        if(x1 > x2) swap(x1, x2); assert(x1 + 1 == x2);
        int t = findShu(x2, y1, y1+1, status);
        return 0 == t;
    }
    assert(1);
    return 0;
}

bool g(int status){
    function<bool (int, int)> dfs = [&](int x, int y)->bool{
        if(x == XT && y == YT){
            return true;
        }
        // cout<<x<<", "<<y<<endl;
        Flag[id(x, y)] = true;
        for(int nr,nc,i=0;i<4;++i){
            nr = x + DR[i]; nc = y + DC[i];
            if(0 <= nr && nr < N && 0 <= nc && nc < M && !Flag[id(nr, nc)] && isConn(x, y, nr, nc, status)){
                bool b = dfs(nr, nc);
                if(b) return true;
            }
        }
        return false;
    };
    memset(Flag, 0, sizeof(Flag));
    bool b = dfs(XS, YS);
    return b;
}

bool isOK(int const limit){
    function<bool (int, int, int)> dfs = [&](int pos, int cnt, int status)->bool{
        if(cnt == limit){
            if(g(status)){
                return true;
            }
            return false;
        }

        if(pos == K) return false;

        bool b = dfs(pos+1, cnt+1, status|(1<<pos));
        if(b) return true;
        b = dfs(pos+1, cnt, status);
        return b;
    };
    bool b = dfs(0, 0, 0);
    return b;
}

int proc(){
    for(int ans=0;ans<=K;++ans){
        if(isOK(ans)) return ans;
    }   
    throw runtime_error("XX");
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif  
    int nofkase = getInt();
    while(nofkase--){
        for(int i=0;i<22;++i){
            Heng[i].clear(); Shu[i].clear();
        }

        N = getInt(); M = getInt(); K = getInt();
        XS = getInt(); YS = getInt();
        XT = getInt(); YT = getInt();
        for(int i=0;i<K;++i){
            int x1 = getInt();
            int y1 = getInt();
            int x2 = getInt();
            int y2 = getInt();
            if(x1 == x2){ // 竖线
                if(y1 > y2) swap(y1, y2);
                Shu[x1].emplace_back(pii({y1, y2}), i);
            }else{
                if(x1 > x2) swap(x1, x2);
                Heng[y1].emplace_back(pii({x1, x2}), i);
            }
        }
        cout << proc() << endl;
    }
    return 0;
}