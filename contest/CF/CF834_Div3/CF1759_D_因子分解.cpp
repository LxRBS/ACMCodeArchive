/**
 * 给定N和M，在[1, M]中找到出一个数K，使得N*K满足：
 * 1 末尾的0的数量最多
 * 2 如果均最多，则输出最大的
 * 0的数量只与2和5有关，首先将N本身的0去掉，然后再找出5的数量或者2的数量
 * 再对M做同样的处理，看一下最多能匹配几个即可
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
int const SIZE = 13;
#else
int const SIZE = 1E2+13;
#endif

using llt = long long;

llt N, M;
llt T;

llt proc5(){
    assert(N % 2);
    int k = 0;
    llt twos = 1;
    int nn = N;
    while(nn % 5 == 0){
        nn /= 5, ++k;
        twos *= 2;
        if(twos > M){
            twos /= 2; --k; break;
        }
    } 
    while(1){
        twos *= 10;
        if(twos > M){
            twos /= 10; break;
        }
    }
    if(1 == twos) return N * T * M;
    return M / twos * twos * N * T;
}

llt proc2(){
    assert(N % 5);
    llt five = 1;
    int nn = N;
    while(nn % 2 == 0){
        nn /= 2; five *= 5;
        if(five > M){
            five /= 5; break;
        }
    }
    while(1){
        five *= 10;
        if(five > M){
            five /= 10; break;
        }
    }
    if(1 == five) return N * T * M;
    return M / five * five * N * T;
}

llt procNone(){
    assert(N % 5 && N % 2);
    llt ten = 1;
    while(1){
        ten *= 10;
        if(ten > M) {ten /= 10; break;}
    }
    if(1 == ten) return N * T * M;
    return M / ten * ten * N * T;
}

llt proc(){
    T = 1;
    while(N % 10 == 0) N /= 10, T *= 10;
    if(N % 5 == 0) return proc5();
    if(N % 2 == 0) return proc2();
    return procNone();
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r" ,stdin);
#endif
    int nofkase = getInt();
    while(nofkase--){
        N = getInt();
        M = getInt();
        printf("%lld\n", proc());
    }    
    return 0;
}