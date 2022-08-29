#include<bits/stdc++.h>
using namespace std;
int T,n,f[25],g[25];
char s[20];
int main(){
    // freopen("1009.in","r",stdin);
    // freopen("1009.out","w",stdout);
    scanf("%d",&T);
    f[1]=f[2]=f[3]=1;f[4]=2;
    g[1]=g[2]=1;g[3]=g[4]=2;
    for(int i=5;i<=20;i++) f[i]=g[i-3]+1,g[i]=f[i-4]+2;
    while(T--){
        scanf("%d %s",&n,s+1);
        if(s[1]=='A'){
            if(n<=20) printf("%d\n",f[n]);
            else{
                int t=n/7-1;
                printf("%d\n",3*t+f[n-t*7]);
            }
        }else{
            if(n<=20) printf("%d\n",g[n]);
            else{
                int t=n/7-1;
                printf("%d\n",3*t+g[n-t*7]);
            }
        }
    }
    return 0;
}