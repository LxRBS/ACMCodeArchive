/**
 * N��ʯ�ӣ����������²�����ÿ��ѡ3�ѣ����м��Ƕ�����������һ�߷�һ����
 * �ʣ�Ҫ������ʯ�Ӷ����ڵ�1�Ѻ͵�N�ѣ�������Ҫ���β����������������-1��
 * ����1��N��Ȼ��Ӱ��𰸡���Σ��������ż������Ȼ���У���һ�β������2������2����
 * ����ĳ��Ϊ��������Ȼ������߻����ұ߱�Ȼ�жѣ�������ǿ���ȡ��
 * ȡ��2���Ժ�1������������ż������1��ֱ���ӵ��յ㼴��
 * �������һ�߻��������ѣ�Ҳû�й�ϵ����Ϊ��֮��ÿһ�������ѣ�Ҫ����һ��ʯ�������ż��
 * ������е�����ʯ��Ҫ����һ��������ʣ�µĶ��ǳɶԵ�ʯ�ӣ�ÿ�Ի���һ����
 * ע������ȫ1�������
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
int const SIZE = 33;
#else
int const SIZE = 100100;
#endif

int N;
int A[SIZE];

typedef long long llt;


llt proc(){
    if(3 == N){
		if(A[1]&1) return -1;
		return A[1]/2;
	}

	if([&]()->bool{
		for(int i=1;i<N-1;++i){
			if(1 == A[i]) continue;
			return false;
		}
		return true;
	}()) return -1;

    int cnt = 0;
	llt ans = 0;
	for(int i=1;i<N-1;++i){
		if(A[i]&1) ++cnt;
		ans += A[i];
	}
	return (ans - cnt) / 2 + cnt;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    int nofkase = getInt();
	while(nofkase--){
        N = getInt();
		for(int i=0;i<N;++i) A[i] = getInt();
		printf("%lld\n", proc());
	}
    return 0;
}