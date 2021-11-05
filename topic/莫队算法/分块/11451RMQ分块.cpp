/**
   ³É¶ÎÐÞ¸ÄRMQ
*/
#include <cstdio>
#include <climits>
#include <algorithm>
using namespace std;

int const SIZE = 100010;
int const BLOCKSIZE = 300;

int N,M;
int A[SIZE];
int Block[SIZE];
int Peak[SIZE];
int Lazy[SIZE];

void build(int n){
    fill(Lazy,Lazy+n/BLOCKSIZE+2,0);
    fill(Peak,Peak+n/BLOCKSIZE+2,INT_MIN);

    for(int i=1;i<=n;++i){
        Block[i] = ( i - 1 ) / BLOCKSIZE + 1;
        if ( Peak[Block[i]] < A[i] ) Peak[Block[i]] = A[i];
    }
}

void modify(int s,int e,int delta){
    for(int i=s,n=min(Block[s]*BLOCKSIZE,e);i<=n;++i){
        A[i] += delta;
    }
    Peak[Block[s]] = Lazy[Block[s]] + *max_element(A+(Block[s]-1)*BLOCKSIZE+1,A+Block[s]*BLOCKSIZE+1);

    if ( Block[s] != Block[e] ) for(int i=(Block[e]-1)*BLOCKSIZE+1;i<=e;++i){
        A[i] += delta;
    }
    Peak[Block[e]] = Lazy[Block[e]] + *max_element(A+(Block[e]-1)*BLOCKSIZE+1,A+Block[e]*BLOCKSIZE+1);

    for(int i=Block[s]+1;i<Block[e];++i){
        Lazy[i] += delta;
        Peak[i] += delta;
    }
}

int query(int s,int e){
    int ret = INT_MIN;

    for(int i=s,n=min(Block[s]*BLOCKSIZE,e);i<=n;++i){
        if ( ret < A[i] + Lazy[Block[s]] ) ret = A[i] + Lazy[Block[s]];
    }

    if ( Block[s] != Block[e] ) for(int i=(Block[e]-1)*BLOCKSIZE+1;i<=e;++i){
        if ( ret < A[i] + Lazy[Block[e]] ) ret = A[i] + Lazy[Block[e]];
    }

    for(int i=Block[s]+1;i<Block[e];++i){
        if ( ret < Peak[i] ) ret = Peak[i];
    }

    return ret;
}

bool read(){
    if ( EOF == scanf("%d%d",&N,&M) ) return false;
    for(int i=1;i<=N;++i)scanf("%d",A+i);

    build(N);
    return true;
}
void proc(){
    char cmd[3];
    int s,e,delta;
    for(int i=0;i<M;++i){
        scanf("%s%d%d",cmd,&s,&e);
        if ( 'C' == *cmd ){
            scanf("%d",&delta);
            modify(s,e,delta);
        }else{
            printf("%d\n",query(s,e));
        }
    }
}
int main(){
    for(int kase=1;read();++kase){
        printf("Case %d:\n",kase);
        proc();
    }
    return 0;
}