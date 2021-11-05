/**
 * ��������ż��X��Y����n����n%X == Y%n
 * ���X==Y��ֱ��ȡX����
 * ���X>Y��ȡX+Y����
 * �ؼ���X<Y���׵ô�ʱ����X<n<Y��
 * ���ֻ�蹹������ΪY-n���ɣ�����һ������n-kx
 * ����2n = Y + kx
 * ͬʱ��xȡģ���õ�r = (Y%X) / 2 
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
int const SIZE = 1000010;
#endif

#define fi first
#define se second

typedef long long llt;

llt X, Y;

llt proc(){
	if(X==Y) return X;
	if(Y<X) return X + Y;
	if(Y%X==0) return X;
	llt b = Y % X;
	b /= 2;    
	return Y - b;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int nofkase = getInt();
	while(nofkase--){
		X = getInt();
		Y = getInt();
		printf("%lld\n", proc());
#ifndef ONLINE_JUDGE
        printf("%lld %lld\n", proc()%X, Y%proc());
#endif
	}
	return 0;
}