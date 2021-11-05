//根据反正切和公式
// 1/a = ( 1/b + 1/c ) / ( 1 - 1/(bc) )
//所以  c = ( ab + 1 ) / ( b - a )
//所以b、c一定大于a
//令b=a+x,c=a+y
//有 xy = a*a+1
//求 x+y 的最小值 

#include <cstdio>
#include <cmath>
typedef unsigned int uint;
int main(){
    uint a;
    while(EOF!=scanf("%u",&a)){
        uint r;
        for(uint x=a;x>=1;--x){
            if ( 0U == (a*a+1U)%x ){
                uint y = (a*a+1U)/x;
                r = a + a + x + y;
                break;     
            }        
        } 
        printf("%u\n",r);                        
    }
    return 0;    
}  
