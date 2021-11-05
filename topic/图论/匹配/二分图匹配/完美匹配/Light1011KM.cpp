#include <cstdio>
#include <algorithm>
using namespace std;

typedef int weight_t;

int const SIZE = 17;
weight_t const INF = 3000000;

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

int N;
void read(){
    scanf("%d",&N);
    for(int i=0;i<N;++i)for(int j=0;j<N;++j)scanf("%d",G[i]+j);
}
int main(){
    //freopen("1.txt","r",stdin);
    int nofkase;
    scanf("%d",&nofkase);
    for(int kase=1;kase<=nofkase;++kase){
        read();
        printf("Case %d: %d\n",kase,KM(N));
    }
}

