/**
   给定a和p，构造序列a*i%p,其中i=1,2,3,...,p-1
   问该序列的逆序对的数量的奇偶性
   发现奇偶性与勒让德符号一一对应
   当p是奇素数时，
   Legendre(a/p) = a^((p-1)/2)%p
   计算一个快速幂或者计算勒让德符号本身即可
*/
#include <bits/stdc++.h>
using namespace std;

char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)

typedef long long llt;
llt getULL(){
	char ch = __hv007();
	while( ch < '0' || ch > '9' ) ch = __hv007();

	llt ret = (llt)(ch-'0');
	while( '0' <= ( ch = __hv007() ) && ch <= '9' ) ret = (ret<<1) + (ret<<3) + (llt)(ch-'0');
	return ret;
}

/// 勒让德符号，保证a、p互质
int Legendre(llt a, llt p){
    /// 如果a是偶数，分解出所有2的因子
    if(0==a%2){
        int k = 0;
        while(0==a%2) a>>=1, ++k;
        return 0==k%2||1==p%8||7==p%8
             ? Legendre(a, p)
             : -Legendre(a, p);
    }
    /// 如果p是偶数
    if(0==p%2){
        while(0==p%2) p>>=1;
        return Legendre(a, p);
    }
    /// a、p均是奇数
    if(1==a) return 1;
    if(p-1==a) return 1==p%4?1:-1;
    /// 取模
    if(a>p) return Legendre(a%p, p);
    /// 翻转
    return 3==a%4&&3==p%4 ? -Legendre(p, a) : Legendre(p, a);
}

int main(){
    int nofkase = getULL();
    while(nofkase--){
        llt a = getULL();
        llt p = getULL();
        puts(1==Legendre(a,p)?"0":"1");
    }
    return 0;
}
