/**
 * 求区间内非独数的种类的数量
 * 例如：[100, 200, 100, 200, 300] 答案为2，因为100和200都是非独
 * 假设问题为[s...e]，令p2,pre,cur依次为某个颜色的三个连续位置
 * 在区间内从左向右扫描cur时，每次令V[p2]--,V[pre]++,V初始全为0
 * 这样就保证了区间内的每一种颜色，只有倒数第二次出现的位置为1，其余全为0
 * 例如:
 * [100, 100, 100, 200, 200, 300] 对应的V为
 * [  0,   1,   0,   1,   0,   0]，此时对V求区间和即可
 * 对于某个问题，只要扫描过程不超过其右端点，即可正确回答这个问题
 * 因此离线，首先将问题按右端点排序，然后边扫描边回答即可
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

#ifndef ONLINE_JUDGE
int const SIZE = 12;
#else
int const SIZE = 2001000;
#endif

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
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
#endif
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

