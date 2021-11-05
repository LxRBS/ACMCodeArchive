/**
   一棵树或者一个基环树，求字典序最小的深搜遍历
   如果是一个树，直接贪心深搜即可
   如果是一个基环树，则需要考虑环。
   最简单的做法是找环以后，将环上的每条边断开，再深搜一遍,O(N^2)可解
*/
#include<bits/stdc++.h>
using namespace std;

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

int N,M;
int Graph[5001][5001];
int Deg[5001];

int Ans[5001];
int Cnt;

//a,b表示禁用的边
void dfs(int u, int parent,int a=0,int b=0){
    if(Cnt == N) return;

    Ans[Cnt++] = u;
    for(int v,i=0,n=Deg[u];i<n;++i){
        if((v=Graph[u][i])!=parent&&!(u==a&&v==b||(u==b&&v==a))){
            dfs(v, u, a, b);
        }
    }
}

int InDeg[5001];
int Cycle[5001], Cycle_Cnt;
bool Flag[5001];
void topoSort(){
    queue<int> q;
    for(int i=1;i<=N;++i)if(1==InDeg[i])q.push(i);
    while(!q.empty()){
        int h = q.front();
        q.pop();
        for(int v,i=0,n=Deg[h];i<n;++i){
            if(InDeg[v=Graph[h][i]]>1){
                if(1==--InDeg[v]){
                    q.push(v);
                }
            }
        }
    }
    //入度大于1的点都是环上的点，整理环上的点
    fill(Flag,Flag+N+1,false);
    int k = 1;
    while(InDeg[k]<=1) ++k;
    bool flag = false;
    do{
        Flag[Cycle[Cycle_Cnt++] = k] = true;
        flag = false;
        for(int i=0,n=Deg[k];i<n;++i){
            if(InDeg[Graph[k][i]]>1&&!Flag[Graph[k][i]]){
                k = Graph[k][i];
                flag = true;
                break;
            }
        }
    }while(flag);
    Cycle[Cycle_Cnt] = *Cycle;
}

int TmpAns[5001];
bool check(){
    for(int i=0;i<N;++i){
        if(Ans[i]!=TmpAns[i]) return Ans[i]<TmpAns[i];
    }
    return false;
}
int main(){
    //freopen("1.txt","r",stdin);
    N = getUnsigned();
    M = getUnsigned();
    for(int a,b,i=0;i<M;++i){
        a = getUnsigned();
        b = getUnsigned();
        Graph[a][Deg[a]++] = b;
        Graph[b][Deg[b]++] = a;
    }
    //排序
    for(int i=1;i<=N;++i) sort(Graph[i],Graph[i]+Deg[i]);
    if(M==N-1){//树
        Cnt = 0;
        dfs(1, 0);
        for(int i=0;i<N;++i)printf("%d ",Ans[i]);
    }else{//基环树
        //首先找环
        copy(Deg,Deg+N+1,InDeg);
        topoSort();
        TmpAns[0] = 100000;
        //for环上的每条边，断开，再做一个dfs
        for(int i=0;i<Cycle_Cnt;++i){
            Cnt = 0;
            dfs(1, 0, Cycle[i], Cycle[i+1]);
            if(check()) copy(Ans,Ans+N,TmpAns);
        }
        for(int i=0;i<N;++i)printf("%d ",TmpAns[i]);
    }
    return 0;
}
