/*
    给定字符串，问在后面补几个字符
    才能使之出现循环节
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

//求特征向量
void getNext(char const src[],int n,int next[]){
    next[0] = 0;
    for(int i=1;i<n;++i){
        int k = next[i-1];
        while( k > 0 && src[i] != src[k] ) k = next[k-1];
        next[i] = src[i] == src[k] ? k + 1 : 0;
    }
}

char A[100010];
int Next[100010];
int main(){
    //freopen("1.txt","r",stdin);
    int nofkase;
    scanf("%d",&nofkase);
    while(nofkase--){
        scanf("%s",A);
        int n = strlen(A);
        getNext(A,n,Next);

        int ans = n - Next[n-1];
        if ( ans != n && 0 == n % ans ) printf("0\n");
        else printf("%d\n",ans-Next[n-1]%ans);
    }
    return 0;
}
