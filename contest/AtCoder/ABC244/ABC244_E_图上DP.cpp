/**
 * 给定N个点M条边的图，N在2000
 * 求满足下列条件的路径的数量
 * 1. 起点为S，终点为T，S和T是已知的
 * 2. 长度为K
 * 3. 路径中X节点出现的次数是偶数，X是已知的
 * 设Aij为从S出发到点i走j步且X为奇数的方案总数，
 * Bij为从S出发到点i走j步且X为偶数的方案总数
 * 则如果j!=X, Aij = SIGMA{Ak[j-1], k到i有一条边},
 *             Bij = SIGMA{Bk[j-1], k到i有一条边}
 * 如果j===X，Aij = SIGMA{Bk[j-1], k到i有一条边},
 *             Bij = SIGMA{Ak[j-1], k到i有一条边}
 * 使用类似SPFA的技巧，用队列安排刷表法的顺序求DP
 * 最后答案就是B[T][K]
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
int const SIZE = 45;
#else
int const SIZE = 2010;
#endif

typedef vector<int> vi;
typedef long long llt;
llt const MOD = 998244353LL;

vi G[SIZE];
int N, M, K, S, T, X;

llt A[SIZE][SIZE], B[SIZE][SIZE];
bool Flag[2][SIZE];

llt proc(){
	B[S][0] = 1;
    queue<int> q; q.push(S); 
	int osn = 0;
	Flag[0][S] = true;	
	int t = 0;
	while(!q.empty()){
        ++t;
        int sz = q.size();
		while(sz--){
			int h = q.front(); q.pop(); Flag[osn][h] = false;
			for(int v: G[h]){
				if(v != X){
                    (B[v][t] += B[h][t-1]) %= MOD;
					(A[v][t] += A[h][t-1]) %= MOD;
				}else{
                    (B[X][t] += A[h][t-1]) %= MOD;
					(A[X][t] += B[h][t-1]) %= MOD;
				}
				if(!Flag[osn^1][v]){
					q.push(v); Flag[osn^1][v] = true;
				}				
			}
		}
		osn ^= 1;
		if(t == K) break;
	}
	llt ans = B[T][K];
	return ans;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    N = getInt(); M = getInt();
	K = getInt(); S = getInt();
	T = getInt(); X = getInt();
	for(int a,b,i=0;i<M;++i){
		a = getInt(); b = getInt();
		G[a].push_back(b);
		G[b].push_back(a);
	}
	cout<<proc()<<endl;
    return 0;
}