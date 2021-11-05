/**
   给定一个数组，问区间内不同的数值数量是多少。
   莫队算法会超时
   考虑一个询问[s, e]，只以每类数值最右边的为有效
   假设某段为[......x]，则查询任意[?, e]区间时，之前的x都可以认为不起作用
   仍然用离线算法。首先将询问按右端点排序
   然后for N，对每一个第二次碰到的数，当前位置加1，上一个位置减1
   并在合适的位置回答问题
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

int Pre[SIZE];
int main(){
    //freopen("1.txt","r",stdin);
    N = getUnsigned();
    //TotalColor = getUnsigned();
    for(int i=1;i<=N;++i) A[i] = getUnsigned();
    M = getUnsigned();

    for(int i=1;i<=M;++i){
        B[B[i].idx = i].s = getUnsigned();
        B[i].e = getUnsigned();
    }

    sort(B+1, B+M+1);
    int cur = 1;
    for(int i=1;i<=M;++i){
        for(int j=cur;j<=B[i].e;++j){
            if(Pre[A[j]]){
                modify(Pre[A[j]], -1);
            }
            modify(Pre[A[j]] = j, 1);
        }
        cur = B[i].e + 1;
        Ans[B[i].idx] = query(B[i].s, B[i].e);
    }
    for(int i=1;i<=M;++i)printf("%d\n", Ans[i]);
    return 0;
}
