/*
  ����A/B���ҳ���С��C��ʹ��
  A^C & B^C ��С
  A��B��Ӧ��λ����1ʱ����Ҫ��CΪ����Ϊ1
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
