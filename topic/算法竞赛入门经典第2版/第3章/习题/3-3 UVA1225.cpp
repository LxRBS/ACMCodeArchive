#include <cstdio>

int const SIZE = 10010;
int A[10][SIZE] = {0};//A[i][n]��ʾǰn�������С�����iһ�������˶��ٴ�
void init(){          //һ���������п��ܵĴ𰸶������
    for(int i=1;i<SIZE;++i){
        for(int j=0;j<10;++j){   //����i-1�Ĵ𰸼���i�Ĵ�
            A[j][i] = A[j][i-1];
        }

        int n = i;
        while(n){
            ++A[n%10][i];
            n /= 10;
        }
    }
}
int main(){
    //freopen("1.txt","r",stdin);

    init();
    int nofkase;
    scanf("%d",&nofkase);
    while(nofkase--){
        int n;
        scanf("%d",&n);

        printf("%d",A[0][n]);  //ע������ĸ�ʽ��ÿ������֮����һ���ո񣬶����һ����֮��û�пո�
        for(int i=1;i<10;++i)printf(" %d",A[i][n]);
        printf("\n");
    }
    return 0;
}
