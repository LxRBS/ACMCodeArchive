/*
  给定A/B，找出最小的C，使得
  A^C & B^C 最小
  A、B对应的位都是1时才需要将C为设置为1
*/

#include <stdio.h>

int main(){
    int nofkase;
    scanf("%d",&nofkase);
    while(nofkase--){
        unsigned a,b;
        scanf("%u%u",&a,&b);

        unsigned int ans = 0;
        for(int i=0,k=1;i<32;++i,k<<=1){
            if((a&k)&&(b&k)){
                ans |= k;
            }
        }
        printf("%u\n",ans?ans:1);
    }
    return 0;
}
