/**
 * ���ɶ�ʯ�ӣ�ÿ��ʯ������ai������һ������bi��
 * ÿһ��ֻ��ȡbi^k������kΪ�Ǹ�����������ȡ��Ϊ���������ֵ�ʤ��
 * ��Ȼ��SG������������ai��bi���ܴ�Ҫ����ҹ���
 * �����biΪ����ʱ��sg����Ϊ01��ѭ��
 * biΪż��ʱ��sg������bi+1����Ϊѭ���ڣ����һ������2��ǰ����01��ѭ��
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
int const SIZE = 37;
#else
int const SIZE = 1E5+10;
#endif

typedef long long llt;
int N;
int A[SIZE], B[SIZE];

int f(llt a, llt b){
    if(b&1){
		return a&1 ? 1 : 0;
	}
	llt left = a % (b + 1);
	if(left == b) return 2;
	return left & 1 ? 1 : 0;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    N = getInt();
	int ans = 0;
	for(int i=0;i<N;++i){
		A[i] = getInt(); B[i] = getInt();
		ans ^= f(A[i], B[i]);
	}	
	puts(ans?"Alice":"Bob");
    return 0;
}
