#include <cstdio>
#include <cstring>

char A[100];
int main(){
    //freopen("1.txt","r",stdin);

    int nofkase;
    scanf("%d",&nofkase);
    for(int kase=0;kase<nofkase;++kase){
        scanf("%s",A);

        int len = strlen(A);
        for(int i=1;i<=len;++i){
            if ( len % i ) continue;//��������ֻ������len������

            int n = len / i;
            for(int j=0;j<i;++j){
                char ch = A[j];     //Aj�����ĸ�ض����ظ����ɴΣ�������ڳ����Ļ�
                for(int k=1;k<n;++k){
                    if ( ch != A[i*k+j] ) goto L;//ֱ����������ѭ����ĩβ��������һ��ѭ��
                }
            }
            if (kase) printf("\n");//��仰���ڿ�������Ļ��У���ϸ������ĸ�ʽҪ��
            printf("%d\n",i);      //�ܵ�����϶��Ǵ𰸣����Ҳ�����ִ��for j��ѭ����
            break;
            L:;//nothing here
        }
    }
    return 0;
}