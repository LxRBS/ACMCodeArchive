/**
 * 给定一个树，每次操作删除当前树的所有叶子
 * 注意特殊情况
 * 问K次操作后剩下几个节点
 * 求一个层次图即可，叶子为1层，其他节点的层次是最大子节点加1
 * 用队列即可
 * 最后看层次大于K的点数即可
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

typedef vector<int> vi;

#ifndef ONLINE_JUDGE
int const SIZE = 15;
#else
int const SIZE = 500050;
#endif

int N, K;
vi G[SIZE];
int Deg[SIZE], Layer[SIZE];

int proc(){
	queue<int> q;
	for(int i=1;i<=N;++i)if(1==Deg[i])q.push(i),Layer[i]=1;
	while(!q.empty()){
        int h = q.front(); q.pop();
		for(auto v: G[h]){
            if(1==Deg[v]) continue;
			if(1 == --Deg[v]){
				q.push(v);
				Layer[v] = Layer[h] + 1;
			}
		}
	}
	int ans = 0;
	for(int i=1;i<=N;++i)if(Layer[i]>K)++ans;
	return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int nofkase = getInt();
	while(nofkase--){
		for(int i=1,n=N=getInt();i<=n;++i) G[i].clear(), Deg[i]=Layer[i]=0;
		K = getInt();
		for(int a, b, i=1;i<N;++i){
            a = getInt();
			b = getInt();
			G[a].push_back(b);
			G[b].push_back(a);
			++Deg[a];
			++Deg[b];
		}
		printf("%d\n", proc());
	}    
    return 0;
}