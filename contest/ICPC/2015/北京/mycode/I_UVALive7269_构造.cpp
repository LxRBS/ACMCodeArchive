/**
   n���ߣ����ȷֱ���1/2/3...n�����ܷ񹹳�һ������
   Ҫ�����������������䣬ż����ż��������
   ���ܷ�������Ҹ���������
   ����3ʱ��
   312
   332
   4ʱ��
   34412
   33442
   5ʱ��
   55522
   54433
   54413
   �������������ӷֽ��֪
   N������ʱ��(N+1)/2�С�N��
   N��ż��ʱ��N/2�С�(N+1)��
   ��2��ʼ�������ż���������ų�2�У����ں��漴��
   �����������ֱ�ӷ������һ�У�Ȼ���ٰ����һ��N�����Ϸ�������һ��λ�ü���
   ���ǰ�����������N==5ʱ4�ǲ��Եģ�����5����ǰ��Ϊ����ֵ
*/
#include <stdio.h>
#include <algorithm>
using namespace std;

char const X5[] = {
    "3 4\n1 4 1 5\n2 4 2 5 3 5\n2 2 2 3 3 3 3 2\n3 1 2 1 1 1 1 2 1 3\n"
};

int N,R,C;
int main(){
    //freopen("1.txt","w",stdout);
    while(EOF!=scanf("%d",&N)){
        N&1?(R=(N+1)>>1,C=N):(R=N>>1,C=N+1);
        printf("%d %d\n",R,C);

        if(1==N){//ֱ�Ӵ�ӡ
            printf("1 1\n");
            continue;
        }

        if(2==N){
            printf("1 1\n1 2 1 3\n");
            continue;
        }

        if(3==N){
            printf("1 1\n1 3 2 3\n2 1 2 2 1 2\n");
            continue;
        }

        if(4==N){
            printf("1 1\n1 3 2 3\n2 1 2 2 1 2\n1 4 2 4 2 5 1 5\n");
            continue;
        }

        if(5==N){
            printf("%s",X5);
            continue;
        }

        //��NΪ����ֵʱ
        printf("%s",X5);
        for(int i=6;i<=N;++i){
            if(i&1){//������ֱ���������һ��
                int lastr = (i+1)>>1;
                for(int j=1;j<i;++j){
                    printf("%d %d ",lastr,j);
                }
                //���һ��Ҫ�����ϻ�λ��
                printf("%d %d",lastr-1,i-1);
            }else{//ż�����������2��
                int lastr = i>>1;
                //����������һ��ż��������Ҫ�ѵ�1�����һ�������ط�
                if(i==N){//�����ط����ӵ�1�п�ʼ��
                    printf("%d %d",lastr,i);
                    //��һ��
                    for(int j=(i>>1)-1;j>=1;--j){
                        printf(" %d %d",j,i);
                    }
                    //�ڶ���
                    for(int j=1;j<=(i>>1);++j){
                        printf(" %d %d",j,i+1);
                    }
                }else{//Ҫ���ط����ӵڶ��п�ʼ��
                    printf("%d %d",lastr+1,i+1);
                    for(int j=(i>>1);j>=1;--j){
                        printf(" %d %d",j,i+1);
                    }
                    for(int j=1;j<(i>>1);++j){
                        printf(" %d %d",j,i);
                    }
                }
            }
            printf("\n");
        }
    }
    return 0;
}
