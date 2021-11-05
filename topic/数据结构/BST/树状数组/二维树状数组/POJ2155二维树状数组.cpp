/*
     N×N的矩阵，2种操作
     C x1 y1 x2 y2：子矩阵内的所有元素改变状态
     Q r y：问(r,y)位置上的元素值
*/
#include <stdio.h>
#include <string.h>

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

int const SIZE = 1020;
int C[SIZE][SIZE];//树状数组

int N,M,Q;

inline int lowbit(int x){return x&-x;}

int query(int r,int c){
    int ans = 0;
    for(;r;r-=lowbit(r))for(int j=c;j;j-=lowbit(j))ans^=C[r][j];
    return ans;
}

void modify(int r, int c, int delta){
    for(;r<=N;r+=lowbit(r))for(int j=c;j<=M;j+=lowbit(j))C[r][j]^=delta;
}

int main(){
    //freopen("1.txt","r",stdin);
    int nofkase=getUnsigned();

    char cmd[3];
    int x1,x2,y1,y2;
    for(int kase=1;kase<=nofkase;++kase){
        N=M=getUnsigned();
        Q=getUnsigned();

        //初始全0，差分数组也全是0
        memset(C,0,sizeof(C));

        if ( kase > 1 ) putchar('\n');

        while(Q--){
            scanf("%s",cmd);
            x1 = getUnsigned();
            y1 = getUnsigned();
            if ( 'C' == *cmd ){
                x2 = getUnsigned();
                y2 = getUnsigned();
                //4个单点操作
                modify(x1,y1,1);
                modify(x2+1,y1,1);
                modify(x1,y2+1,1);
                modify(x2+1,y2+1,1);
            }else{
                printf("%d\n",query(x1,y1));
            }
        }
    }
    return 0;
}
