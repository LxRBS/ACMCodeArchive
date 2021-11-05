#include <cstdio>
#include <cstring>

int const ACROSS = 0x100;
int const DOWN = 0x200;

int N,M;
char A[10][11];
int B[10][10];

inline bool isAcrossStart(int r,int c){
    return 0 == c || '*' == A[r][c-1];
}

inline bool isDownStart(int r,int c){
    return 0 == r || '*' == A[r-1][c];
}

//读入数据，并且顺便记录一下每个位置是否能够作为横向单词或者纵向单词的开头
bool read(){
    scanf("%d",&N);
    if ( 0 == N ) return false;

    scanf("%d",&M);
    for(int i=0;i<N;++i)scanf("%s",A[i]);

    memset(B,0,sizeof(B));
    int k = 0;
    for(int i=0;i<N;++i)for(int j=0;j<M;++j){
        if ( '*' == A[i][j] ) continue;
        int a = isAcrossStart(i,j) ? ACROSS : 0;
        int b = isDownStart(i,j) ? DOWN : 0;
        int c = a | b;
        if ( c ){
            B[i][j] = c | ++k;
        }
    }
    return true;
}
//输出以(r,c)位置开头的横向单词
void outAcross(int r,int c){
    while( c < M && A[r][c] != '*' ) printf("%c",A[r][c++]);
}
//输出所有的横向单词
void doAcross(){
    printf("Across\n");

    for(int i=0;i<N;++i)for(int j=0;j<M;++j){
        if ( 0 == ( B[i][j] & ACROSS ) ) continue;

        int sn = B[i][j] & 0xFF;
        printf("%3d.",sn);
        outAcross(i,j);
        printf("\n");
    }
}
void outDown(int r,int c){
    while( r < N && A[r][c] != '*' ) printf("%c",A[r++][c]);
}
void doDown(){
    printf("Down\n");

    for(int i=0;i<N;++i)for(int j=0;j<M;++j){
        if ( 0 == ( B[i][j] & DOWN ) ) continue;

        int sn = B[i][j] & 0xFF;
        printf("%3d.",sn);
        outDown(i,j);
        printf("\n");
    }
}
int main(){
    //freopen("1.txt","r",stdin);
    for(int kase=1;read();++kase){
        if ( kase > 1 ) printf("\n");
        printf("puzzle #%d:\n",kase);
        doAcross();
        doDown();
    }
    return 0;
}
