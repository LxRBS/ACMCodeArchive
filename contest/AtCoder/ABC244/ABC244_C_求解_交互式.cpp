/**
 * ����N����2N+1��Χ������ѡ�������һ�ַ����������ֻ�ʤ
 * ����ʽ��Ŀ���������ֺ͵��Բ���
 * ����ѡ�м������Ȼ��ѡ��һ��������ѡ�ĶԳƼ���
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
int const SIZE = 45;
#else
int const SIZE = 1E5+5;
#endif

int N;

void proc(){
	printf("%d\n", N+1);fflush(stdout);	
	while(1){
        int a; scanf("%d", &a);
		if(0 == a) break;
		printf("%d\n", N+N+1+1-a);fflush(stdout);
	}
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    scanf("%d", &N);
	proc();
    return 0;
}