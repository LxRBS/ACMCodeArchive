/*
     ��һ��forѭ����ѭ���˳������ȼ���
     A + Cx = B (mod 2^k)
     �� Cx = B-A (mod M)
     Cx + My = B-A
     �÷����н�ĳ�Ҫ����Ϊ
     gcd(C,M) = B-A

     ������չ��ŷ����·���
     ax + by = n

     ��d = gcd(a,b)
     ���Ƚⷽ��
     ax'+by'=d�����x'��y'�Ƿ��̵Ľ⣬��
     ��k=n/d��kx'��ky'����ԭ���̵�һ����
     kx'+b/d*t��ky'-a/d*t����ԭ���̵Ľ⼯

     һ��������ǿ������ĳ����������ͨ����ʽ���ؽ�
     x = kx'+b/d*t
     ����Ҫ������ͨ�����С��������
     ֻҪ���ؽ�x��b/dȡ��������
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
