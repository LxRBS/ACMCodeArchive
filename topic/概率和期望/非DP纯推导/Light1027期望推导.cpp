/*
    ��N���ţ��ȸ��ʵı�ѡ��
    ������Щ��ѡ���Ժ󣬻���xi���Ӻ��뿪�Թ�
    ����һЩ�������yi���Ӻ�ص�ԭ��
    ÿ��ѡ�񶼲�����һ�ε�Ӱ��
    �ʳ��ŵ�ƽ������ʱ��
    ���ΪE���� E = SIGMA( Xi / n ) + SIGMA( yi/n + E )
*/

#include <stdio.h>

int N;
int A[110];

int gcd(int a,int b){
    while( b ){
        int r = b;
        b = a % b;
        a = r;
    }
    return a;
}

int main(){
    int nofkase;
    scanf("%d",&nofkase);
    for(int kase=1;kase<=nofkase;++kase){
        int sum = 0, cnt = 0;

        scanf("%d",&N);
        for(int i=0;i<N;++i){
            scanf("%d",A+i);
            if ( A[i] > 0 ) sum += A[i], ++cnt;
            else sum += -A[i];
        }

        printf("Case %d: ",kase);
        if ( 0 == cnt ) printf("inf\n");
        else {
            int g = gcd(sum,cnt);
            printf("%d/%d\n",sum/g,cnt/g);
        }
    }
    return 0;
}

