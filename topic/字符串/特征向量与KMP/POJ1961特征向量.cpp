/*
    �����ַ�������ʲôʱ�����ѭ����
    ���� aabaabaab
    λ�ô�1��ʼ������λ��2/6/9ʱ����ѭ����
*/
#include <cstdio>
#include <cstring>

//��src������������nΪsrc�ĳ���
void getNext(char const src[],int n,int next[]){
    next[0] = 0;
    for(int i=1;i<n;++i){
        int k = next[i-1];
        while( k > 0 && src[i] != src[k] ) k = next[k-1];
        next[i] = src[i] == src[k] ? k + 1 : 0;
    }
}
int N;
char A[1000100];
int Next[1000100];
int main(){
    //freopen("1.txt","r",stdin);
    for(int kase=1;scanf("%d",&N)&&N;++kase){
        fgets(A,1000100,stdin);
        fgets(A,1000100,stdin);
        int n = strlen(A) - 1;

        getNext(A,n,Next);

        printf("Test case #%d\n",kase);
        for(int i=2;i<=n;++i){
            int t = i - Next[i-1];
            if ( 0 == i % t && 1 != i / t ){
                printf("%d %d\n",i,i/t);
            }
        }
        printf("\n");
    }
    return 0;
}
