/**
 * G题的HARD版本，一共有1E5的询问，因此需要有一个log算法。
 * 所有可能的路径其实一个内向基环树的森林。在树上很难做二分，可以考虑倍增
 * 当然不需要实际建树。注意到JJ的走法其实是确定的，
 * 即从任意一点出发，走1步、2步、4步能到的点与询问无关，只跟地图有关
 * 令B[k][pos]是pos位置经过2^k步能够到达的位置，可以预处理出B数组。
 * 对于每个询问T，如果位置W满足：JJ从T走到W的步数大于等于D[W]，则可以相遇
 * 注意到这个条件具有单调性，因为如果某个位置满足条件，则往后的位置肯定也满足，因为只需要一起移动即可
 * 于是第一个满足条件的W，从T走到W的步数即为答案。实际操作的时候，改为找到最后一个不满足条件的节点。
 * 令step为当前已经走过的步数，k为当前跨度，pos为当前位置，
 * 每一次，如果 pos + 2^k 已经满足条件了，令 k-= 1
 * 否则，令 pos = pos + 2^k， step += 2 ^ k
 * 这样最后一定停留在最后一个不满足条件的位置上，再向前走一步即可。
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
using vi = vector<int>;
using vvi = vector<vi>;

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

vector<vector<vector<pii>>> Bei;

void initJJ(){
    Bei.assign(21, vector<vector<pii>>(N, vector<pii>(M, {-1, -1})));
    
    auto & bei = Bei[0];
    for(int i=0;i<N;++i)for(int j=0;j<M;++j){
        switch(Board[i][j]){
            case '.':bei[i][j] = {i, j};break;
            case '#':bei[i][j] = {-1, -1};break;
            case 'U':bei[i][j] = isOK(i - 1, j) ? pii({i - 1, j}) : pii({i, j});break;
            case 'D':bei[i][j] = isOK(i + 1, j) ? pii({i + 1, j}) : pii({i, j});break;
            case 'L':bei[i][j] = isOK(i, j - 1) ? pii({i, j - 1}) : pii({i, j});break;
            case 'R':bei[i][j] = isOK(i, j + 1) ? pii({i, j + 1}) : pii({i, j});break;
            default:assert(0);
        }
    }

    for(int k=1;k<=20;++k){
        auto & bei = Bei[k];
        const auto & pre = Bei[k - 1];
        for(int i=0;i<N;++i)for(int j=0;j<M;++j){
            if(Board[i][j] == '#') continue;
            auto p = pre[i][j];
            bei[i][j] = pre[p.first][p.second];     
        }
    }
    
    
    // for(int i=0;i<N;++i)for(int j=0;j<M;++j){
    //     if(Board[i][j] == '#') continue;
    //     printf("(%d, %d): ", i, j);
    //     for(int k=0;k<=3;++k){
    //         printf("[%d (%d, %d)]", 1<<k, Bei[k][i][j].first, Bei[k][i][j].second);
    //     }
    //     printf("\n");
    // } 

    return;
}

int proc(){
    if(!D.count(T)) return -1;

    int ans = 0;
    auto p = T;
    for(int k=20;k>=0;--k){
        auto nxt = Bei[k][p.first][p.second];
        auto it = D.find(nxt);
        assert(it != D.end());

        if(ans + (1<<k) < it->second){
            ans += 1 << k;
            p = nxt;
        }
    }
    return ans + 1;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    // ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    scanf("%d%d%d%d%d", &N, &M, &S.first, &S.second, &Q);
    for(int i=0;i<N;++i) scanf("%s", Board[i]);
    init();
    initJJ();
    for(int q=1;q<=Q;++q){
        T.first = getInt(); T.second = getInt();
        printf("%d\n", proc());
    }
    return 0;
}