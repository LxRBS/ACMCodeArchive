/*
    每一个操作将一段球改成白色或者黑色
    初始全黑
    问最后最长的白球序列的始末位置
    离散化，将每个点的两边的端点均加入
    例如指令是100 1000 w
    则将99 100 101 999 1000和1001均加入离散化
*/
#include <stdio.h>
#include <algorithm>
using namespace std;

int const SIZE = 2001 * 6;

inline int lson(int t){return t<<1;}
inline int rson(int t){return lson(t)|1;}

int ST[SIZE<<2];//最小值，黑色为0，白色为1
int Lazy[SIZE<<2];

void _pushUp(int t){
    ST[t] = min(ST[lson(t)],ST[rson(t)]);
}

void _pushDown(int t){
    if('w'==Lazy[t]){//全改成1
        ST[lson(t)] = ST[rson(t)] = 1;
        Lazy[lson(t)] = Lazy[rson(t)] = 'w';
    }else if('b'==Lazy[t]){//全改成0
        ST[lson(t)] = ST[rson(t)] = 0;
        Lazy[lson(t)] = Lazy[rson(t)] = 'b';
    }

    Lazy[t] = 0;
}

void modify(int t,int s,int e,int a,int b,int color){
    if(a<=s&&e<=b){
        ST[t] = (color == 'w' ? 1 : 0);
        Lazy[t] = color;
        return;
    }

    _pushDown(t);
    int const m = (s+e)>>1;
    if(a<=m) modify(lson(t),s,m,a,b,color);
    if(m<b) modify(rson(t),m+1,e,a,b,color);
    _pushUp(t);
}

int query(int t,int s,int e,int pos){
    if(s==e){
        return ST[t];
    }

    _pushDown(t);
    int const m = (s+e)>>1;
    if(pos<=m) return query(lson(t),s,m,pos);
    return query(rson(t),m+1,e,pos);
}

int A[SIZE],B[SIZE],Color[SIZE];
long long int T[SIZE];
int N,NN;
int main(){
    //freopen("1.std.in","r",stdin);
    while(EOF!=scanf("%d",&N)){
        NN=0;
        char s[3];
        for(int i=0;i<N;++i){
            scanf("%d%d%s",A+i,B+i,s);
            T[++NN] = A[i] - 1;
            T[++NN] = A[i];
            T[++NN] = A[i] + 1;
            T[++NN] = B[i] - 1;
            T[++NN] = B[i];
            T[++NN] = B[i] + 1;
            Color[i] = *s;
        }

        //离散化
        sort(T+1,T+NN+1);
        NN = unique(T+1,T+NN+1) - T;

        //不需要build，直接初始化
        //也不需要初始化，只有一个case

        for(int i=0;i<N;++i){
            int a = lower_bound(T+1,T+NN,A[i]) - T;
            int b = lower_bound(T+1,T+NN,B[i]) - T;
            modify(1,1,NN-1,a,b,Color[i]);
        }

        //查询
        int cnt = 0,start;
        for(int i=1;;){
            while(i<NN&&0==query(1,1,NN-1,i)) ++i;
            if(i==NN) break;

            //i是白球
            int left = i;
            while(i<NN&&1==query(1,1,NN-1,i)) ++i;
            int right = i - 1;
            //从left到right是白球
            int tmp = T[right] - T[left] + 1;
            if(cnt<tmp){
                cnt = tmp;
                start = T[left];
            }

        }
        if(cnt)printf("%d %d\n",start,start+cnt-1);
        else printf("Oh, my god\n");//测试数据中其实并没有这个分支
    }
    return 0;
}
