/**
 * 给定N*N的棋盘，其上有一些障碍物，再给定10对起点终点，问能否从起点走到终点。
 * 每个点对互为障碍物。直接广搜即可。搜10次。
 */
#include <bits/stdc++.h>
using namespace std;

char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)
 
using llt = long long; 
llt getInt(){
	int sgn = 1;
	char ch = __hv007();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = __hv007();
	if ( '-' == ch ) {sgn = 0;ch=__hv007();}
 
	llt ret = (llt)(ch-'0');
	while( '0' <= (ch=__hv007()) && ch <= '9' ) ret = ret * 10LL + (llt)(ch-'0');
	return sgn ? ret : -ret;
}



#ifndef ONLINE_JUDGE
int const SIZE = 21;
#else
int const SIZE = 2e5+5;
#endif


using vi = vector<int>;
using vll =vector<llt>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vpii = vector<pii>;

llt const MOD = 998244353LL;

int const DX[] = {-1, 1, 0, 0};
int const DY[] = {0, 0, -1, 1};

int N, M;
int T;
vvi Board;
vector<pii> A, B;

int proc(int pos){
	int const dx = B[pos].first;
	int const dy = B[pos].second;

	int ans = 0;
	queue<pii> q;
	vvi flag(N, vi(N, 0));

	int x = A[pos].first, y = A[pos].second;
    q.push({x, y});
	flag[x][y] = 1;

	while(!q.empty()){
		int sz = q.size();
		++ans;
		while(sz--){
			auto h = q.front(); q.pop();
            for(int nx,ny,i=0;i<4;++i){
                nx = h.first + DX[i];
				ny = h.second + DY[i];
				if(nx == dx && ny == dy) return ans;

				if(0 <= nx && nx < N && 0 <= ny && ny < N && 0 == Board[nx][ny] && 0 == flag[nx][ny]){
					flag[nx][ny] = 1;
					q.push({nx, ny});
				}
			}
		}
	}
	return -1;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	// int nofkase; cin >> nofkase;
    N = getInt(); M = getInt();
	Board.assign(N, vi(N, 0));
	for(int x,y,i=0;i<M;++i){
        x = getInt(); y = getInt();
		Board[x][y] = 0x20;
	}
    T = getInt();
	A.assign(T + 1, {});
	B.assign(T + 1, {});
    for(int x,y,i=1;i<=T;++i){
        x = getInt(); y = getInt();
		A[i] = {x, y};
		Board[x][y] = i;
		x = getInt(); y = getInt();
		Board[x][y] = i | 0x10;
		B[i] = {x, y};
	}
	for(int i=1;i<=T;++i){
		printf("%d\n", proc(i));
	}
    return 0; 
}