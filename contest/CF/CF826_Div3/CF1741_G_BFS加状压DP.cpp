/**
 * N个节点的无向图。一共有F个人从节点1出发，要到各自的目的地（可能重复）。
 * 这F个人中有K个人是没有车的（K<=6）。其余人有车。有车的人可以携带任意数量的没有车的人。
 * 每辆车只会沿着最短路径走到自己的目的地（多条最短路则可以任意选一条）
 * 没车的人则可以在这其中搭顺风车
 * 问最少几人搭不了顺风车
 * 有K很小，显然可以状压。
 * 令Di表示节点i搭载的所有可能性，跑一个BFS即可得出
 * 令Y记录所有有车的节点，则原题变为了从D[Y[1]] ~ D[Y[n]]各选一个数，使得或者中的位数最多
 * 用DP即可。
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
int const SIZE = 2E5+5;
#endif

using vi = vector<int>;
using vvi = vector<vi>;
using si = set<int>;
using vsi = vector<si>;

vvi G;
int N, M, F, K;
vi YouCar;
vi MeiCar;
vsi D;
vi Bit;

void bfs(){
	vi juli(N+1, -1);
	D.assign(N+1, si());

	vi q(N+2, 0);
	auto head = q.begin();
	auto tail = q.begin();

    juli[*tail++ = 1] = 0;
	D[1].insert(Bit[1]);

	while(head < tail){
		auto h = *head++;
		for(auto v : G[h]){
			if(-1 == juli[v]){
				juli[*tail++ = v] = juli[h] + 1;
			}
            if(juli[h] + 1 == juli[v]){
				for(int i : D[h]){
					D[v].insert(i | Bit[v]);
				}
			}			
		}
	}
	return;
}

int dp(){
    vvi d(YouCar.size(), vi(1<<K, 0));
    d[0][0] = 1;
	for(int i=1;i<YouCar.size();++i){
		for(int j : D[YouCar[i]]){
			for(int k=0;k<(1<<K);++k){
				if(0 == d[i-1][k]) continue;
				d[i][k | j] = 1; 
			}
		}
	}

    int ans = 0;
	for(int i=0;i<(1<<K);++i){
        if(d[F-K][i] == 0) continue;
		int tmp = 0;
		for(int j=0;j<K;++j){
			if(i & (1<<j)) ++tmp;
		}
		ans = max(ans, tmp);
	}
	return K - ans;
}

int proc(){
    bfs();
	auto ans = dp();	
	return ans;
}

void read(){
    G.assign(1 + (N=getInt()), vi());
	M = getInt();
	for(int a,b,i=0;i<M;++i){
        a = getInt();
		b = getInt();
		G[a].push_back(b);
		G[b].push_back(a);
	}

	vi tmp(F=getInt(), 0);
	for(int & i : tmp) i = getInt();
 
    si s;
	K = getInt();
	for(int i=0;i<K;++i) s.insert(getInt() - 1);

    Bit.assign(N+1, 0);
    MeiCar.clear(); MeiCar.reserve(K);
	YouCar.clear(); YouCar.reserve(F - K + 1); YouCar.push_back(0);
	for(int i=0;i<F;++i){
		if(s.count(i)){
            MeiCar.push_back(tmp[i]);
			Bit[tmp[i]] |= (1 << (MeiCar.size() - 1));
		}else{
            YouCar.push_back(tmp[i]);
		}
	}

}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int nofkase = getInt();
	for(int kase=1;kase<=nofkase;++kase){
        read();
		printf("%d\n", proc());
	}
    return 0;
}
