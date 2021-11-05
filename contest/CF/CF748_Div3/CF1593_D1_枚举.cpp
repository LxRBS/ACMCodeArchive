/**
 * ����NԪ�ص�����A����ѡ��һ��K��ÿ��ѡ��һ��Ai��Ai-=K
 * ���Ҫ��ʹ�����е�Ai��ȣ������������ޡ�
 * �����Ŀ��ܵ�K�Ƕ��٣����K��������������-1
 * 
 * ����ֻ�г�ʼֵȫ��Ȳ����-1.
 * �����ս��Ϊd����Ai-miK=d, Aj-mjK=d
 * ���� Ai-Aj = (mi-mj)K
 * ˵��K��Ȼ�Ƕ���֮���Լ��
 * ����K���������֮���gcd
 *  * N��40������ö�ټ���
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

#ifndef ONLINE_JUDGE
int const SIZE = 13;
#else
int const SIZE = 50;
#endif

llt gcd(llt a,llt b){
    while( b ){
        llt r = b;
        b = a % b;
        a = r;
    }
    return a;
}

int N;
int A[SIZE];

int proc(){
    sort(A+1, A+N+1);
	N = unique(A+1, A+N+1) - A - 1;

	if(1 == N) return -1;

	int ans = A[2] - A[1];
	for(int i=1;i<N;++i)for(int j=i+1;j<=N;++j){
        ans = gcd(ans, A[j] - A[i]);
	}
	return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int nofkase = getInt();
	while(nofkase--){
		N = getInt();
		for(int i=1;i<=N;++i) A[i] = getInt();
		printf("%d\n", proc());
	}
    return 0;
}