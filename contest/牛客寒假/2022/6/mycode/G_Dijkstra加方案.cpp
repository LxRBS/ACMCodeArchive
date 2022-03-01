/**
 * 给定一个二维数组，Aij为LRUD四个字母之一，表示四个方向，只能按照格子的指令行进
 * 问最少改几个格子，可以沿着格子的指令从左上走到右下，并给出方案
 * 本质上就是最短路求方案
*/
#include <bits/stdc++.h>
using namespace std;

int const _SS123_ = 100001;
char *__abc147, *__xyz258, __ma369[_SS123_];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,_SS123_,stdin),__abc147==__xyz258) ? EOF : *__abc147++)

int getUnsigned(){
	char ch = __hv007();
	while( ch < '0' || ch > '9' ) ch = __hv007();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = __hv007() ) && ch <= '9' ) ret = (ret<<1) + (ret<<3) + (int)(ch-'0');
	return ret;
}

char getChar(){
    char ch = __hv007();
    while(ch != 'L' && ch != 'R' && ch != 'U' && ch != 'D') ch = __hv007();
    return ch;
}

#ifndef ONLINE_JUDGE
int const SIZE = 1113;
#else
int const SIZE = 1010;
#endif

char const OUT[] = "LRUD";
int S2I[256];

typedef pair<int, int> pii;


int const DR[] = {0, 0, -1, 1};
int const DC[] = {-1, 1, 0, 0};

int N, M;
int A[SIZE][SIZE];


pair<int, int> Pre[SIZE][SIZE];
int D[SIZE][SIZE];
bool Flag[SIZE][SIZE];

struct t3{
    int r, c, w;
    t3(int a=0,int b=0,int ww=0):r(a),c(b),w(ww){}
};

struct cmp{
    bool operator()(const t3&a, const t3&b)const{
        if(a.w != b.w) return a.w > b.w;
        if(a.r != b.r) return a.r < b.r;
        return a.c < b.c;
    }
};

priority_queue<t3, vector<t3>, cmp> Q;

void proc(){
    if(1 == N && 1 == M){
        return (void)printf("0\n");
    }

    while(!Q.empty()) Q.pop();

    Q.push({1, 1, 0}); 
    D[1][1] = 0;
    Pre[1][1] = {0, 0};

    while(1){
        
        while(!Q.empty() && Flag[Q.top().r][Q.top().c]) Q.pop();
        if(Q.empty()) break;

        t3 h = Q.top(); Q.pop();
        Flag[h.r][h.c] = true;
        if(h.r == N && h.c == M){
            break;
        }

        int ori = A[h.r][h.c];

        for(int i=0;i<4;++i){
            int nr = h.r + DR[i];
            int nc = h.c + DC[i];     

            if(nr<=0||nr>N||nc<=0||nc>M) continue;
            if(Flag[nr][nc]) continue;

            int tmp = D[h.r][h.c] + (ori!=i?1:0);

            if(tmp < D[nr][nc]){
                Pre[nr][nc] = {h.r, h.c};
                Q.push({nr, nc, D[nr][nc] = tmp});
            }
        }        
    }

    auto g = [](int r, int c, int nr, int nc)->char{
        if(c-1 == nc) return 'L';
        if(c+1 == nc) return 'R';
        if(r-1 == nr) return 'U';
        if(r+1 == nr) return 'D';
        return '\0';
    };

    printf("%d\n", D[N][M]);
    int r = N, c = M;
    while(1){
        auto &p = Pre[r][c];
        if(0 == p.first && 0 == p.second) break;
        if(D[r][c] != D[p.first][p.second]){
            printf("%d %d %c\n", p.first, p.second, g(p.first, p.second, r, c));    
        } 
        r = p.first;
        c = p.second;
    }  

    return;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    S2I['L'] = 0; S2I['R'] = 1; S2I['U'] = 2; S2I['D'] = 3;
    int nofkase = getUnsigned();
    while(nofkase--){
        N = getUnsigned();
        M = getUnsigned();
        for(int i=1;i<=N;++i)for(int j=1;j<=M;++j){
            D[i][j] = 1000000000;
            Flag[i][j] = false;
            switch(getChar()){
                case 'L': A[i][j] = 0;break;
                case 'R': A[i][j] = 1;break;
                case 'U': A[i][j] = 2;break;
                case 'D': A[i][j] = 3;break;
                default:throw runtime_error("XX");
            }
        }
        proc();
    }

    return 0;
}