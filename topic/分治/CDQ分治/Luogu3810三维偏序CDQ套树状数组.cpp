/**
   三维偏序模板题，CDQ套树状数组
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

int const SIZE = 100030;
typedef long long llt;

inline int lowbit(int x){return x&-x;}


struct cdq_t{
    int idx;
    int x;
    int y;
    int z;
    int cnt;
    bool operator < (const cdq_t&rhs)const{
        return this->x < rhs.x || (this->x==rhs.x&&this->y<rhs.y)
            || (this->x==rhs.x&&this->y==rhs.y&&this->z<rhs.z)
            || (this->x==rhs.x&&this->y==rhs.y&&this->z==rhs.z&&this->idx<rhs.idx);
    }
}A[SIZE], B[SIZE];

int N, Q, K;
int C[SIZE+SIZE];
int Ans[SIZE];

int query(int pos){
    int ans = 0;
    for(;pos;pos-=lowbit(pos))ans+=C[pos];
    return ans;
}

void modify(int pos, int delta){
    for(;pos<=K;pos+=lowbit(pos)) C[pos] += delta;
}

void CDQ(int s, int e){
    if(s>=e) return;

    int mid = (s+e) >> 1;
    CDQ(s, mid); CDQ(mid+1, e);

    int a = s, b = mid+1, t = s;
    while(a<=mid&&b<=e){
        if(A[a].y<=A[b].y){
            modify(A[a].z, A[a].cnt);
            B[t++] = A[a++];
        }else{
            Ans[A[b].idx] += query(A[b].z);
            B[t++] = A[b++];
        }
    }
    while(a<=mid){
        modify(A[a].z, A[a].cnt);
        B[t++] = A[a++];
    }
    while(b<=e){
        Ans[A[b].idx] += query(A[b].z);
        B[t++] = A[b++];
    }

    /// 清空树状数组，但是不能直接fill
    for(int i=s;i<=mid;++i){
        modify(A[i].z, -A[i].cnt);
    }

    copy(B+s, B+e+1, A+s);
}

int Cnt[SIZE];
int main(){
    //freopen("1.txt","r",stdin);
    N = getInt();
    K = getInt();
    for(int i=1;i<=N;++i){
        A[A[i].idx = i].x = getInt();
        A[i].y = getInt();
        A[i].z = getInt();
        A[i].cnt = 0;
    }
    sort(A+1, A+N+1);
    Q = 0;
    for(int i=1;i<=N;++i){
        if(Q && A[Q].x==A[i].x&&A[Q].y==A[i].y&&A[Q].z==A[i].z){
            ++A[Q].cnt;
        }else{
            A[++Q] = A[i];
            A[A[Q].idx = Q].cnt = 1;
        }
    }
    CDQ(1, Q);
    for(int i=1;i<=Q;++i)Ans[A[i].idx] += A[i].cnt - 1;
    for(int i=1;i<=Q;++i)Cnt[Ans[A[i].idx]] += A[i].cnt;
    for(int i=0;i<N;++i)printf("%d\n", Cnt[i]);
    return 0;
}
