#include <cstdio>

char A[100];
int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
#endif

    int n;
    scanf("%d",&n);
    while(n--){
        scanf("%s",A);//�����ַ�������A��ͷ��û�пո����ʹ��scanf %s

        int ret = 0;
        char *p = A;//p��һ��ָ�룬ר�������ַ���ѭ���У�����Ч�ʱȽϸ�
        while(*p){  //��Ҳ��һ��ר�����ַ�����ѭ������������ʵ���ϵȼ��� *p != '\0'�� ��סC���Ե��ַ���������'\0'��β��
            int k = 0;
            while( 'O' == *p ) ++p, ++k;//��ǰ��ĸ��O���ͼ�k��++p����˼����ȡ��һ����ĸ
            ret += k * ( k + 1 ) / 2;   //ÿһ��O�ĵ÷־��Ǵ�1�ӵ�k

            while( *p && 'X' == *p ) ++p;
        }

        printf("%d\n",ret);
    }
    return 0;
}
