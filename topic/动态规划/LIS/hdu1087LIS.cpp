//严格最大上升子序列 
#include <cstdio>
int DP[1001];
int A[1001];
void dp(int n){
    DP[0] = A[0];
    for(int i=1;i<n;++i){
        DP[i] = A[i];
        for(int j=0;j<i;++j){
            if ( A[i] > A[j] ){
                int t = DP[j] + A[i];
                if ( t > DP[i] ) DP[i] = t;
            }
        }
    } 
}
int main(){
    int n;
    while( scanf("%d",&n) && n ){
        for(int i=0;i<n;++i)scanf("%d",A+i);
        dp(n);
        int ret = DP[0];
        for(int i=1;i<n;++i)
            if(ret<DP[i])ret=DP[i];
        printf("%d\n",ret);
    }
    return 0;
}