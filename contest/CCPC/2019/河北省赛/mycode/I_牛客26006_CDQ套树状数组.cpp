/**
  平面上一堆星星，每一个有一个坐标和初始亮度
  然后亮度随着时间做周期性变化，到MAX以后从0开始
  给定Q个询问，每次问ti时刻矩形中星星的亮度总和
  首先，至少是二维偏序，然后在x,y以内，
  时刻小的与时刻大的均需要统计，三维偏序，CDQ分治
  排序的时候要注意
*/
#include<bits/stdc++.h>
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

const int SIZE = 250500;
llt Cnt[SIZE], Sum[SIZE];

llt Time[SIZE];//离散化数组
int TIdx;//离散化用

inline int lowbit(int x){return x&-x;}
void modify(llt *a, int i, llt x){while(i <= TIdx) a[i] += x, i += lowbit(i);return;}
llt query(llt *a, int i){llt res = 0;while(i) res += a[i], i -= lowbit(i); return res;}


int N, Q, QCnt;
llt MAX, Ans[SIZE];
struct cdq_t{
    int x, y, op;//op代表操作类型，id代表一个询问的初始位置
    llt time, pos;//pos为离散化后的查询点/修改点
    llt *pans;
    bool operator < (const cdq_t& a)const {
        if(x!=a.x) return x < a.x;
        if(y!=a.y) return y < a.y;
        //if(time!=a.time) return time < a.time; // 这一句不能加
        return op < a.op;//如果x坐标相同，插入要优先于查询
    }
}A[SIZE], B[SIZE];


void CDQ(int s, int e){
    if(s>=e) return;

    int mid = (s+e)>>1;
    CDQ(s, mid); CDQ(mid+1, e);

    int a = s, b = mid+1, t = s;
    while(a <= mid && b <= e){
        if(A[a].y <= A[b].y){
            if(A[a].op == -2){//加入星星
                modify(Cnt, A[a].pos, 1);
                modify(Sum, A[a].pos, A[a].time);
            }
            B[t++] = A[a++];
        }
        else{
            if(A[b].op != -2){
                llt v = query(Sum, TIdx);//总的初始价值
                llt cnt1 = query(Cnt, TIdx);//总的星星
                llt cnt2 = query(Cnt, A[b].pos);//在[0, MAX-time]的星星
                //Ans[A[b].id] += A[b].op*( v + cnt1*(A[b].time) - (cnt1 - cnt2)*(MAX+1) );
                //*A[b].pans += A[b].op*( v + cnt1*(A[b].time) - (cnt1 - cnt2)*(MAX+1) );
                *A[b].pans += A[b].op * (v + cnt2*MAX-cnt1*A[b].time-(cnt1-cnt2));
            }
            B[t++] = A[b++];
        }
    }
    while(b <= e){//先把查询处理完
        if(A[b].op != -2){
            llt v = query(Sum, TIdx);
            llt cnt1 = query(Cnt, TIdx), cnt2 = query(Cnt, A[b].pos);
            //Ans[A[b].id] += A[b].op*( v + cnt1*(A[b].time) - (cnt1 - cnt2)*(MAX+1) );
            //*A[b].pans += A[b].op*( v + cnt1*(A[b].time) - (cnt1 - cnt2)*(MAX+1) );
            *A[b].pans += A[b].op * (v + cnt2*MAX-cnt1*A[b].time-(cnt1-cnt2));
        }
        B[t++] = A[b++];
    }
    for(int i = s; i < a; ++i){//删除之前的更改
        if(A[i].op == -2){
            modify(Cnt, A[i].pos, -1);
            modify(Sum, A[i].pos, -A[i].time);
        }
    }
    while(a <= mid) B[t++] = A[a++];//再把左边剩余的处理完
    copy(B+s, B+e+1, A+s);
}


int main(){
    //freopen("1.txt","r",stdin);
    N = getUnsigned();
    Q = getUnsigned();
    MAX = getUnsigned();
	TIdx = 0;
	for(int i = 1; i <= N; ++i){
        A[i].x = getUnsigned();
        A[i].y = getUnsigned();
        Time[TIdx++] = A[i].time = getUnsigned() - MAX;
        A[i].op = -2;
	}
	QCnt = N;
	for(int t,x1,y1,x2,y2,i = 1; i <= Q; ++i){
        t = getUnsigned();
        x1 = getUnsigned();
        y1 = getUnsigned();
        x2 = getUnsigned();
        y2 = getUnsigned();

        A[++QCnt].pans = Ans+i, A[QCnt].op = 1, A[QCnt].x = x1 - 1, A[QCnt].y = y1 - 1, A[QCnt].time = -t;
        A[++QCnt].pans = Ans+i, A[QCnt].op = 1, A[QCnt].x = x2, A[QCnt].y = y2, A[QCnt].time = -t;
        A[++QCnt].pans = Ans+i, A[QCnt].op = -1, A[QCnt].x = x2, A[QCnt].y = y1 - 1, A[QCnt].time = -t;
        A[++QCnt].pans = Ans+i, A[QCnt].op = -1, A[QCnt].x = x1 - 1, A[QCnt].y = y2, A[QCnt].time = -t;
        Time[TIdx++] =  - t;
	}

	sort(A+1, A+QCnt+1);
	sort(Time, Time+TIdx);
	TIdx = unique(Time,Time+TIdx) - Time;
	for(int i = 1; i <= QCnt; ++i) A[i].pos = lower_bound(Time,Time+TIdx, A[i].time) - Time + 1;
	CDQ(1, QCnt);
	for(int i = 1; i <= Q; ++i) printf("%lld\n", Ans[i]);
}

