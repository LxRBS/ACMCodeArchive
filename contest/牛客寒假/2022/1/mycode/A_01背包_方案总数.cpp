/**
 * ��һ����λ���������λ�����������ӣ�ֱ����Ϊ��λ�����ý����Ϊԭ���ĸ�
 * ����N��������һ���ж�����ѡ��ʹ��ѡ����֮�͵ĸ�Ϊk������kΪ1~9
 * �����������õ��ľ��Ƕ�9ȡģ�����ԭ�����Ϊ������ѡ��ʹ�ú�ģ9Ϊk
 * DviΪǰi����ģΪv�ķ�������������
 * Dvi = D[v][i-1] + D[v-Ai+9][i-1]
 * ����i������ѡ����ѡ
 * ע���ʼ������
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
int const SIZE = 100055;
#endif

typedef long long llt;
llt const MOD = 998244353;

int N;
llt A[SIZE];
llt D[10][SIZE];

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    N = getInt();
	for(int i=1;i<=N;++i)A[i] = getInt() % 9;
	D[0][0] = 1;
    for(int i=1;i<=N;++i){
		D[1][i] = (D[1][i-1] + D[(1-A[i]+9)%9][i-1])%MOD;
		D[2][i] = (D[2][i-1] + D[(2-A[i]+9)%9][i-1])%MOD;
		D[3][i] = (D[3][i-1] + D[(3-A[i]+9)%9][i-1])%MOD;
		D[4][i] = (D[4][i-1] + D[(4-A[i]+9)%9][i-1])%MOD;
		D[5][i] = (D[5][i-1] + D[(5-A[i]+9)%9][i-1])%MOD;
		D[6][i] = (D[6][i-1] + D[(6-A[i]+9)%9][i-1])%MOD;
		D[7][i] = (D[7][i-1] + D[(7-A[i]+9)%9][i-1])%MOD;
		D[8][i] = (D[8][i-1] + D[(8-A[i]+9)%9][i-1])%MOD;
		D[0][i] = (D[0][i-1] + D[(0-A[i]+9)%9][i-1])%MOD;		
	}
	for(int i=1;i<=8;++i)printf("%lld ", D[i][N]);
	printf("%lld\n", D[0][N]-1);
    return 0;
}
