/*
   1 a:找一段空间有连续a个空，分配出去
   2 a b: 从a开始的b个位置回收
*/

#include <stdio.h>

int const SIZE = 50010;

//ST[t]表示t节点中最长的可用空间
int ST[SIZE<<2];

//Start[t]表示最长可用空间的起点
int Start[SIZE<<2];

//Front[t]表示t的最左边连续区间的长度
int Front[SIZE<<2];

//Back[t]表示t的最右边连续区间的长度
int Back[SIZE<<2];
//
int Lazy[SIZE<<2];

inline int lson(int t){return t<<1;}
inline int rson(int t){return lson(t)|1;}

inline void _pushUp(int t,int s,int e){
    int left = ST[lson(t)];
    int right = ST[rson(t)];
    int mid = Back[lson(t)] + Front[rson(t)];

    int const m = ( s + e ) >> 1;
    if(left>=mid&&left>=right){
        ST[t] = left;
        Start[t] = Start[lson(t)];
    }else if(mid>left&&mid>=right){
        ST[t] = mid;
        Start[t] = m - Back[lson(t)] + 1;
    }else{
        ST[t] = right;
        Start[t] = Start[rson(t)];
    }

    Front[t] = Front[lson(t)];
    if(m-s+1==Front[lson(t)]) Front[t] += Front[rson(t)];

    Back[t] = Back[rson(t)];
    if(e-m==Back[rson(t)]) Back[t] += Back[lson(t)];
}

inline void _pushDown(int t,int s,int e){
    if(1==Lazy[t]){//1表示分配
        int son = lson(t);
        ST[son] = Start[son] = Front[son] = Back[son] = 0;//全都分配出去了，空闲长度为0
        Lazy[son] = 1;

        son = rson(t);
        ST[son] = Start[son] = Front[son] = Back[son] = 0;
        Lazy[son] = 1;
    }else if(2==Lazy[t]){//2表示回收
        int const m = ( s + e ) >> 1;
        int son = lson(t);
        ST[son] = Front[son] = Back[son] = m - s + 1;
        Start[son] = s;
        Lazy[son] = 2;

        son = rson(t);
        ST[son] = Front[son] = Back[son] = e - m;
        Start[son] = m + 1;
        Lazy[son] = 2;
    }
    Lazy[t] = 0;
}

void build(int t,int s,int e){
    Lazy[t] = 0;
    if ( s == e ){
        ST[t] = Front[t] = Back[t] = 1;
        Start[t] = s;
        return;
    }

    int const m = ( s + e ) >> 1;
    build(lson(t),s,m);
    build(rson(t),m+1,e);
    _pushUp(t,s,e);
}

//返回有连续length长度空闲空间的最小起始点
int query(int t,int s,int e,int length){
    if(ST[t]<length){
        return 0;
    }else if(ST[t]==length){
        return Start[t];
    }

    _pushDown(t,s,e);
    int const m = ( s + e ) >> 1;
    //左儿子区间有答案
    if(ST[lson(t)]>=length)return query(lson(t),s,m,length);
    //如果答案在左右儿子之间
    if(Back[lson(t)]+Front[rson(t)]>=length) return m - Back[lson(t)] + 1;
    return query(rson(t),m+1,e,length);
}

//op为1表示分配，为2表示回收
//对源数组[a, b]区间做op操作
void modify(int t,int s,int e,int a,int b,int op){
    if(a<=s&&e<=b){
        Lazy[t] = op;
        if(1==op){
            ST[t] = Start[t] = Front[t] = Back[t] = 0;
        }else{
            ST[t] = Front[t] = Back[t] = e - s + 1;
            Start[t] = s;
        }
        return;
    }

    _pushDown(t,s,e);
    int const m = ( s + e ) >> 1;
    if(a<=m)modify(lson(t),s,m,a,b,op);
    if(m<b)modify(rson(t),m+1,e,a,b,op);
    _pushUp(t,s,e);
}

int N,M;
int main(){
    //freopen("1.txt","r",stdin);
    scanf("%d%d",&N,&M);
    build(1,1,N);

    int op,a,b;
    while(M--){
        scanf("%d%d",&op,&a);

        if(1==op){
            int ret = query(1,1,N,a);
            printf("%d\n",ret);
            if(ret){
                b = ret + a - 1;
                modify(1,1,N,ret,b,1);
            }
        }else{
            scanf("%d",&b);
            b = a + b - 1;
            modify(1,1,N,a,b,2);
        }

    }
    return 0;
}
