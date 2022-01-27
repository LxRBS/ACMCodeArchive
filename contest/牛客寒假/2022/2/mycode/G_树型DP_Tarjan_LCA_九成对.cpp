/**
 * ��һ��������������Ȩֵ������a��b���ڣ����a�ߵ�b��
 * ��aȨֵ����b�������軮�֣�������Ҫ����W[b]-W[a]
 * ����Q��ѯ�ʣ�ÿ���ʴ�u��vҪ���Ѷ���
 * �������⣬��ʼ����W[u]�Ļ���
 * ��X[i]Ϊ�Ӹ���i��Ļ��֣���Y[i]Ϊ��i�����Ļ���
 * ����DP�������
 * ���Զ�ÿ��ѯ�ʣ�ֻ���ҳ�u��v��LCA����
 * Tarjan�㷨������LCA���ش�����
 * ����ֻ��90%����ȷ�ʣ���֪���������
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

typedef long long llt;
typedef vector<int> IntVecTy;
typedef pair<int, int> PiiTy;

struct pair_hash{
	inline size_t operator()(const PiiTy&p)const{
		return p.first * 1331 + p.second;
	}	
};

#ifndef ONLINE_JUDGE
int const SIZE = 11;
#else
int const SIZE = 1000001;
#endif

typedef IntVecTy I2VecMapTy[SIZE];
typedef unordered_map<PiiTy, int, pair_hash> MapTy;

IntVecTy G[SIZE];

int N, M;
llt A[SIZE];
llt X[SIZE]; 
llt Y[SIZE];

I2VecMapTy Qs, IQ;
MapTy Q2I;
llt Ans[SIZE];

void dfs(int u, int parent){
    for(int v: G[u]){
		if(v == parent) continue;
		if(A[v] <= A[u]){
			X[v] = X[u];
			Y[v] = Y[u] + A[u] - A[v];
		}else{
			X[v] = X[u] + A[v] - A[u];
			Y[v] = Y[u];
		}
		dfs(v, u);
	}     
}

int Father[SIZE];
int find(int x){return x==Father[x]?x:Father[x]=find(Father[x]);}

bool Flag[SIZE];
void Tarjan(int u, int parent){
    Flag[Father[u] = u] = true;

	for(int v: G[u]){
		if(v == parent) continue;
		Tarjan(v, u);
		Father[v] = u;
	}

    for(int v: Qs[u]){
		if(!Flag[v]) continue;

        int idx = Q2I[{u, v}];
// 		if(Ans[idx] != -1) continue;

		int r = find(v); // r is lca of u and v.		
		Ans[idx] = A[u] + Y[u] - Y[r] + X[v] - X[r];
	}

	for(int v: IQ[u]){
		if(!Flag[v]) continue;

        int idx = Q2I[{v, u}];
// 		if(Ans[idx] != -1) continue;
		
		int r = find(v);
		Ans[idx] = A[v] + Y[v] - Y[r] + X[u] - X[r];
	}
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    N = getInt();
	M = getInt();
	for(int i=1;i<=N;++i) A[i] = getInt();
	for(int a,b,i=1;i<N;++i){
		a = getInt();
		b = getInt();
		G[a].push_back(b);
		G[b].push_back(a);
	}
	X[1] = Y[1] = 0;
	dfs(1, 0);
	for(int a,b,i=1;i<=M;++i){
        a = getInt();
		b = getInt();
		Qs[a].push_back(b);
		IQ[b].push_back(a);
		Q2I[{a, b}] = i;
		Ans[i] = -1;
	}
	Tarjan(1, 0);
	for(int i=1;i<=M;++i){
		printf("%lld\n", Ans[i]);
	}
    return 0;
}
