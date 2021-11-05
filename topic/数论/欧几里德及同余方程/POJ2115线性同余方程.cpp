/*
     做一个for循环，循环退出条件等价于
     A + Cx = B (mod 2^k)
     则 Cx = B-A (mod M)
     Cx + My = B-A
     该方程有解的充要条件为
     gcd(C,M) = B-A

     对于扩展的欧几里德方程
     ax + by = n

     令d = gcd(a,b)
     首先解方程
     ax'+by'=d，如果x'和y'是方程的解，则
     令k=n/d，kx'和ky'就是原方程的一个解
     kx'+b/d*t和ky'-a/d*t就是原方程的解集

     一般而言我们可以求出某个满足上述通解形式的特解
     x = kx'+b/d*t
     现在要求这种通解的最小正整数解
     只要将特解x对b/d取余数即可
*/
#include <stdio.h>
#include <cmath>
#include <sstream>
#include <algorithm>
using namespace std;

typedef long long llt;
typedef llt int_t;

//The extended Euclidean algorithm implemented by iteration
//returns gcd(a,b), and x, y are satisfied with ax + by = gcd
int_t exEuclid(int_t a,int_t b,int_t&x,int_t&y){
    int_t x0 = 1, y0 = 0;
    int_t x1 = 0, y1 = 1;
    x = 0; y = 1;
    int_t r = a % b;
    int_t q = ( a - r ) / b;
    while( r ){
        x = x0 - q * x1;
        y = y0 - q * y1;
        x0 = x1; y0 = y1;
        x1 = x; y1 = y;
        a = b; b = r; r = a % b;
        q = ( a - r ) / b;
    }
    return b;
}

int main(){
    llt a,b,c,k,x,y,m,ans;
    while(scanf("%lld%lld%lld%lld",&a,&b,&c,&k),a,b,c,k){
        m = 1LL << k;
        ans = exEuclid(c,m,x,y);
        if ( (b-a) % ans ) puts("FOREVER");
        else {
            llt t = (b-a)/ans;
            x *= t;
            t = m / ans;
            x %= t;
            if ( x < 0 ) x += t;
            printf("%lld\n",x);
        }
    }
    return 0;
}
