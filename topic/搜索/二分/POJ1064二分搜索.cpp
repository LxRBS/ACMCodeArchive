/*
    N个不同长度的电缆，一共切成等长度的K份
    要求这个长度最长
    如果长度小于0.01，则输出0.00
*/
#include <stdio.h>
typedef long long llt;

int N,K;
llt Total;
llt A[10010];
bool read(){
    if ( EOF == scanf("%d%d",&N,&K) ) return false;
    int a,b;
    Total = 0;
    for(int i=0;i<N;++i){
        scanf("%d.%d",&a,&b);
        A[i] = a * 100LL + b;
        Total += A[i];
    }
    return true;
}

//检查N个电线是否能分成K份，每份长为m
bool check(int m){
    if ( 0 == m ) return true;

    int ans = 0;
    for(int i=0;i<N&&ans<K;++i){
        ans+=A[i]/m;
    }
    return ans >= K;
}

llt proc(){
    //答案至少是0，至多是Total/K
    llt mid, left = 0, right = Total / K;
    
    //可行解从小到大，需求取最大解
    //则判断条件为本身，最后答案为right
    do{
        mid = ( left + right ) >> 1;
        if ( check(mid) ) left = mid + 1;
        else right = mid - 1;
    }while( left <= right );
    return right>=1?right:0;
}
int main(){
    //freopen("1.txt","r",stdin);
    while( read() ) printf("%.2f\n",proc()/100.0);
    return 0;
}
