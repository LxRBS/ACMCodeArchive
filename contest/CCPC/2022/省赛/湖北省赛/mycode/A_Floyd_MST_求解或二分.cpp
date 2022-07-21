/**
 * 300个节点的无向图，分为普通节点和核酸检测站，必须时刻保证两次核酸检测的时间差不超过GAP
 * 例如在第0s作为过核酸检测，则在第GAP（或者更靠前）秒必须再做一次
 * 意思就是此时必须位于检测站节点。
 * 给定边的长度，问能够合法的走遍所有节点的最小整数速度是多少
 * 显然可以用二分构建框架，但实际上可以直接求解，只需求出最长关键路径即可
 * 首先显然要跑一个Floyd，对于普通节点，其关键路径就是距离其最短的检测站的距离，再乘以2
 * 再考虑检测站之间，关键路径就是以检测站的MST上的最长路径！
 * 所有关键路径中最长的那个是整个图的关键路径，只需在GAP时间内能跑完即可 
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

char getChar(){
	char ch = __hv007();
	while(!isalpha(ch)) ch = __hv007();
	return ch;
}

#ifndef ONLINE_JUDGE
int const SIZE = 11;
#else
int const SIZE = 309;
#endif

using llt = long long;
using Real = double;
llt const INF = 1E17;

int N, M, K;
llt Gap;
llt A[SIZE][SIZE];
Real G[SIZE][SIZE];
int Station[SIZE];
bool IsStation[SIZE];

llt proc(){
	if(1 == N) return 0;
	if(0 == Gap) return -1;
	if(0 == M) return -1;

    for(int k=1;k<=N;++k)for(int i=1;i<=N;++i)for(int j=1;j<=N;++j){
		A[i][j] = min(A[i][j], A[i][k]+A[k][j]);
	}

    llt ans = 0;
	for(int i=1;i<=N;++i){
		if(IsStation[i]) continue;
		
		llt tmp = INF;
		for(int j=0;j<K;++j){
            tmp = min(tmp, A[i][Station[j]]);
		}
		ans = max(ans, tmp);
	}
	ans += ans;

	llt d[SIZE];
	bool flag[SIZE] = {false};
	fill(d, d+N+1, INF);
	d[Station[0]] = 0;

	for(int k,i,j,v,u=0;u<K;++u){
		k = -1;
		for(v=0;v<K;++v){
			j = Station[v];
			if(!flag[j] && (-1==k || d[j]<d[k])){
				k = j;
			}			
		}
        
		ans = max(ans, d[k]);
		flag[k] = true;

		for(v=0;v<K;++v){
			j = Station[v];
			if(!flag[j] && A[k][j] < d[j]){
                d[j] = A[k][j];
			}
		}		
	}	

    if(ans >= INF) return -1;
	if(ans % Gap) return ans / Gap + 1;
	return ans / Gap;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    N = getInt(); M = getInt(); K = getInt();
	Gap = getInt();
	assert(N != 1);
	for(int i=1;i<=N;++i){
		for(int j=1;j<=N;++j){
			A[i][j] = INF;
		}
		A[i][i] = 0;
	}
	for(int a,b,c,i=0;i<M;++i){
        a = getInt(); b = getInt(); c = getInt();
	    A[a][b] = A[b][a] = c;
	}
	for(int i=0;i<K;++i) IsStation[Station[i]=getInt()] = true;
	cout << proc() << endl;
    return 0;
}