#include <cstdio>
#include <cstring>

int const SIZE = 100010;
char A[SIZE],B[SIZE];

int main(){
    //freopen("1.txt","r",stdin);

    while( EOF != scanf("%s%s",A,B) ){
        int la = strlen(A), lb = strlen(B);

        if ( la > lb ){
            printf("No\n");
            continue;
        }

        bool ans = false;
        int k = 0;
        for(int b=0;b<=lb;++b){        //挨个匹配A中的字母，这是一种贪心策略
            if ( B[b] == A[k] ) ++k;
            if ( la + 1 == k ) ans = true;
        }

        printf(ans?"Yes\n":"No\n");   //printf里面是一个条件表达式，?:是条件运算符
    }

    return 0;
}
