/**
 * 二维数组A，从左上到右下有多少天路径满足本路径上的数值是互异的。
 * 注意到规模只有10，暴力深搜即可
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
int const SIZE = 21;
#else
int const SIZE = 66;
#endif

using llt = long long;
using vi = vector<int>;
using vll =vector<llt>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vpii = vector<pii>;
using ull = unsigned long long;

int H, W;
vvi A;
llt Ans;

void dfs(int r, int c, set<int> & s){
    if(r + 1 == H and c + 1 == W){
		++Ans;
		return;
	}

    if(r + 1 < H){
		if(!s.count(A[r + 1][c])){
			s.insert(A[r + 1][c]);
			dfs(r + 1, c, s);
			s.erase(A[r + 1][c]);
		}
	}

	if(c + 1 < W){
		if(!s.count(A[r][c + 1])){
			s.insert(A[r][c + 1]);
			dfs(r, c + 1, s);
			s.erase(A[r][c + 1]);
		}
	}
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	// int nofkase; scanf("%d", &nofkase);
    H = getInt(); W = getInt();
	A.assign(H, vi(W, 0));
	for(auto & vec : A){
		for(auto & i : vec) i = getInt();
	}

    Ans = 0;
	set<int> ss;
	ss.insert(A[0][0]);
    dfs(0, 0, ss);
	assert(ss.size() == 1 and *ss.begin() == A[0][0]);
	cout << Ans << endl;
    return 0; 
}


