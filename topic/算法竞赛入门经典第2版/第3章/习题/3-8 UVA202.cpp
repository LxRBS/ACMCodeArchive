#include <cstdio>
#include <cstring>

int Pos[3100];
int A[3100];
int main(){
    //freopen("1.txt","r",stdin);
    int a,b,i,k;
    while( EOF != scanf("%d%d",&a,&b) ){
        memset(Pos,0,sizeof(Pos));     //memset�������ǰ�Pos����ȫ������

        printf("%d/%d = %d.",a,b,a/b);

        a = a % b;
        for(k=1;;++k){
            if ( Pos[a] ) break; //Pos[a]��¼a���ֵ�λ�ã�a�������������ظ�������ζ�ŷ���ѭ����

            Pos[a] = k;
            A[k] = a * 10 / b;
            a = a * 10 % b;     //�ֹ�ģ�����
        }

        for(int i=1;i<Pos[a];++i)printf("%d",A[i]);
        printf("(");
        for(i=Pos[a];i<k&&i<=50;++i)printf("%d",A[i]);
        if ( i != k ) printf("...");
        printf(")\n");

        printf("   %d = number of digits in repeating cycle\n\n",k-Pos [a]);
    }
    return 0;
}
