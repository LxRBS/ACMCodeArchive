/**
   给定各种货币的汇率，问是否存在套利的可能
   跑一个Floyd，看是否有大于1的
   题目输入有自己跟自己兑换的，注意初始化的顺序
*/
#include <bits/stdc++.h>
using namespace std;

int N,M;
map<string,int> Map;
double G[33][33];
bool read(){
    cin>>N;
    if(0==N)return false;

    for(int i=1;i<=N;++i)fill(G[i],G[i]+N+1,0.0);
    for(int i=1;i<=N;++i)G[i][i]=1.0;
    Map.clear();
    for(int i=1;i<=N;++i){
        string s;
        cin>>s;
        Map[s] = i;
    }
    cin>>M;
    while(M--){
        string a,b;
        double w;
        cin>>a>>w>>b;
        int ia = Map[a];
        int ib = Map[b];
        if(G[ia][ib]<w)G[ia][ib]=w;
    }
    
    return true;
}
int proc(){
    //floyd
    for(int k=1;k<=N;++k)for(int i=1;i<=N;++i)for(int j=1;j<=N;++j){
        G[i][j] = max(G[i][j],G[i][k]*G[k][j]);
    }
    for(int i=1;i<=N;++i)if(G[i][i]>1)return 1;
    return 0;
}
char Ans[][10] = {"No","Yes"};
int main(){
    //freopen("1.txt","r",stdin);
    for(int kase=1;read();++kase){
        printf("Case %d: %s\n",kase,Ans[proc()]);
    }

    return 0;
}
