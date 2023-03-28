/**
 * 二维矩阵A，Aij为数字表示是一个雷，可以炸毁曼哈顿距离小于等于Aij的所有墙
 * 问雷全炸光后数组长什么样。规模不大，直接暴力。最后处理雷本身。
 */
#include <bits/stdc++.h>
using namespace std;

#include <bits/extc++.h>
using namespace __gnu_cxx;
using namespace __gnu_pbds;


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
int const SIZE = 21;
#else
int const SIZE = 2E5+10;
#endif

using llt = long long;
using vi = vector<int>;
using vll =vector<llt>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vpii = vector<pii>;
using ull = unsigned long long;
// using i128 = __int128_t;
using Real = long double;

Real const EPS = 1E-14;
inline int sgn(Real x) {return x > EPS ? 1 : (x < -EPS ? -1 : 0);}
inline bool is0(Real x) {return 0 == sgn(x);}

void proc(vector<string> & b, int r, int c){
	int n = b.size(), m = b[0].length();
	int d = b[r][c] - '0';
	for(int i=max(0, r-d);i<=min(n-1, r+d);++i){
		for(int j=max(0,c-d);j<=min(m-1,c+d);++j){
			if(abs(i-r) + abs(j-c) <= d){
				if(!isdigit(b[i][j])) b[i][j] = '.';
			}
		}
	}
	return;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int n, m; cin >> n >> m;
	vector<string> board(n);
	for(auto & s : board) cin >> s;
	for(int i=0;i<n;++i)for(int j=0;j<m;++j){
		if(isdigit(board[i][j])){
			proc(board, i, j);
		}
	}
	for(int i=0;i<n;++i)for(int j=0;j<m;++j){
		if(isdigit(board[i][j])){
			board[i][j] = '.';
		}
	}	
	for(const auto & s : board) cout << s << endl;
    return 0; 
}


