/**
   B/Cģʽ����B������C������������������
   Sģʽ����S����
   �����������л���Ϊ���ɿ飬ÿһ��ֻ����1һ��ģʽ
   ������ܻ��ֳɶ��ٿ顣
   ����S�ǲ�����ŵģ�����ÿ��S���������ɿ�
   B/C�����Ǵ���ŵģ�ÿ��1������ʾ�µ�һ��
*/
#include <stdio.h>
char A[1000010];

int main(){
    int n;
    while(EOF!=scanf("%d",&n)){
        fgets(A,10000,stdin);

        int ans = 0;
        while(n--){
            fgets(A,10000,stdin);
            if('S'==*A) ++ans;
            else if('1'==A[2]&&('\n'==A[3]||'\0'==A[3]))++ans;
        }
        printf("%d\n",ans);
    }
    return 0;
}
