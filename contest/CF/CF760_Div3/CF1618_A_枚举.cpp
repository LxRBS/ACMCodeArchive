/**
 * 给3个数，记作A数组，互相求和得到7个数，记作B数组
 * 现在给定B（升序），求A，任意满足均可
 * 首先，B0肯定是A之一，然后在剩下的6个中间选2个看是否满足条件即可
 * 枚举
*/
#include <bits/stdc++.h>
using namespace std;

char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)

int getUnsigned(){
	char ch = __hv007();
	while( ch < '0' || ch > '9' ) ch = __hv007();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = __hv007() ) && ch <= '9' ) ret = (ret<<1) + (ret<<3) + (int)(ch-'0');
	return ret;
}

typedef long long llt;

llt A[11], B[11];

bool check(const string&s){
    A[1] = A[2] = -1;
    
    map<llt, int> m;
    for(int i=1;i<7;++i) ++m[B[i]];

    for(int i=0;i<6;++i){
        if('1' == s[i]){
            if(-1 == A[1]){
                --m[A[1] = B[1+i]];
            }else if(-1 == A[2]){
                --m[A[2] = B[1+i]];
            }else{
                throw runtime_error("YYY");
            }
        }
    }
    
    --m[A[0]+A[1]];
    --m[A[0]+A[2]];
    --m[A[1]+A[2]];
    --m[A[0]+A[1]+A[2]];

    for(auto pp: m){
        if(pp.second) return false;
    }

    printf("%lld %lld %lld\n", A[0], A[1], A[2]);
    return true;
}

void proc(){
    A[0] = B[0];
    string s = "000011";
    do{
        if(check(s)) return;
    }while(next_permutation(s.begin(), s.end()));
    throw runtime_error("XX");
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
#endif
    int nofkase = getUnsigned();
    while(nofkase--){
        for(int i=0;i<7;++i) B[i] = getUnsigned();
        proc();
    }
    return 0;
}

