/**
 * ����һ��������ÿ���ڵ�һ�Ա��[a, b]��
 * ��������ڵ��Ǹ��ӹ�ϵ�������ǰ�����ϵ
 * ��������ڵ㲻�Ǹ��ӹ�ϵ�����ŵĽ���Ϊ�ռ�
 * ���������������£�Ҫ����ֵ��max��С
 * dfs��������Ȼ�������������������������Ǳ��ֵ�����Ը�С��
 * ÿ����Ҷ���Է���[1, 1]��[n, n]��n����Ҷ������
 * Ȼ��ÿ���ڵ㻹��Ҫ����[min, max]���ɣ����Է�������������������
*/
#include <bits/stdc++.h>
using namespace std;

char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000-1,stdin),__abc147==__xyz258) ? EOF : *__abc147++)

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
int const SIZE = 17;
#else
int const SIZE = 200010;
#endif

int N;
vector<int> G[SIZE];
pair<int,int> A[SIZE] = {{0, 0}};
int TimeStamp = 0;

void dfs(int u,int p){
	bool b = false;
	for(int v: G[u]){
		if(v == p) continue;
		dfs(v, u);
		b = true;
		A[u].first = min(A[u].first, A[v].first);
		A[u].second = max(A[u].second, A[v].second);
	}
	if(b){
        
	}else{
		A[u].first = A[u].second = ++TimeStamp;
	}
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    N = getInt();
	for(int a,b,i=1;i<N;++i){
		a = getInt();
		b = getInt();
		G[a].push_back(b);
		G[b].push_back(a);
		A[i].first = N+N;
	}
	A[N].first = N + N;
	dfs(1, 0);
	for(int i=1;i<=N;++i){
		printf("%d %d\n", A[i].first, A[i].second);
	}
    return 0;
}
