/**
   树状数组模板题，用CDQ分治实现
*/
#include <bits/stdc++.h>
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
    int type; // 124
    int pos;
    int val;
    cdq_t(int a=0,int b=0,int c=0):type(a),pos(b),val(c){}
}A[SIZE*3], B[SIZE*3];

int N, M, Q, ACnt;
int Ans[SIZE];
void disp(int,int);
void CDQ(int s, int e){
    if(s>=e) return;

    int mid = (s+e)>>1;
    CDQ(s, mid);
    CDQ(mid+1, e);

    int a = s, b = mid+1, t = s, sum = 0;
    while(a<=mid && b<=e){
        if(A[a].pos <= A[b].pos){ // 说明a位置在b位置左边
            if(A[a].type&1){ // 修改操作
                sum += A[a].val;
            }
            B[t++] = A[a++];
        }else{ // 说明a位置在b位置右边
            if(A[b].type&2){
                Ans[A[b].val] -= sum;
            }else if(A[b].type&4){
                Ans[A[b].val] += sum;
            }
            B[t++] = A[b++];
        }
    }
    /// 如果a还有剩余，就无所谓了
    while(a<=mid) B[t++] = A[a++];
    /// 右边还有剩余，还需考虑
    while(b<=e){
        if(A[b].type&2){
            Ans[A[b].val] -= sum;
        }else if(A[b].type&4){
            Ans[A[b].val] += sum;
        }
        B[t++] = A[b++];
    }
    /// 将其按照位置变得有序
    copy(B+s, B+e+1, A+s);
    //disp(s, e);
}

void disp(int s, int e){
    printf("[%d, %d]\n", s, e);
    for(int i=s;i<=e;++i){
        printf("%d: %d %d %d\n", i, A[i].type, A[i].pos, A[i].val);
    }
    for(int i=1;i<=ACnt;++i){
        printf("%d: %d\n", i, Ans[i]);
    }
}
int main(){
    //freopen("1.txt","r",stdin);
    N = getInt();
    M = getInt();
    for(int i=1;i<=N;++i){
        A[i] = cdq_t(1, i, getInt());
    }

    Q = N; ACnt = 0;
    for(int i=0;i<M;++i){
        if((A[++Q].type = getInt())&1){
            A[Q].pos = getInt();
            A[Q].val = getInt();
        }else{
            A[Q].pos = getInt() - 1;
            A[Q].val = ++ACnt;

            A[++Q].type = 4;
            A[Q].pos = getInt();
            A[Q].val = ACnt;
        }
    }

    CDQ(1, Q);
    for(int i=1;i<=ACnt;++i)printf("%d\n", Ans[i]);
    return 0;
}
