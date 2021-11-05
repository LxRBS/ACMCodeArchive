/**
  二维偏序，用CDQ分治实现
*/
#include <stdio.h>
#include <algorithm>
using namespace std;

char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)

int getInt(){
	int sgn = 1;
	char ch = __hv007();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = __hv007();
	if ( '-' == ch ) {sgn = 0;ch=__hv007();}

	int ret = (int)(ch-'0');
	while( '0' <= (ch=__hv007()) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return sgn ? ret : -ret;
}

int const SIZE = 500010;
typedef long long llt;

struct cdq_t{
    int idx;
    int x;
    int y;
    cdq_t(int a=0,int b=0,int c=0):idx(a),x(b),y(c){}
}A[SIZE*3], B[SIZE*3];

int N, M, Q, ACnt;
int Ans[SIZE], Level[SIZE];
void disp(int,int);

void CDQ(int s, int e){
    if(s>=e) return;

    int mid = (s+e)>>1;
    CDQ(s, mid);
    CDQ(mid+1, e);

    int a = s, b = mid+1, t = s, sum = 0;
    while(a<=mid && b<=e){
        if(A[a].x<=A[b].x){
            B[t++] = A[a++];
        }else{
            Level[A[b].idx] += a - s;
            B[t++] = A[b++];
        }
    }
    /// 如果a还有剩余
    while(a<=mid){
        B[t++] = A[a++];
    }
    /// 右边还有剩余，还需考虑
    while(b<=e){
        Level[A[b].idx] += a - s;
        B[t++] = A[b++];
    }
    /// 将其按照位置变得有序
    copy(B+s, B+e+1, A+s);
}

void disp(int s, int e){
    printf("[%d, %d]\n", s, e);
    for(int i=s;i<=e;++i){
        printf("%d: %d %d %d\n", i, A[i].idx, A[i].x, A[i].y);
    }
    for(int i=1;i<=ACnt;++i){
        printf("%d: %d\n", i, Ans[i]);
    }
}
int main(){
    //freopen("1.txt","r",stdin);
    N = Q = getInt();
    for(int i=1;i<=N;++i){
        A[i].idx = i;
        A[i].x = getInt();
        A[i].y = getInt();
    }

    CDQ(1, Q);
    for(int i=1;i<=N;++i)++Ans[Level[i]];
    for(int i=0;i<N;++i)printf("%d\n", Ans[i]);
    return 0;
}
