//给定位置，问最少放几个皇后可以全部攻击到指定位置
//修改为判定性问题，进行搜索
#include <stdio.h>
#include <string.h>
using namespace std;

int N,M,Ans;
char A[12][12];
bool Flag[4][30];//行列主次对角线
int Row[110];
int Col[110];
int XCnt;
bool read(){
    if ( EOF == scanf("%d%d",&N,&M) || 0 ==  N ) return false;

    memset(Flag,0,sizeof(Flag));
    XCnt = 0;Ans = 5;
    for(int i=0;i<N;++i){
        scanf("%s",A[i]);
        for(char *p=A[i],j=0;*p;++p,++j)if ( 'X' == *p ){
            Row[XCnt] = i;
            Col[XCnt++] = j;
        }
    }
    return true;
}

inline bool isOK(){
    //对每一个X
    for(int i=0;i<XCnt;++i){
        //如果四个方向均没有攻击到，则没有被攻击到
        if ( !Flag[0][Row[i]] && !Flag[1][Col[i]] && !Flag[2][Row[i]-Col[i]+M] && !Flag[3][Row[i]+Col[i]] ) return false;
    }
    return true;
}

//dfs解决判定性问题，用maxAns数量的皇后能发攻击到所有指定位置
//depth表示已经放置的皇后数量，pos表示当前可放置的位置
bool dfs(int depth,int pos,int maxAns){
    if ( depth == maxAns ){
        return isOK();
    }

    for(int i=pos;i<N*M;++i){
        int r = i / M;
        int c = i % M;

        //在rc位置放置皇后
        bool flag0 = Flag[0][r];
        bool flag1 = Flag[1][c];
        bool flag2 = Flag[2][r-c+M];
        bool flag3 = Flag[3][r+c];

        Flag[0][r] = Flag[1][c] = Flag[2][r-c+M] = Flag[3][r+c] = true;

        bool t = dfs(depth+1,i,maxAns);
        if ( t ) return true;

        //还原
        Flag[0][r] = flag0;
        Flag[1][c] = flag1;
        Flag[2][r-c+M] = flag2;
        Flag[3][r+c] = flag3;
    }
    return false;
}

int main(){
    //freopen("1.txt","r",stdin);
    for(int kase=1;read();++kase){
        for(Ans=0;;++Ans)if(dfs(0,0,Ans))break;
        printf("Case %d: %d\n",kase,Ans);
    }
    return 0;
}
