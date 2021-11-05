/**
    四维偏序模板题
    按顺序给定操作
    1表示插入
    2表示查询
    对每一个2操作，询问给定范围内有多少个已经插入的点
    CDQ套树状数组
*/
#include <bits/stdc++.h>
using namespace std;

char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)

int getUnsigned(){
	char ch = __hv007();
	while( ch < '0' || ch > '9' ) ch = __hv007();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = __hv007() ) && ch <= '9' ) ret = (ret<<1) + (ret<<3) + (int)(ch-'0');
	return ret;
}


typedef long long llt;
int const SIZE = 50010 * 8;

int WCnt;
int BIT[SIZE];

inline int lowbit(int x){return x & -x;}
void modify(int pos, int delta){
    for(;pos<=WCnt;pos+=lowbit(pos))BIT[pos] += delta;
}

int query(int pos){
    int ans = 0;
    for(;pos;pos-=lowbit(pos)) ans += BIT[pos];
    return ans;
}

struct cdq_t{
    int x, y, z;
    int op;
    int *pans;
    bool b;
}A[SIZE], B[SIZE], C[SIZE];


int Ans[SIZE], ACnt;
int N, Q, W[SIZE];

inline void mk8(int i){
    int xl = getUnsigned();
    int yl = getUnsigned();
    int zl = getUnsigned();
    int xr = getUnsigned();
    int yr = getUnsigned();
    int zr = getUnsigned();

    A[++Q].op = -1;
    A[Q].x = xl - 1;
    A[Q].y = yl - 1;
    A[Q].z = (W[WCnt++] = zl - 1);
    *(A[Q].pans = Ans + ACnt) = 0;

    A[++Q].op = 1;
    A[Q].x = xl - 1;
    A[Q].y = yl - 1;
    A[Q].z = W[WCnt++] = zr;
    *(A[Q].pans = Ans + ACnt) = 0;

    A[++Q].op = 1;
    A[Q].x = xl - 1;
    A[Q].y = yr;
    A[Q].z = zl - 1;
    *(A[Q].pans = Ans + ACnt) = 0;

    A[++Q].op = -1;
    A[Q].x = xl - 1;
    A[Q].y = yr;
    A[Q].z = zr;
    *(A[Q].pans = Ans + ACnt) = 0;

    A[++Q].op = 1;
    A[Q].x = xr;
    A[Q].y = yl - 1;
    A[Q].z = zl - 1;
    *(A[Q].pans = Ans + ACnt) = 0;

    A[++Q].op = -1;
    A[Q].x = xr;
    A[Q].y = yl - 1;
    A[Q].z = zr;
    *(A[Q].pans = Ans + ACnt) = 0;

    A[++Q].op = -1;
    A[Q].x = xr;
    A[Q].y = yr;
    A[Q].z = zl - 1;
    *(A[Q].pans = Ans + ACnt) = 0;

    A[++Q].op = 1;
    A[Q].x = xr;
    A[Q].y = yr;
    A[Q].z = zr;
    *(A[Q].pans = Ans + ACnt++) = 0;
}

void CDQ2(int s, int e){
    if(s>=e) return;

    int mid = (s + e) >> 1;
    CDQ2(s, mid); CDQ2(mid+1, e);

    int a = s, b = mid + 1, t = a;
    while(a<=mid&&b<=e){
        if(B[a].y<=B[b].y){
            if(B[a].b&&!B[a].op){
                modify(B[a].z, 1);
            }
            C[t++] = B[a++];
        }else{
            if(!B[b].b&&B[b].op){
                *B[b].pans += B[b].op * query(B[b].z);
            }
            C[t++] = B[b++];
        }
    }
    while(b<=e){
        if(!B[b].b&&B[b].op){
            *B[b].pans += B[b].op * query(B[b].z);
        }
        C[t++] = B[b++];
    }
    for(int i=s;i<a;++i){
        if(B[i].b&&!B[i].op){
            modify(B[i].z, -1);
        }
    }
    while(a<=mid){
        C[t++] = B[a++];
    }
    copy(C+s, C+e+1, B+s);
}

void CDQ(int s, int e){
    if(s>=e) return;

    int mid = (s + e) >> 1;
    CDQ(s, mid); CDQ(mid+1, e);

    int a = s, b = mid + 1, t = a;
    while(a<=mid&&b<=e){
        if(A[a].x<=A[b].x){
            B[t] = A[a++];
            B[t++].b = 1;
        }else{
            B[t] = A[b++];
            B[t++].b = 0;
        }
    }
    while(a<=mid){
        B[t] = A[a++];
        B[t++].b = 1;
    }
    while(b<=e){
        B[t] = A[b++];
        B[t++].b = 0;
    }

    copy(B+s, B+e+1, A+s);
    CDQ2(s, e);
}

int main(){
    //freopen("1.txt","r",stdin);
    int nofkase = getUnsigned();
    while(nofkase--){
        N = getUnsigned();
        ACnt = WCnt = Q = 0;

        for(int cmd,i=1;i<=N;++i){
            cmd = getUnsigned();
            if(1==cmd){
                A[++Q].x = getUnsigned();
                A[Q].y = getUnsigned();
                W[WCnt++] = A[Q].z = getUnsigned();
                A[Q].op = 0;

            }else{ // 变成8个操作
                mk8(i);
            }
        }

        /// 离散化z坐标
        sort(W, W+WCnt);
        WCnt = unique(W, W+WCnt) - W;
        for(int i=1;i<=Q;++i){
            A[i].z = lower_bound(W, W+WCnt, A[i].z) - W + 1;
        }

        CDQ(1, Q);
        for(int i=0;i<ACnt;++i)printf("%d\n", Ans[i]);
    }
    return 0;
}
