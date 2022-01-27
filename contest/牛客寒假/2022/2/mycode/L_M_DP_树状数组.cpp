/**
 * 给定一个数组A，以及一个表示限制条件的数组B，问合法的序列一共有多少个
 * 规则为：
 * 1 序列是不严格递增的
 * 2 对每个Ai，要么Ai是第一个被选中的，要么Ai之前的Bi个元素中至少有一个
 * 令Ui是以i结尾的方案总数，则
 * Ui = SIGMA{Uj, j=i-b,...,i-1, 且Aj<=Ai}
 * 再令 Di = I[i-1] + Ui, 则D[N]是答案
 * 这个显然超时
 * 注意到Ui求的是区间和，可以考虑使用树状数组
 * 对A按值排序，对于新的顺序，对于当前要计算的Ui，比它大的值都还没有出现
 * 因此可以计算令Ui为[Ai.idx-b, Ai.idx-1]的区间和
 * 计算完以后再将Ui插入即可
 * 最后整个[1...N]的区间和为答案
*/
#include<bits/stdc++.h>
namespace GenHelper
{
    int z1,z2,z3,z4,z5,u,res;
    int get()
    {
        z5=((z1<<6)^z1)>>13;
        z1=((int)(z1&4294967)<<18)^z5;
        z5=((z2<<2)^z2)>>27;
        z2=((z2&4294968)<<2)^z5;
        z5=((z3<<13)^z3)>>21;
        z3=((z3&4294967)<<7)^z5;
        z5=((z4<<3)^z4)>>12;
        z4=((z4&4294967)<<13)^z5;
        return (z1^z2^z3^z4);
    }
    int read(int m) {
        u=get();
        u>>=1;
        if(m==0)res=u;
        else res=(u/2345+1000054321)%m;
        return res;
    }
     void srand(int x)
    {
        z1=x;
        z2=(~x)^(0x23333333);
        z3=x^(0x12345798);
        z4=(~x)+51;
      	u = 0;
    }
}

using namespace GenHelper;
using namespace std;

#ifndef ONLINE_JUDGE
int const SIZE = 13;
#else
int const SIZE = 2000010;
#endif

typedef long long llt;
llt const MOD = 1000000000+7;

int N;
llt C[SIZE];

/// 树状数组
inline int lowbit(int x){return x & -x;}
void modify(int idx, llt delta){
	for(;idx<=N;idx+=lowbit(idx)){
		(C[idx] += delta) %= MOD;
	}
}
llt query(int idx){
	llt ans = 0;
    for(;idx;idx-=lowbit(idx)){
        (ans += C[idx]) %= MOD;
	}
	return ans;
}
inline llt query(int s, int e){
    return (query(e) - query(s-1) + MOD) % MOD;
}

struct _t{
	int idx;
	int val;
	int b;
}A[SIZE];

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int seed;
    scanf("%d%d", &N, &seed);
	srand(seed);
	for(int i=1;i<=N;i++){
		A[A[i].idx = i].val = read(0);
		A[i].b = read(i);
	}

	sort(A+1, A+N+1, [](const _t&a, const _t&b)->bool{
		if(a.val != b.val) return a.val < b.val;
		if(a.idx != b.idx) return a.idx < b.idx;
		return a.b < b.b;
	});
    
    for(int i=1;i<=N;++i){
		llt t = 1LL + query(A[i].idx-A[i].b, A[i].idx-1);
		modify(A[i].idx, t);
	}
	printf("%lld\n", query(N));
    return 0;
}