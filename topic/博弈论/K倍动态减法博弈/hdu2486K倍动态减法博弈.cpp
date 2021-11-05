/**
    K倍动态减法博弈
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long llt;
//K倍动态博弈的必败点
//数组a存放结果，数组b辅助
//n是计算的上限即a[i]<=n，k是倍数
//返回a的数量
int KNim(llt n,llt k,llt a[],llt b[]){
    a[0] = b[0] = 1;
    int cnt = 1;
    int t = 0;
    while(a[cnt-1]<n){
        a[cnt]=b[cnt-1]+1;
        //找到第一个t使得at*k<a[cnt]
        while(a[t+1]*k<a[cnt]) ++t;
        if(a[t]*k<a[cnt]) b[cnt] = b[t] + a[cnt];
        else b[cnt] = a[cnt];
        ++cnt;
    }
    return cnt;
}

llt A[1000010],B[1000010];
int main(){
    //freopen("1.txt","r",stdin);
    int nofkase;
    scanf("%d",&nofkase);
    for(int kase=1;kase<=nofkase;++kase){
        llt n,k;
        scanf("%lld%lld",&n,&k);
        int cnt = KNim(n,k,A,B);

        printf("Case %d: ",kase);
        if(A[cnt-1]==n){
            printf("lose\n");
            continue;
        }

        //不停的减去A中的数，最后剩下的即可
        int ans = 0;
        for(int i=cnt-1;n;--i){
            if(A[i]<=n) n -= A[i], ans = i;
        }
        printf("%lld\n",A[ans]);
    }
    return 0;
}
