//���ݷ����к͹�ʽ
// 1/a = ( 1/b + 1/c ) / ( 1 - 1/(bc) )
//����  c = ( ab + 1 ) / ( b - a )
//����b��cһ������a
//��b=a+x,c=a+y
//�� xy = a*a+1
//�� x+y ����Сֵ 

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
