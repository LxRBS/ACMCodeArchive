/**
 * 300���ڵ������ͼ����Ϊ��ͨ�ڵ�ͺ�����վ������ʱ�̱�֤���κ������ʱ������GAP
 * �����ڵ�0s��Ϊ�������⣬���ڵ�GAP�����߸���ǰ�����������һ��
 * ��˼���Ǵ�ʱ����λ�ڼ��վ�ڵ㡣
 * �����ߵĳ��ȣ����ܹ��Ϸ����߱����нڵ����С�����ٶ��Ƕ���
 * ��Ȼ�����ö��ֹ�����ܣ���ʵ���Ͽ���ֱ����⣬ֻ�������ؼ�·������
 * ������ȻҪ��һ��Floyd��������ͨ�ڵ㣬��ؼ�·�����Ǿ�������̵ļ��վ�ľ��룬�ٳ���2
 * �ٿ��Ǽ��վ֮�䣬�ؼ�·�������Լ��վ��MST�ϵ��·����
 * ���йؼ�·��������Ǹ�������ͼ�Ĺؼ�·����ֻ����GAPʱ���������꼴�� 
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