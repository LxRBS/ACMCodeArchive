/**
 * ����һ�����飬����һ�ֲ�����ѡ��1<=x<y<z<=N
 * ��A[x]�滻ΪA[y]-A[z]
 * ���ܷ񾭹�������N�β����������Ϊ���ϸ�����Ҫ�󷽰�
 * �������У������Ƿ�����Ȼ������A[N-1]��A[N]�Ĺ�ϵ
 * Ȼ���ǣ�����A[N-2] > A[N-1]����ôΨһ�Ļ��������A[N-2]=A[N-1]-A[N]����ʱҪ��A[N]�ǷǸ�����
 * ��֮�����A[N]�Ǹ�����Ҫ��������У���ֻ��A[N-2]�����������ģ���������Ѿ����й���
 * ���ԣ�A[N]���������п��н⡣��ʱ���Թ���һ���⣬��Ai=A[i+1]-A[N]����
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
int const SIZE = 200110;
#endif

typedef long long llt;

int N;
llt A[SIZE];

void proc(){
	if(A[N-2] > A[N-1]){
		return (void)puts("-1");
	}
	if(is_sorted(A, A+N)){
		return (void)puts("0");
	}

    if(A[N-1] < 0){
		return (void)puts("-1");
	}

	printf("%d\n", N-2);
	for(int i=N-3;i>=0;--i){
		printf("%d %d %d\n", i+1, i+1+1, N);
	}
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    int nofkase = getInt();
	while(nofkase--){
        N = getInt();
		for(int i=0;i<N;++i)A[i]=getInt();
        proc();
	}
	
    return 0;
}
