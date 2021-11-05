//很明显的二分图带权匹配，要求权和最小
//稍微处理一下即可
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

typedef int weight_t;

int const SIZE = 110;
weight_t const INF = 100000;

//Matrix of bipartite graph, indexed from 0
weight_t G[SIZE][SIZE];
//Link[i] - i means that there is an edge between A[Link[i]] and B[i]
int Link[SIZE];
//Flags
bool FA[SIZE],FB[SIZE];
//Labels
weight_t LA[SIZE],LB[SIZE];

weight_t Slack[SIZE];

//returns true if there exists an augment path
//n is the size of A, also equals to size of B
bool dfs(int node,int n){
    FA[node] = true;
    for(int i=0;i<n;++i){
        if ( FB[i] ) continue;

        if ( LA[node] + LB[i] == G[node][i] ){
            FB[i] = true;

            if ( -1 == Link[i] || dfs(Link[i],n) ){
                Link[i] = node;
                return true;
            }
        }else{
            weight_t t = LA[node] + LB[i] - G[node][i];
            if ( t < Slack[i] ) Slack[i] = t;
        }
    }
    return false;
}

//returns the value of the best match
//n is the size of A, it is equal to size of B too
int KM(int n){
    fill(Link,Link+n,-1);

    fill(LB,LB+n,0);
    for(int i=0;i<n;++i){
        LA[i] = *max_element(G[i],G[i]+n);
    }

    for(int i=0;i<n;++i){
        fill(Slack,Slack+n,INF);

        while(1){
            fill(FA,FA+n,false);
            fill(FB,FB+n,false);

            //match successfully
            if ( dfs(i,n) ) break;

            //finds the available label changing
            weight_t delta = INF;
            for(int j=0;j<n;++j){
                if( !FB[j] && Slack[j] < delta){
                    delta = Slack[j];
                }
            }

            //updates labels
            for(int j=0;j<n;++j){
                if ( FA[j] ) LA[j] -= delta;
                if ( FB[j] ) LB[j] += delta;
                else Slack[j] -= delta;
            }
        }
    }

    int ret = 0;
    for(int i=0;i<n;++i) ret += G[Link[i]][i];
    return ret;
}

int N,M;
char A[110][110];
int R[2][110],C[2][110];
int MenCnt,HouseCnt;
inline int _f(int menIdx,int houseIdx){
    int dr = R[0][menIdx] - R[1][houseIdx];
    if ( dr < 0 ) dr = -dr;
    int dc = C[0][menIdx] - C[1][houseIdx];
    if ( dc < 0 ) dc = -dc;
    return dr + dc;
}
bool read(){
    scanf("%d%d",&N,&M);
    if ( 0 == N && 0 == M ) return false;

    MenCnt = HouseCnt = 0;
    for(int i=0;i<N;++i){
        scanf("%s",A[i]);
        for(char *p=A[i],j=0;*p;++p,++j){
            if ( 'm' == *p ) R[0][MenCnt] = i, C[0][MenCnt++] = j;
            else if ( 'H' == *p ) R[1][HouseCnt] = i, C[1][HouseCnt++] = j;
        }
    }

    //建立二分图
    memset(G,0,sizeof(G));
    for(int i=0;i<MenCnt;++i)for(int j=0;j<HouseCnt;++j){
        G[i][j] = 20000 - _f(i,j);
    }
    return true;
}

int main(){
    //freopen("1.txt","r",stdin);
    while( read() ){
        int n = MenCnt < HouseCnt ? MenCnt : HouseCnt;
        printf("%d\n",20000 * n - KM(MenCnt+HouseCnt-n));
    }
}
