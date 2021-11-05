/*
    在数轴上，一次给一个线段涂上颜色
    后面的颜色会覆盖前面的颜色
    问最后能看到多少个颜色

    显然是成段更新，线段树
    区间范围是1千万，需要离散化
    另外注意位置编号的含义
*/

#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <numeric>
using namespace std;

int const SIZE = 20010;

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

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

int N,NN;
int T[SIZE];
int A[SIZE],B[SIZE];

bool read(){
    N = getUnsigned();
    for(int i=0;i<N;++i) T[i+i] = A[i] = getUnsigned(), T[i+i+1] = B[i] = getUnsigned() + 1;

    sort(T,T+N+N);
    NN = unique(T,T+N+N) - T;

    //离散化
    for(int i=0;i<N;++i){
        pair<int*,int*> pp = equal_range(T,T+NN,A[i]);
        A[i] = pp.first - T + 1;

        pp = equal_range(T,T+NN,B[i]);
        B[i] = pp.first - T/* + 1*/;//左闭右开，就不用加1了
    }

    fill(ST,ST+NN*4,0);
    fill(Lazy,Lazy+NN*4,0);
    fill(L,L+NN*4,0);
    fill(R,R+NN*4,0);

    return true;
}

int Flag[SIZE];
int main(){
    //freopen("1.txt","r",stdin);

    int nofkase = getUnsigned();
    while(nofkase--){
        read();

        //成段更新
        for(int i=0;i<N;++i){
            modify(1,1,NN,A[i],B[i],i+1);
        }

        //检查结果
        fill(Flag,Flag+N+1,0);
        int cnt = 0;
        for(int i=1;i<=NN;++i){
            _t ans = query(1,1,NN,1,i);

            if ( ans.cnt > cnt && ans.right != 0 ){
                cnt = ans.cnt;
                Flag[ans.right] = 1;
            }
        }

        printf("%d\n",accumulate(Flag+1,Flag+N+1,0));
    }
    return 0;
}


