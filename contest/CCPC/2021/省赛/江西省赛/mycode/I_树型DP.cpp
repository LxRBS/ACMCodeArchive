/**
 * N���ڵ������ÿ���ڵ���һ��ai����ʾ�ýڵ������aiʱ�������ҵ
 * ����һ�ַ������������ҵ��i����ȥj����j�����ҵ�󣬿��Գ�j����ҵ�����أ�i���뷵�ؼҲ���Ϊ��ҵ���
 * ��ʱi�����ҵ��ʱ�����j��ʱ�����i��j���ؼҵ�ʱ��
 * �����������
 * 1. �޸�i��ai
 * 2. �޸�i��j�ҵľ���
 * 3. ��ÿ�������������ҵ��ʱ�䣬����3����������200��
 * N��1E5 
 * ��������DP����DiΪ���ֻ���Ƕ��Ӻ�������������ʱ�䣬��Ȼ
 * Di = min(Ai, min{Dj+Wij})������j��i�Ķ���
 * ����ֻ��Ҫ���Ǹ��ڵ㼴�ɡ������ǿ�����Ҫ�����ڶ�СDP����Ϊ���Ӻ͸��ײ��ܻ������
 * ��������ʵ����Ҫ������p��ĳ������i������Dp�����ɹ��򣬱�Ȼ��
 * Dp >= Di + Wip
 * ��������������� Dp + Wip > Di�����Կ϶�p�Ĵ𰸲����ɶ���i����ģ����ǿ��Է�������p����ֵ������i
 * ���ֻ��Ҫ��1Ϊ���������飬����������DP���ɡ�
 * ��һ�����꣬D1�϶�����ȷ�𰸣�����ֱ���ѵڶ�����¼��ɡ�
 * ���˵��������ʵ���ܻ�����
 * CF�Ͽ���ֱ�ӹ���ţ���Ͽ���һ�㣬��ʼ��ʱ��Ҫʹ��copy�������������ֵ��
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
int const SIZE = 11;
#else
int const SIZE = 1E5+7;
#endif

using llt = long long;
using pii = pair<int, int>;
using vpii = vector<pii>;


vpii G[SIZE];
int N, Q;
int A[SIZE];
llt W[SIZE];

llt B[SIZE];

/// ��ʱB������ǳ�������ҵ����Сֵ
void dfs(int u, int p){
    // B[u] = A[u]; /// ţ�����������ʼ���ͻ�T
    for(const pii & e: G[u]){
        if(e.first == p) continue;
        
        dfs(e.first, u);

        B[u] = min(B[u], B[e.first] + W[e.second]);
    }
}

/// B�����
void dfs2(int u, int p){
    for(const pii & e: G[u]){
        if(e.first == p) continue;
        /// ˵��u�Ǵӱ�ĵط�Ū������Сֵ
        B[e.first] = min(B[e.first], B[u] + W[e.second]);
        dfs2(e.first, u);
    }
}

llt proc(){
    copy(A+1, A+N+1, B+1);
    dfs(1, 0);
    dfs2(1, 0);
    llt ans = 0;
    for(int i=1;i<=N;++i) ans ^= B[i];
    return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    N = getInt(); Q = getInt();
    for(int i=1;i<=N;++i) A[i] = getInt();
    for(int a,b,w,i=1;i<N;++i){
        a = getInt(); b = getInt(); W[i] = getInt();
        G[a].emplace_back(b, i);
        G[b].emplace_back(a, i);
    } 

    for(int op, q=1;q<=Q;++q){
        if(1 == (op=getInt())){
            int i = getInt();
            A[i] = getInt();
        }else if(2 == op){
            int i = getInt();
            W[i] = getInt();
        }else{
            cout << proc() << endl;
        }
    }
    return 0;
}