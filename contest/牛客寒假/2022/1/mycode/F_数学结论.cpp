/**
 * ��������A��M����A�г����ɶΣ�ʹ��ÿһ����λ�������ڵ���M
 * �������Էֳɶ��ٶ�
 * �����ۣ���������
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
int const SIZE = 1000055;
#endif

typedef long long llt;

int N, M;
int A[SIZE];

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    int nofkase = getInt();
	while(nofkase--){
		N = getInt();
		M = getInt();
		int ans = 0;
		for(int i=1;i<=N;++i)if((A[i]=getInt())>=M)++ans;
		ans = ans + ans - N;
		printf("%d\n", ans<=0?-1:ans);
	}
    return 0;
}
