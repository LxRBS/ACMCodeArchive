/**
  给定一些横平竖直的线，问一共有多少个正方形
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int N,M;
bool G[81][81];

inline int tr(int row,int col){
    return row + col * N;
}

bool read(){
    if ( EOF == scanf("%d%d",&N,&M) ) return false;

    memset(G,0,sizeof(G));

    char s[3];
    int row,col;
    for(int i=0;i<M;++i){
        scanf("%s%d%d",s,&row,&col);
        --row, --col;
        if ( 'V' == *s ) swap(row,col);

        int a = tr(row,col);
        int b = 'H' == *s ? tr(row,col+1) : tr(row+1,col);
        G[a][b] = G[b][a] = true;
    }
    return true;
}
void preProc(){
    for(int r=0;r<N;++r)for(int c=0;c<N;++c){
        int u = tr(r,c);
        //rightwards
        int prev = tr(r+1,c);
        for(int rr=r+2;rr<N;++rr){
            int cur = tr(rr,c);
            if ( !G[u][prev] || !G[prev][cur] ) break;

            G[u][cur] = G[cur][u] = true;
            prev = cur;
        }

        prev = tr(r,c+1);
        for(int cc=c+2;cc<N;++cc){
            int cur = tr(r,cc);
            if ( !G[u][prev] || !G[prev][cur] ) break;

            G[u][cur] = G[cur][u] = true;
            prev = cur;
        }
    }
}
int calc(int size){
    int ans = 0;
    for(int r=0;r+size<N;++r)for(int c=0;c+size<N;++c){
        int a0 = tr(r,c);
        int a1 = tr(r,c+size);
        int a2 = tr(r+size,c+size);
        int a3 = tr(r+size,c);
        if ( G[a0][a1] && G[a1][a2] && G[a2][a3] && G[a3][a0] ) ++ans;
    }
    return ans;
}

int main(){
    for(int kase=1;read();++kase){
        preProc();

        if ( kase > 1 ) printf("\n**********************************\n\n");
        printf("Problem #%d\n\n",kase);

        bool flag = true;
        for(int size=1;size<=N;++size){
            int ans = calc(size);
            if ( ans ) flag = false, printf("%d square (s) of size %d\n",ans,size);
        }

        if ( flag ) printf("No completed squares can be found.\n");
    }
    return 0;
}