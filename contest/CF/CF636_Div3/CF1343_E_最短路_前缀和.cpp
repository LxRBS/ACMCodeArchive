/**
 * 给定n个点m条边的无向图，再给定顶点a、b、c，要求从a到b再从b到c
 * 再给定m个权值，要求给m条边赋权，问如何赋权能使上述路径权值和最小
 * 考虑第四方节点x，如果x到a、b、c的路径不重合，则直接求出最短路径，
 * 再求出前若干个最小权值即可，用前缀和可以解决
 * 但是如果路径有重复，很难办。题解用小于等于m做判断是有问题的
 * 以下数据很多标程都过不了。当然也没测几个。我自己这个也过不了
 * 莫非看错题了
 * 1
 * 3 2 1 2 3
 * 10 20 30
 * 1 2 
 * 1 3
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
int const SIZE = 22;
#else
int const SIZE = 200100;
#endif

typedef long long llt;
int const INF = 0x3FFFFFFF;

int N, M;
int A, B, C;

llt W[SIZE];
vector<int> G[SIZE];
bool Flag[SIZE];

int DA[SIZE], DB[SIZE], DC[SIZE];

void spfa(int s, int d[]){
	fill(d, d+N+1, INF);
	fill(Flag, Flag+N+1, false);
	queue<int> q;
	int tmp = -1;
	q.push(s);
	Flag[s] = true;
	while(!q.empty()){
		++tmp;
        int sz = q.size();
		while(sz--){
			int h = q.front(); q.pop();
            d[h] = tmp;
			for(auto v: G[h])if(!Flag[v]){Flag[v]=true;q.push(v);}
		}
	}
}

llt Sum[SIZE];

llt proc(){
    sort(W+1, W+M+1);
	for(int i=1;i<=M;++i) Sum[i] = Sum[i-1] + W[i];

	spfa(A, DA); spfa(B, DB); spfa(C, DC);
	
	llt ans = 0x3FFFFFFFFFFFFFFF;
	for(int tmp, i=1;i<=N;++i){
		tmp = DA[i]+DB[i]+DC[i];
		if(tmp <= M){
			ans = min(ans, Sum[tmp] + Sum[DB[i]]);
		}
        
	}
    return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
#endif
    int nofkase = getInt();
    while(nofkase--){
        N = getInt(); M = getInt();
        A = getInt(); B = getInt(); C = getInt();
		for(int i=1;i<=N;++i) G[i].clear();
        for(int i=1;i<=M;++i) W[i] = getInt();
		for(int u,v,i=1;i<=M;++i){
			u = getInt(); v = getInt();
			G[u].push_back(v);
			G[v].push_back(u);
		}
		printf("%lld\n", proc());
	}
    return 0;
}

