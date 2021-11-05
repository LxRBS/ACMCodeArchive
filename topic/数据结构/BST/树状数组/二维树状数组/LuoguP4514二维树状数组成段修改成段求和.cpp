/*
     N×M的矩阵，2种操作成段修改成段更新
*/
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

int getInt(){
	int sgn = 1;
	char ch = getchar();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = getchar();
	if ( '-' == ch ) {sgn = 0;ch=getchar();}

	int ret = (int)(ch-'0');
	while( '0' <= (ch=getchar()) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return sgn ? ret : -ret;
}

int const SIZE = 2050;
int C[4][SIZE][SIZE];
int N,M;

inline int lowbit(int x){return x&-x;}

//在第idx个C上面做查询
int query(int r,int c,int idx){
    int sum = 0;
    for(;r;r-=lowbit(r))for(int j=c;j;j-=lowbit(j))sum += C[idx][r][j];
    return sum;
}
//在第idx个C上面做修改
void modify(int r,int c,int delta,int idx){
    for(;r<=N;r+=lowbit(r))for(int j=c;j<=M;j+=lowbit(j))C[idx][r][j] += delta;
}
//源数组的[(r1,c1),(r2,c2)]区间全部增加delta
void modify(int r1,int c1,int r2,int c2,int delta){
    //相当于差分数组上的4个单点操作
    //但是要同时修改4个树状数组，所以有16个操作
    //修改差分数组
    modify(r1,c1,delta,0);modify(r2+1,c2+1,delta,0);
    modify(r1,c2+1,-delta,0);modify(r2+1,c1,-delta,0);
    //修改(i-1)×(j-1)×D
    modify(r1,c1,delta*(r1-1)*(c1-1),1);modify(r2+1,c2+1,delta*r2*c2,1);
    modify(r1,c2+1,-delta*(r1-1)*c2,1);modify(r2+1,c1,-delta*r2*(c1-1),1);
    //修改(i-1)×D
    modify(r1,c1,delta*(r1-1),2);modify(r2+1,c2+1,delta*r2,2);
    modify(r1,c2+1,-delta*(r1-1),2);modify(r2+1,c1,-delta*r2,2);
    //修改(j-1)×D
    modify(r1,c1,delta*(c1-1),3);modify(r2+1,c2+1,delta*c2,3);
    modify(r1,c2+1,-delta*c2,3);modify(r2+1,c1,-delta*(c1-1),3);
}
//查询源数组的[(1,1),(r,c)]区间和
int query(int r,int c){
    return r * c * query(r,c,0) - c * query(r,c,2)
         + query(r,c,1) - r * query(r,c,3);
}
//查询源数组的[(r1,c1),(r2,c2)]区间和
int query(int r1,int c1,int r2,int c2){
    return query(r2,c2) - query(r2,c1-1) + query(r1-1,c1-1) - query(r1-1,c2);
}
int main(){
    //freopen("1.txt","r",stdin);
    char cmd[3];
    scanf("%s",cmd);
    N = getInt(); M = getInt();
    int r1,c1,r2,c2;
    while(EOF!=scanf("%s",cmd)){
        r1=getInt();c1=getInt();r2=getInt();c2=getInt();
        if('k'==*cmd){
            printf("%d\n",query(r1,c1,r2,c2));
        }else{
            modify(r1,c1,r2,c2,getInt());
        }
    }
    return 0;
}
