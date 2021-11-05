#include <cstdio>
#include <cstring>

int Pos[3100];
int A[3100];
int main(){
    //freopen("1.txt","r",stdin);
    int a,b,i,k;
    while( EOF != scanf("%d%d",&a,&b) ){
        memset(Pos,0,sizeof(Pos));     //memset的作用是把Pos数组全部清零

        printf("%d/%d = %d.",a,b,a/b);

        a = a % b;
        for(k=1;;++k){
            if ( Pos[a] ) break; //Pos[a]记录a出现的位置，a是余数，余数重复出现意味着发现循环节

            Pos[a] = k;
            A[k] = a * 10 / b;
            a = a * 10 % b;     //手工模拟除法
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
