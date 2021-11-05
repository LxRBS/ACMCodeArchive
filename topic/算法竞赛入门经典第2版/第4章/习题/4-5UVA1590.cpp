/**
   �������ɸ�IP��ַ�����ܹ�������ЩIP����С����
   �������������׵�ַ����������
*/
#include <stdio.h>
#include <algorithm>
using namespace std;

typedef unsigned int uint;

uint const MASK[] = {
    0,0x80000000,0xC0000000,0xE0000000,0xF0000000,
    0xF8000000,0xFC000000,0xFE000000,0xFF000000,
    0xFF800000,0xFFC00000,0xFFE00000,0xFFF00000,
    0xFFF80000,0xFFFC0000,0xFFFE0000,0xFFFF0000,
    0xFFFF8000,0xFFFFC000,0xFFFFE000,0xFFFFF000,
    0xFFFFF800,0xFFFFFC00,0xFFFFFE00,0xFFFFFF00,
    0xFFFFFF80,0xFFFFFFC0,0xFFFFFFE0,0xFFFFFFF0,
    0xFFFFFFF8,0xFFFFFFFC,0xFFFFFFFE,0xFFFFFFFF
};

//���ip��ʽ
void output(uint ip){
    printf("%u.%d.%d.%d\n",ip>>24,(ip>>16)&0xFF,(ip>>8)&0xFF,ip&0xFF);
}

int main(){
    //freopen("1.txt","r",stdin);
    int n;
    while(EOF!=scanf("%d",&n)){//һ����n��IP��ַ
        uint a,b,c,d;
        scanf("%u.%u.%u.%u",&a,&b,&c,&d);
        uint ip = (a<<24)|(b<<16)|(c<<8)|d;
        uint ans = 0;//��ʾ��λ����ͬ������

        for(int i=1;i<n;++i){
            scanf("%u.%u.%u.%u",&a,&b,&c,&d);
            uint tmp = (a<<24)|(b<<16)|(c<<8)|d;
            //��λȡ���
            tmp = (ip>>ans)^(tmp>>ans);
            //�ҵ�tmp�����λ1
            int k = 32-ans-1;
            while(k>=0&&!((1<<k)&tmp)) --k;
            ans += k+1;
        }

        uint mask = MASK[32-ans];

        ip &= mask;
        output(ip);
        output(mask);
    }
    
    return 0;

}
