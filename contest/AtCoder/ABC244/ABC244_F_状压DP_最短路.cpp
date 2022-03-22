/**
 * N个点M条边的无向图，N在17
 * 给定一个长度为N的01字符串S
 * 对于一条路径，如果：Si是0，则该路径含有偶数个i，如果Si是1，则该路径含有奇数个i
 * 则称该路径是满足条件的
 * 对所有可能的字符串S，对每一个字符串求出满足条件的最短路径长度，最后求和
 * 显然所有可能的字符串是2^17个，需要用到状压DP
 * 设Dijs为从i到j且状态为s的最短路径，枚举每一个起点i，跑一个最短路即可
 * Dijs = min{Dik[s^(1<<j-1)]，k到j有一条边}
 * 标程设计的状态是Dsi，表示状态为s以i结尾的最短路，空间少一维，时间？
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
int const SIZE = 10;
#else
int const SIZE = 18;
#endif

typedef vector<int> vi;
typedef long long llt;
llt const INF = 0x3FFFFFFF;

vi G[SIZE];
int N, M;
bool Flag[SIZE][(1<<SIZE-1)];
llt D[SIZE][SIZE][(1<<SIZE-1)];

void proc(int idx){
	llt (&d)[SIZE][(1<<SIZE-1)] = D[idx];
	memset(d, -1, sizeof(d));
	memset(Flag, 0, sizeof(Flag));

	queue<pair<int, int> > q;
	q.push({idx, 1<<idx-1});
	d[idx][1<<idx-1] = 0;

    Flag[idx][1<<idx-1] = true;
    int t = 0;
	while(!q.empty()){
        ++t;
        int sz = q.size();
		while(sz--){
            auto p = q.front(); q.pop();
			int h = p.first; int st = p.second;
			Flag[h][st] = false;

		    for(int v: G[h]){
                int nst = st ^ (1<<v-1);
				if(-1 == d[v][nst] || d[v][nst] > 1 + d[h][st]){
					d[v][nst] = 1 + d[h][st];
					if(!Flag[v][nst]){
						Flag[v][nst] = true;
						q.push({v, nst});
					}
				}
			}
		}
	} 
}

llt f(int status){
	if(0 == status) return 0;
	int c = 0;
	for(int i=0;i<N;++i){
        if((1<<i)&status) ++c;
		if(c>=2) break;
	}
	if(1 == c) return 1;
	llt ans = -1;
	for(int i=1;i<=N;++i)for(int j=1;j<=N;++j){
		if(-1 == D[i][j][status]) continue;
        if(-1 == ans || ans > D[i][j][status]){
			ans = D[i][j][status];	
		}
	}
	assert(ans != -1);
	return ans + 1;
}
llt proc(){
    for(int i=1;i<=N;++i){
		proc(i);
	}
	llt ans = 0;
	for(int i=0;i<(1<<N);++i){
        ans += f(i);
	}
	return ans;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    N = getInt(); M = getInt();
	for(int a,b,i=0;i<M;++i){
		a = getInt(); b = getInt();
		G[a].push_back(b);
		G[b].push_back(a);
	}
	cout<<proc()<<endl;
    return 0;
}