/*
  已知
  x + y = a
  lcm(x,y) = b
  求 x、y

  设 g = gcd(x,y) 则 x = ig, y = jg，且i、j互质
  则 ig + jg = a, ig * jg / g = ijg = b
  所以 g = gcd(a,b)
  原方程转化为
  x + y = a
  x * y = b * gcd(a,b)
*/
#include <cstdio>
#include <cmath>
typedef long long int int_t;
int_t gcd(int_t a,int_t b){
    while( b ){
        int_t r = b;
        b = a % b;
        a = r;
    }
    return a;
}

int main(){
    int a,b;
    while( EOF != scanf("%d%d",&a,&b) ){
        int_t c = gcd(a,b) * b;
        int_t delta = a * a - 4LL * c;
        if ( delta < 0 ){
            puts("No Solution");
            continue;
        }

        double sqrtd = sqrt((double)delta);
        if ( (int)(sqrtd+0.5) != sqrtd ){
            puts("No Solution");
            continue;
        }

        printf("%d %d\n",(int)((a-sqrtd)/2.0+0.5),(int)((a+sqrtd)/2.0+0.5));
    }
    return 0;
}

