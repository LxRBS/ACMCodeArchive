/**
 * ����һ�����飬�����Ϊ���ɸ��ӶΣ�
 * ÿ���Ӷε��ϸ�����������еĳ���Ϊki
 * ���Ƿ����һ�����ַ�����ʹ�����е�ki������Ϊ0
 * ���nΪż������ֱ�ӷ�Ϊn�ݣ����ɡ�
 * ���nΪ����������Ҫ�ҵ�һ������Ϊ2�Ľ����ӶΡ�
 * �������no
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
int const SIZE = 21;
#else 
int const SIZE = 100010;
#endif

#define fi first
#define se second

typedef long long llt;

int N;
int A[SIZE];

bool proc(){
	if(N%2==0) return true;

	for(int i=2;i<=N;++i){
		if(A[i-1] >= A[i]) return true;
	}
	return false;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int nofkase = getInt();
	while(nofkase--){
		N = getInt();
		for(int i=1;i<=N;++i)A[i] = getInt();
		puts(proc()?"YES":"NO");
	}
	return 0;
}