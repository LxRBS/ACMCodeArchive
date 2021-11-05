#include <cstdio>
typedef long long llt;

llt Fac[21] = {1LL};//20!在64位整型内
llt Stirling[21][21] = {0LL};//第一类斯特林数
void calc(){
    for(int i=1;i<21;++i){
        Fac[i] = Fac[i-1] * (llt)i;
        Stirling[i][i] = 1LL;
    }   
    for(int p=2;p<21;++p)for(int k=1;k<p;++k)
        Stirling[p][k] = (llt)(p-1)*Stirling[p-1][k] + Stirling[p-1][k-1];      
} 
int main(){
    calc();
    int kase;
    scanf("%d",&kase);
    while(kase--){
        int n,k;
        scanf("%d%d",&n,&k); 
        llt s = 0LL;
        for(int i=1;i<=k;++i) s +=  Stirling[n][i]-Stirling[n-1][i-1];
        printf("%.4lf\n",(double)s/(double)Fac[n]);             
    }
    return 0;
}
