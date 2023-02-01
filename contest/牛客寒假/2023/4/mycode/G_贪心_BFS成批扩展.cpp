/**
 * 给一个800*800的迷宫，其中JJ必须按照迷宫格子的字母走，即UDLR分别表示上下左右各走一步。
 * ZN可以随意走。初始，ZN在S。给定最多10个询问，每次问，如果JJ从T开始运动，则ZN至少要多长时间可以与JJ走到同一格。
 * 首先显然有一个贪心的思想，无论ZN要去哪一格，都可以用最短时间到达，然后剩下的时间原地等待即可。
 * ZN的起点是固定的，因此事先求出ZN到达所有格子的最短时间。
 * 只有10个询问，因此每次都重新走一遍。从T出发，根据地板的字母模拟即可。
 * 每次记录JJ到达pos的时间，如果ZN能够在那之前或者同时到达，则答案就是JJ到pos的时间
 * 如果某个pos ZN无法到达，则肯定所有JJ的位置ZN都是无法到达的，返回 -1
 * 如果JJ最后停留在某个位置，则答案就是ZN到达该位置的时间。
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
int const SIZE = 13;
#else
int const SIZE = 810;
#endif

using pii = pair<int, int>;


int const DR[] = {-1, 1, 0, 0};
int const DC[] = {0, 0, -1, 1};

int Q;
int N, M;
pii S, T;

char Board[SIZE][SIZE];

map<pii, int> D;

void init(){
    queue<pii> q;
    q.push(S);
    D[S] = 0;
    int k = 0;
    int sz = 0;
    while(sz = q.size()){
        ++k;
        while(sz--){
            auto h = q.front(); q.pop();
            for(int i=0;i<4;++i){
                auto dx = h.first + DR[i];
                auto dy = h.second + DC[i];
                if(0 <= dx && dx < N && 0 <= dy && dy < M && Board[dx][dy] != '#'){
                    auto it = D.find({dx, dy});
                    if(it == D.end()){
                        it = D.insert(it, {{dx, dy}, k});
                        q.push({dx, dy});
                    }
                }
            }
        }
    } 
    return;
}

inline bool isOK(int x, int y){
    return 0 <= x && x < N && 0 <= y && y < M && Board[x][y] != '#';
}

pii move(pii p){
    switch(Board[p.first][p.second]){
        case 'L':{
            auto nr = p.first, nc = p.second - 1;
            if(isOK(nr, nc)) return {nr, nc};
            return p;
        }
        case 'R':{
            auto nr = p.first, nc = p.second + 1;
            if(isOK(nr, nc)) return {nr, nc};
            return p;            
        }
        case 'U':{
            auto nr = p.first - 1, nc = p.second;
            if(isOK(nr, nc)) return {nr, nc};
            return p;            
        }
        case 'D':{
            auto nr = p.first + 1, nc = p.second;
            if(isOK(nr, nc)) return {nr, nc};
            return p;                
        }
        case '.': return p;
        case '#':assert(0);
        default:assert(0);
    }
    return {-10000000,-100000000};
}

int proc(){
    auto cur = T;
    int k = 0;
    while(1){
        auto it = D.find(cur);
        if(it == D.end()) return -1;
        if(it != D.end() && it->second <= k) return k;

        auto tmp = move(cur);
        if(tmp == cur) return it->second;

        cur = tmp;
        ++k;
    }
    return -1;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    // ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    scanf("%d%d%d%d%d", &N, &M, &S.first, &S.second, &Q);
    for(int i=0;i<N;++i) scanf("%s", Board[i]);
    init();
    for(int q=1;q<=Q;++q){
        T.first = getInt(); T.second = getInt();
        printf("%d\n", proc());
    }
    return 0;
}