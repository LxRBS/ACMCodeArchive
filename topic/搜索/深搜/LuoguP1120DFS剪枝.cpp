/**
   若干根同样长的小木棍，砍成N段
   给定N段的长度，求原长的最小可能
*/
#include <bits/stdc++.h>
using namespace std;

int N,Sum;
int A[100];
int Length,Cnt;
bool Ans;
int TT;
//Flag[i]表示第i个棍是否使用
bool Flag[100];
//Next[i]表示接下来的第一个与i长度不一样的棍的编号
int Next[100];

//一共要拼接Cnt个槽，槽长度为Length
//idx表示当前拼接的槽编号，从0开始
//left表示当前槽剩余的长度
//start表示需要搜索的木棍的起始编号
void dfs(int idx,int left,int start){
    if(idx==Cnt){Ans=true;return;}

    int i = start;
    while(i<N){
        if(Flag[i]){
            ++i;
            continue;
        }
        
        //如果拼上以后，剩下的比A[N-1]还要短 ，不能拼
        if(((TT=left-A[i])!=0&&TT<A[N-1])) {
            i = Next[i];//当前长度不能用，直接到下一个长度
            continue;
        }
        //递归
        Flag[i] = true;
        if(TT)dfs(idx,TT,i+1);//直接往后搜木棍
        else dfs(idx+1,Length,0);//从头开始
        if(Ans) return;
        //还原
        Flag[i] = false;
        //如果left==Length，又不能拼接成功，则说明肯定是之前有问题
        //如果left==A[i]，又不能拼接成功，则说明之前肯定有问题
        if(left==Length||left==A[i]) return;
        i=Next[i];
    }
}

//检查N个长度是否能够拼成cnt个length长度
bool check(int length,int cnt){
    Length = length;
    Cnt = cnt;
    Ans = false;
    dfs(0,Length,0);
    return Ans;
}

int f(){
    for(int i=A[0];i<=Sum/2;++i){
        if(0==Sum%i&&check(i,Sum/i))return i;
    }
    return Sum;
}
int main(){
    //freopen("1.txt","r",stdin);
    scanf("%d",&N);
    int k = 0;
    for(int i=0;i<N;++i){
        int a;
        scanf("%d",&a);
        if(a<=50)A[k++]=a;
    }
    N=k;
    //从大到小排序，先排大的
    sort(A,A+N,greater<int>());
    for(int i=0;i<N;++i){
        Next[i] = upper_bound(A,A+N,A[i],greater<int>()) - A;
    }
    Sum = accumulate(A,A+N,0);
    //答案必然在A[0]到Sum之间
    printf("%d\n",f());
    return 0;
}
