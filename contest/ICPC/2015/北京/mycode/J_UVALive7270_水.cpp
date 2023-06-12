/**
   B/C模式下有B操作和C操作，操作后面接序号
   S模式下有S操作
   整个操作序列划分为若干块，每一块只能有1一个模式
   问最多能划分成多少块。
   由于S是不带序号的，所以每个S操作单独成块
   B/C操作是带序号的，每个1操作表示新的一块
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