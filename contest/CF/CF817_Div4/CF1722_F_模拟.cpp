/**
 * 给定一个二维数组，判断其中所有的星号是否构成互不相邻的L型
 * 模拟判断即可。
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
int const SIZE = 1E2+13;
#endif

using pii = pair<int, int>;
using vpii = vector<pii>;

int const DR[] = {-1, -1, -1,  0, 1, 1,  1,  0};
int const DC[] = {-1,  0, +1, +1, 1, 0, -1, -1};

int N, M;
char A[SIZE][SIZE];

bool judge(int r, int c){
    vpii vec;
    queue<pii> q;
    vec.push_back({r, c});
    q.push({r, c});
    A[r][c] = '.';
    int sz;
    while(sz = q.size()){
        while(sz--){
            auto h = q.front(); q.pop();
            for(int i=0;i<8;++i){
                int dr = h.first + DR[i];
                int dc = h.second + DC[i];
                if(0<=dr&&dr<N&&0<=dc&&dc<M&&A[dr][dc]=='*'){
                    A[dr][dc] = '.';
                    q.push({dr, dc});
                    vec.push_back({dr, dc});
                }
            }
        }
    }
    if(vec.size() != 3) return false;
    map<int, int> mr, mc;
    for(auto p : vec){
        ++mr[p.first];
        ++mc[p.second];
    }
    if(mr.size() != 2 || mc.size() != 2) return false;
    return true;
}

bool proc(){
    for(int i=0;i<N;++i)for(int j=0;j<M;++j){
        if('.' == A[i][j]) continue;
        if(!judge(i, j)) return false;
    }
    return true;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r" ,stdin);
#endif    
    int nofkase; scanf("%d", &nofkase);
	while(nofkase--){
        scanf("%d%d", &N, &M);
        for(int i=0;i<N;++i) scanf("%s", A[i]);
        puts(proc()?"YES":"NO");
	}
    return 0;
}
