/**
 * ��������A������ΪN��N��1E5���涨���²�����
 * ������һ��������ʼΪD�����ξ���ÿһ��Ai����2�����㣺
 * 1 D = D + Ai
 * 2 D = D ^ Ai
 * ����N�β����󣬵õ�һ�����
 * �ٸ���X��Y����֪X����X+3�������������������ֻ��һ���ܱ��Y
 * �ʣ�����һ��
 * ����+3�ᵼ�µĲ�ͬ�������ܹ�������ż�ı仯��Ҳ����˵X��X+3��Ȼ������ż��
 * �ٿ��Ǽӷ�������������������Ai��������β�����X��X+3�ᱣ����ż����
 * ��������һ��Y����ż�Լ���
*/
#include <bits/stdc++.h>
using namespace std;

char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)

typedef long long llt;
llt getInt(){
	int sgn = 1;
	char ch = __hv007();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = __hv007();
	if ( '-' == ch ) {sgn = 0;ch=__hv007();}

	llt ret = (llt)(ch-'0');
	while( '0' <= (ch=__hv007()) && ch <= '9' ) ret = ret * 10LL + (llt)(ch-'0');
	return sgn ? ret : -ret;
}


#ifndef ONLINE_JUDGE
int const SIZE = 11;
#else
int const SIZE = 1000055;
#endif

int N;
llt X, Y;
llt A[SIZE];

bool proc(){
	X &= 3;
	for(int i=1;i<=N;++i){
		X ^= A[i] & 3;
	}
	return (X&1) == (Y&1);
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    int nofkase = getInt();
    while(nofkase--){
        N = getInt(); X = getInt(); Y = getInt();
		for(int i=1;i<=N;++i)A[i] = getInt();
		puts(proc()?"Alice":"Bob");
    }
    return 0;
}
