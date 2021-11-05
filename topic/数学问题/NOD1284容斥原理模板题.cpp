//求不是2/3/5/7倍数的数的个数，容斥原理，模板题
#include <stdio.h>
#include <algorithm>
using namespace std;
typedef unsigned long long ull;

//容斥原理，求2/3/5/7至少其一倍数的数的个数
ull A[] = {2,3,5,7};
ull f(ull n){
    ull ret = 0ULL;
    for(int i=1,m=1<<4;i<m;++i){
        ull t = n;
        int k = 0;
        for(int j=0;j<4;++j){
            if ( (1<<j) & i ){
                t /= A[j];
                ++k;
            }
        }
        ret += k&1?t:-t;
    }
    return ret;
}
int main(){
    ull n;
    scanf("%llu",&n);
    printf("%llu\n",n-f(n));
    return 0;
}
