/**
 * ��������A�����ܷ񾭹�����β�����ʹ������Ai�����
 * ����ֻ��һ�֣���ѡx>=2��������Ai%=x
 * ���ȹ۲죬���ͬʱ��0��1����϶���No��
 * ���û��1������ԴӴ�Сѡ��x�����������ÿ��Ai�����0
 * �����1����ֻ�ܽ�����Ai�����1��������Ҫѡ��Ai-1��Ϊx��
 * �������ʱ����Aj==Ai-1����Aj��Ϊ0���ͻ�ʧ��
 * �����ж�һ�¼���
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
int const SIZE = 10;
#else
int const SIZE = 1E5+5;
#endif

typedef long long llt;
typedef pair<int, int> pii;

int N;
llt A[SIZE];

bool proc(){
	sort(A, A+N);
    N = unique(A, A+N) - A;
	if(1 == N) return true;
	if(0 == A[0]){
		if(1 == A[1]) return false;
		return true;
	}
	if(1 != A[0]) return true;
	for(int i=1;i<N;++i){
		if(1 == A[i] - A[i-1]) return false;
	}
	return true;
}

int main() {    
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    int nofkase = getInt();
	while(nofkase--){
        N = getInt();
		for(int i=0;i<N;++i) A[i] = getInt();
		puts(proc()?"YES":"NO");
	}
    return 0;
}
