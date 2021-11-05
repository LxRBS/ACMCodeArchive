//同余方程
#include <cstdio>
using namespace std;
typedef long long int_t;

//非递归的扩展欧几里德算法
//返回a、b的gcd，同时x、y满足ax+by=gcd
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

//x0+mt - (y0+nt) == Lk
//mt - nt = Lk +y0 - x0
// (m - n)t - Lk = y0 - x0
int main()
{
    int_t x0,y0,m,n,L;
    while (EOF!=scanf("%I64d%I64d%I64d%I64d%I64d",&x0,&y0,&m,&n,&L)){
        int_t a = m - n;
        int_t b = L;
        int_t d = y0 - x0;
        int_t x,y;
        int_t gcd = exEuclid(a,b,x,y);
        if ( d % gcd ){
            printf("Impossible\n");
            continue;
        }

        int_t t = d / gcd * x;
        t %= b;
        if ( t < 0LL ) t += b;
        printf("%I64d\n",t);
    }
    return 0;
}
