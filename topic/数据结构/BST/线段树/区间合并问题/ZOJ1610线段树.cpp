/*
    在数轴上，一次给一个线段涂上颜色
    后面的颜色会覆盖前面的颜色
    问最后每个颜色的线段有多少个

    显然是成段更新，线段树
*/

#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

int const SIZE = 8010;

inline int lson(int x){return x<<1;}
inline int rson(int x){return lson(x)|1;}

int ST[SIZE<<2];//段数
int L[SIZE<<2],R[SIZE<<2];//左右边界的颜色
int Lazy[SIZE<<2];

struct _t{
    int cnt;
    int left;
    int right;
    _t(int aa=0,int bb=0,int cc=0):cnt(aa),left(bb),right(cc){}
};

inline void _pushUp(int t){
    ST[t] = ST[lson(t)] + ST[rson(t)] + (R[lson(t)]==L[rson(t)]?-1:0);
    L[t] = L[lson(t)];
    R[t] = R[rson(t)];
}

inline void _pushDown(int t){
    if ( Lazy[t] ){
        ST[lson(t)] = ST[rson(t)] = 1;
        Lazy[lson(t)] = L[lson(t)] = R[lson(t)] = Lazy[t];
        Lazy[rson(t)] = L[rson(t)] = R[rson(t)] = Lazy[t];
        Lazy[t] = 0;
    }
}

_t query(int t,int s,int e,int a,int b){
    if ( a <= s && e <= b ){
        return _t(ST[t],L[t],R[t]);
    }

    _pushDown(t);
    int mid = (s+e) >> 1;
    _t lans,rans;
    if ( a <= mid ) {
        lans = query(lson(t),s,mid,a,b);
        if ( b <= mid ) return lans;
    }
    if ( mid < b ){
        rans = query(rson(t),mid+1,e,a,b);
        if ( mid < a ) return rans;
    }
    return _t(lans.cnt+rans.cnt+(lans.right==rans.left?-1:0),lans.left,rans.right);
}

void modify(int t,int s,int e,int a,int b,int color){
    if ( a <= s && e <= b ){
        ST[t] = 1;
        Lazy[t] = L[t] = R[t] = color;
        return;
    }

    _pushDown(t);//?
    int mid = ( s + e ) >> 1;
    if ( a <= mid ) modify(lson(t),s,mid,a,b,color);
    if ( mid < b ) modify(rson(t),mid+1,e,a,b,color);
    _pushUp(t);
}

int Ans[SIZE];
int main(){
    //freopen("1.txt","r",stdin);

    int n,a,b,color;
    while( 1 == scanf("%d",&n) ){
        memset(ST,0,sizeof(ST));
        memset(L,0,sizeof(L));
        memset(R,0,sizeof(R));
        memset(Lazy,0,sizeof(Lazy));

        int first = 10000, last = -1;

        while(n--){
            scanf("%d%d%d",&a,&b,&color);

            //使用左闭右开表示线段
            ++a;++color;
            //++b,--b;
            first = min(first,a);
            last = max(last,b);

            modify(1,1,8001,a,b,color);
        }

        //检查每种颜色的段数
        fill(Ans,Ans+SIZE,0);
        int color = 0, cnt = 0;
        for(int i=first;i<=last;++i){
            _t ans = query(1,1,8001,first,i);

            if ( ans.cnt > cnt && ans.right != 0 ){//加入了新的有颜色的一段
                cnt = ans.cnt;
                ++Ans[ans.right];
            }
        }

        for(int i=1;i<=8001;++i)if(Ans[i])printf("%d %d\n",i-1,Ans[i]);
        putchar('\n');
    }
    return 0;
}


