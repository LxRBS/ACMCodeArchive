/**
 * 给定数组A，长度为N，N在1E5，规定如下操作：
 * 假设有一个数，起始为D，依次经过每一个Ai，有2种运算：
 * 1 D = D + Ai
 * 2 D = D ^ Ai
 * 经过N次操作后，得到一个结果
 * 再给定X和Y，已知X或者X+3按照上述规则最后有且只有一个能变成Y
 * 问，是哪一个
 * 考虑+3会导致的不同，发现能够导致奇偶的变化，也就是说X和X+3必然是异奇偶的
 * 再考虑加法和异或操作，发现任意Ai，无论如何操作，X和X+3会保持奇偶互异
 * 因此最后检查一下Y的奇偶性即可
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