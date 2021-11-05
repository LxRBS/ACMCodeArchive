#include <stdio.h>

#define N 1000000
int dp[N];
int dfs(int n)
{
    int i,tm,tp;
    int hash[150];
    
memset(hash,0,sizeof(hash));
    
    tm=tp=n;
    
    tm=tp%10;
    if(tm==0){
        tp/=10;
        if(dp[tp]==-1)
            dp[tp]=dfs(tp);
        hash[dp[tp]]=1;
    }
    while(tm>0){
        --tp;
        if(dp[tp]==-1)
            dp[tp]=dfs(tp);
        hash[dp[tp]]=1;
        --tm;
    }
    tp=n;
    tm=(tp/10)%10;
    if(tm==0&&n>=100){
        tp/=100;
        if(dp[tp]==-1)
            dp[tp]=dfs(tp);
        hash[dp[tp]]=1;
    }
    while(tm>0){
        tp-=10;
        if(tp<10)break;
        if(dp[tp]==-1)
            dp[tp]=dfs(tp);
        hash[dp[tp]]=1;
        tm--;
    }
    tp=n;
    tm=(tp/100)%10;
    if(tm==0&&n>=1000){
        tp/=1000;
        if(dp[tp]==-1)
            dp[tp]=dfs(tp);
        hash[dp[tp]]=1;
    }
    while(tm>0){
        tp-=100;
        if(tp<100)break;
        if(dp[tp]==-1)
            dp[tp]=dfs(tp);
        hash[dp[tp]]=1;
        tm--;
    }
    tp=n;
    tm=(tp/1000)%10;
    if(tm==0&&n>=10000){
        tp/=10000;
        if(dp[tp]==-1)
            dp[tp]=dfs(tp);
        hash[dp[tp]]=1;
    }
    while(tm>0){
        tp-=1000;
        if(tp<1000)break;
        if(dp[tp]==-1)
            dp[tp]=dfs(tp);
        hash[dp[tp]]=1;
        tm--;
    }
    tp=n;
    tm=(tp/10000)%10;
    if(tm==0&&n>=100000){
        tp/=100000;
        if(dp[tp]==-1)
            dp[tp]=dfs(tp);
        hash[dp[tp]]=1;
    }
    while(tm>0){
        tp-=10000;
        if(tp<10000)break;
        if(dp[tp]==-1)
            dp[tp]=dfs(tp);
        hash[dp[tp]]=1;
        tm--;
    }
    tp=n;
    tm=(tp/100000)%10;
    while(tm>0){
        tp-=100000;
        if(tp<100000)break;
        if(dp[tp]==-1)
            dp[tp]=dfs(tp);
        hash[dp[tp]]=1;
        tm--;
    }
    for(i=0;i<150;i++)
        if(hash[i]==0)return i;
}
int main()
{  
    char s[9];
    memset(dp,-1,sizeof(dp));
    dp[0]=1;//±ØÊ¤µã 
    
    while(gets(s)){
        int nn=0;
        int i = 0;
        
if(s[0]=='0'){
            printf("Yes\n");
            continue;
        }
        
        while(s[i]){
            nn=nn*10+s[i]-48;
            i++;
        }
        if(dp[nn]==-1)dp[nn]=dfs(nn);
        if(dp[nn]==0){
            printf("No\n");
        }
        else printf("Yes\n");
    }
    return 0;
}
