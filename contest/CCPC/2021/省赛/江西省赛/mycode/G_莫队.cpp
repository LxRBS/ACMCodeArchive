/**
 * 给定数组，区间查询出现最多的公约数的次数，不考虑1
 * 数量级为5E4，可以考虑莫队算法
 * 首先确定只考虑质因子即可，其次数值范围在1E6，因此每个数最多含有7个质因子
 * 记录当前区间质因子的出现的次数，以及相应次数的质因子，
 * 对每个变动的元素维护上面两个数据即可
 * 对每个变动的元素需要for它的所有质因子，最多为7。
 * 时间比较紧，不能乱用时间
 * 首先不需要用筛法求出1E6的质因子，因为题目最多只需要5E4个数的质因子数据，提前筛出来是浪费
 * 其次多组数据清空的时候不要memset，因为质因子最大接近1E6，memset也是这个量级
 * 直接用莫队算法中的操作清空，指针最多移动5E4次，每次最多7个操作，数量级只有3.5E5。
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

#ifndef ONLINE_JUDGE
int const SIZE = 11;
int const BLOCK_SIZE = 1;
#else
int const SIZE = 5E4+7;
int const BLOCK_SIZE = 230;
#endif

using llt = long long int;
struct _t{
    int s, e;
    int idx;
    bool operator < (const _t & b) const {
        int ln = this->s / BLOCK_SIZE;
        int rn = b.s / BLOCK_SIZE;
        if(ln != rn) return ln < rn;
        return this->e < b.e;
    }
}Problem[SIZE];

bool isComp[(int)1E6+1] = {false};
int P[1003];
int PCnt = 0;
void sieve(){
    int s = 1003;
    for(llt i=2;i<s;++i){
        if ( !isComp[i] ) P[PCnt++] = i;
 
        for(llt j=0;j<PCnt&&i*P[j]<SIZE;++j){
            isComp[i*P[j]] = true;
            if ( 0 == i % P[j] ) break;
        }
    }
}
 
using vi = vector<int>;
vi Fac[(int)1E6+1];
 
void f(int n){
    vi & vec = Fac[n];
    for(int i=0;i<PCnt&&(llt)P[i]*P[i]<=n;++i){
        if(0 == n % P[i]){
            vec.push_back(P[i]);
            while(0 == n % P[i]) n /= P[i];
        }
    }
    if(n != 1) vec.push_back(n);
}
 
int N, Q;
int A[SIZE];
int Ans[SIZE];
int MoAns = 0;

int Cnt2Prime[SIZE];
int Prime2Cnt[(int)1E6+1];

/// 插入n增加的质因子数量
inline void insert(int n){
    for(auto i: Fac[n]){
        int & c = Prime2Cnt[i];
        if(c) --Cnt2Prime[c];
        
        MoAns = max(MoAns, ++c);
        ++Cnt2Prime[c];
    }
}

/// 删除n减少的质因子数量
inline void remove(int n){
    for(auto i: Fac[n]){
        int & c = Prime2Cnt[i];
        --Cnt2Prime[c];
        if(MoAns == c && 0 == Cnt2Prime[c]) --MoAns;

        --c;
        if(c) ++Cnt2Prime[c];
    }
}

void proc(){ // 莫队算法
    sort(Problem+1, Problem+Q+1);

    int curLeft = 1, curRight = 0;
    MoAns = 0;

    for(int i=1;i<=Q;++i){
        while(curRight < Problem[i].e) insert(A[++curRight]);
        while(curLeft > Problem[i].s) insert(A[--curLeft]);
        while(curRight > Problem[i].e) remove(A[curRight--]);
        while(curLeft < Problem[i].s) remove(A[curLeft++]);
        Ans[Problem[i].idx] = MoAns;
    }

    /// 相当于清空数据
    while(curLeft <= curRight) remove(A[curRight--]);

    return;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    sieve();
    int nofkase = getInt();
    while(nofkase--){
        /// 初始化
        // fill(Prime2Cnt, Prime2Cnt+1000001, MoAns=0);
        // memset(Cnt2Prime, 0, sizeof(Cnt2Prime));

        N = getInt(); Q = getInt();
        for(int i=1;i<=N;++i) {
            if(Fac[A[i] = getInt()].empty()){
                f(A[i]);
            }
        }
        for(int i=1;i<=Q;++i) {
            Problem[Problem[i].idx = i].s = getInt();
            Problem[i].e = getInt();
        }
        proc();
        for(int i=1;i<=Q;++i) printf("%d\n", Ans[i]);
    }
    return 0;
}