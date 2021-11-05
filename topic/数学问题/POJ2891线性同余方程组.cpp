//线性同余方程组，模不互质，要迭代求解
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

//x = ri ( mod ai )
int_t proc(int k){
    int_t r = 0, a = 1;
    int_t ri,ai,x,y;

    while(k--){
        scanf("%I64d%I64d",&ai,&ri);
        if ( -1LL == r ) continue;
         
        int_t gcd = exEuclid(a,ai,x,y);
        int_t d = ri - r;
        if ( d % gcd ){
            r = -1LL;
            continue;
        }

		int_t t = ai / gcd;
        //x = ( x * ( (ri-r)/gcd ) % t + t ) % t;
        x = d / gcd * x;
        //*
		x %= t;
        if ( x < 0LL ) x += t;
        //*/
        r = r + x * a;
        a = a / gcd * ai;
    }
    return r;
}
int main()
{
    int k;
    while(EOF!=scanf("%d",&k)){
        printf("%I64d\n",proc(k));
    }
    return 0;
}
