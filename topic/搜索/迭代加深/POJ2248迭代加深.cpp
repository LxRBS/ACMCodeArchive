/**
   给定N，要求生成一个元素各不相同的数列{1,x,...,y,N}，
   使得每个数都是两个元素之和（可以重复），
   要求数列最短，N在100以内
   例如当N==5时，{1,2,4,5}是一个解
   多解的情况下随便输出一个毫无疑问{1,2,3,...,N}是一个可行解，
   这样就要深入100层，且肯定不是答案
   使用迭代加深限制搜索层数，由于事先不知道层数，动态控制
*/
#include <stdio.h>
#include <algorithm>
using namespace std;

int Limit;
int N,A[110] = {1};

//搜索第x个数，x从0开始
bool dfs(int x){
    if(x>=Limit){
        if(A[x-1]==N) return true;
        return false;
    }

    //从大往下搜索，方便剪枝
    bool flag[110] = {false};
    for(int i=x-1;i>=0;--i)for(int j=i;j>=0;--j){
        if(A[i]+A[j]<=A[x-1]) break;
        if(A[i]+A[j]<=N&&!flag[A[i]+A[j]]){
            flag[A[x] = A[i]+A[j]] = true;
            if(dfs(x+1)) return true;
            //不需要还原，自然会覆盖掉
        }
    }
    return false;
}

int main(){
    //freopen("1.txt","r",stdin);
    while(1){
        scanf("%d",&N);
        if(0==N) break;

        if(1==N){
            printf("1\n");continue;
        }else if(2==N){
            printf("1 2\n");continue;
        }

        fill(A,A+N+1,0);
        A[0]= 1;

        for(Limit=3;;++Limit){
            if(dfs(1)){
                printf("1");
                for(int i=1;A[i]!=N;++i)printf(" %d",A[i]);
                printf(" %d\n",N);
                break;
            }
        }

    }
    return 0;
}
