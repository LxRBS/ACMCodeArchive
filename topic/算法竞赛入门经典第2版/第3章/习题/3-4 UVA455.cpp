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
            if ( len % i ) continue;//首先周期只可能是len的因子

            int n = len / i;
            for(int j=0;j<i;++j){
                char ch = A[j];     //Aj这个字母必定会重复若干次，如果周期成立的话
                for(int k=1;k<n;++k){
                    if ( ch != A[i*k+j] ) goto L;//直接跳到本次循环的末尾，进行下一次循环
                }
            }
            if (kase) printf("\n");//这句话用于控制输出的换行，仔细看输出的格式要求
            printf("%d\n",i);      //能到这里肯定是答案，而且不必在执行for j的循环。
            break;
            L:;//nothing here
        }
    }
    return 0;
}