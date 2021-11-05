/**
    区间查询至少出现过2次的数值的数量
    莫队算法会超时
    与不同数量一样，那个是查询至少出现1次的数量
    仍然是离线查询。只是把前一个位置设置为1，这样就能保住当前区间至少是2个。
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

int const SIZE = 2001000;

struct _t{
    int s, e;
    int idx;
    bool operator < (const _t&rhs)const{
        if(e!=rhs.e) return e < rhs.e;
        return s < rhs.s;
    }
}B[SIZE];

int N, TotalColor, M;
int A[SIZE], Ans[SIZE];

int C[SIZE];

inline int lowbit(int x){return x&-x;}
void modify(int pos, int delta){
    for(;pos<=N;pos+=lowbit(pos)) C[pos] += delta;
}
int query(int pos){
    int ans = 0;
    for(;pos;pos-=lowbit(pos)) ans+=C[pos];
    return ans;
}
inline int query(int s, int e){return query(e)-query(s-1);}

int Pre[SIZE], P2[SIZE];
int main(){
    //freopen("1.txt","r",stdin);
    N = getUnsigned();
    TotalColor = getUnsigned();
    M = getUnsigned();
    for(int i=1;i<=N;++i) A[i] = getUnsigned();

    for(int i=1;i<=M;++i){
        B[B[i].idx = i].s = getUnsigned();
        B[i].e = getUnsigned();
    }

    sort(B+1, B+M+1);
    int cur = 1;
    for(int i=1;i<=M;++i){
        for(int j=cur;j<=B[i].e;++j){
            if(P2[A[j]]){
                modify(P2[A[j]], -1);
            }
            if(Pre[A[j]]){
                modify(Pre[A[j]], 1);
            }
            P2[A[j]] = Pre[A[j]];
            Pre[A[j]] = j;
        }
        cur = B[i].e + 1;
        Ans[B[i].idx] = query(B[i].s, B[i].e);
    }
    for(int i=1;i<=M;++i)printf("%d\n", Ans[i]);
    return 0;
}
