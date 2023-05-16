/*
  给定若干个1-9的数字，问有多少个不同的三元组满足x+y=z
  搜索
  最多能够有36个算式
  112 123 134 145 156 167 178 189
  213 224 235 246 257 268 279
  314 325 336 347 358 369
  ...
*/
#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;

int Cnt[10];
int Ans = 0, Max=0;

int Eq[36][3]={
   1,1,2, 1,2,3, 1,3,4, 1,4,5, 1,5,6, 1,6,7, 1,7,8,1,8,9,
   2,1,3, 2,2,4, 2,3,5, 2,4,6, 2,5,7, 2,6,8, 2,7,9,
   3,1,4, 3,2,5, 3,3,6, 3,4,7, 3,5,8, 3,6,9,
   4,1,5, 4,2,6, 4,3,7, 4,4,8, 4,5,9,
   5,1,6, 5,2,7, 5,3,8, 5,4,9,
   6,1,7, 6,2,8, 6,3,9,
   7,1,8, 7,2,9,
   8,1,9
};

bool Flag[36];

//pos表示从当前开始搜
void dfs(int pos){
    if(pos==36){
        return;
    }
    for(int i=pos;i<36;++i){
        if(36-i+Ans<Max) break;

        int x = Eq[i][0];
        int y = Eq[i][1];
        int z = Eq[i][2];

        if((x!=y&&Cnt[x]&&Cnt[y]&&Cnt[z])||(x==y&&Cnt[x]>=2&&Cnt[z])){
            ++Ans;
            if(Max<Ans)Max=Ans;
            --Cnt[x],--Cnt[y],--Cnt[z];
            dfs(i+1);
            ++Cnt[x],++Cnt[y],++Cnt[z];
            --Ans;
        }
    }
}

int proc(){
    fill(Flag,Flag+36,false);
    Ans = Max = 0;

    dfs(0);
    return Max;
}
int main(){
    //freopen("1.txt","r",stdin);
    int nofkase;
    scanf("%d",&nofkase);
    for(int kase=1;kase<=nofkase;++kase){
        for(int i=1;i<=9;++i)scanf("%d",Cnt+i);
        printf("Case #%d: %d\n",kase,proc());
    }
    return 0;
}
