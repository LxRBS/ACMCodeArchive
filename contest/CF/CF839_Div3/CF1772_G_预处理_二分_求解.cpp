/**
 * 给定一个数组A，再给定一个X和一个Y，Y > X
 * 每次选择一个Ai,如果Ai<=X，则X加1，否则减一，问要多少次操作可以令X变成Y
 * 令Ai的选择次数为Ci，每次必须选择Ci最小的i，或者Ci最小的之一的i
 * 显然应该优先选Ai小的。当所有能加分的Ai都选过一次以后，只能选减分的。
 * 如果一轮的净胜分不是正数，则无法达到。
 * 首先将Ai排序，然后每一次循环，至少增加一个可以得分的Ai
 * 如果直接使用X与Ai与比较，来计算得分项，比较麻烦，因为在一轮之中有可能越过多个Ai
 * 先预处理一下，令Li是为了越过Ai而必须具备的最低分数，而After[i]是具备Li的分数，在本轮能到达的最大值
 * DP方程很简单
 * if(After[i] >= A[i]) L[i] = L[i-1], After[i] = After[i-1] + 1 // 说明用L[i-1]就能越过Ai，而且在之前的基础上又多得了一分
 * else L[i] = A[i] - i, After[i] = A[i] + 1; // Ai必然与A[i-1]拉开了大于i的差距， A[i]-i的分数值可以保证前面得到i分，正好越过Ai
 * 
 * 拿到L数组以后就可以只用分数去跟L数组比，每次循环至少跨越一个Ai，最多N次循环即可
 * 二分就能拿到本轮的加分，以及负分和净胜分
 * 先讨论特殊情况，如果加分就能超过Y，则可以得出答案结束
 * 如果本轮加分就是N，则以后就是简单循环，也可以得出答案结束
 * 否则，就要考虑要多少轮可以超过下一个Li，在从来没有到达Y的情况下，可以直接用整轮数超过Li。令这个轮数是k1
 * 因为只要不过Li，加分就不会变化。这就是用Li比Ai的好处。
 * 过了Li以后，就可以开始下一次迭代。
 * 但是在这个过程中，要考虑一下，是否超过了Y。不能直接用Y和Li比，因为达到Y未必用整轮数
 * 令 Y - X = k * lun + cha lun是整轮的分数，cha是一个小于加分的正数
 * 即k轮之后，再来一个加分段，即可达到Y。所以 k >= (Y - X - jia) / lun
 * 所以 k是比$(Y - X - jia) / lun$大的最小整数。
 * 看k1和k谁小就用谁。如果是用k的话，则加分项没有变化，但是下一次迭代，必然能超过Y。
 */
#include <bits/stdc++.h>
using namespace std;
 
namespace IO{

char *__abc147, *__xyz258, __ma369[1000000];
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

using llt = long long;

llt getLL(){
	int sgn = 1;
	char ch = __hv007();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = __hv007();
	if ( '-' == ch ) {sgn = 0;ch=__hv007();}
 
	llt ret = (int)(ch-'0');
	while( '0' <= (ch=__hv007()) && ch <= '9' ) ret = ret * 10LL + (llt)(ch-'0');
	return sgn ? ret : -ret;    
}

char getChar(function<bool(char)> ok){
    char ch = __hv007();
    while(!ok(ch)) ch = __hv007();
    return ch;
}

}

using llt = long long;
using vll = vector<llt>;
using vi = vector<int>;

int N;
llt X, Y;
vll A;

inline llt ceil(llt a, llt b){return (a + b - 1) / b;}

llt proc(){
	sort(A.begin(), A.end());
  
    vll leftmost(N, 0LL);
	vll after(N, 0LL);

	leftmost[0] = A[0];
	after[0] = A[0] + 1;
	for(int i=1;i<N;++i){
		if(after[i - 1] >= A[i]) leftmost[i] = leftmost[i - 1], after[i] = after[i - 1] + 1;
		else leftmost[i] = A[i] - i, after[i] = A[i] + 1;
	}

    llt ans = 0;
	while(1){
		auto it = upper_bound(leftmost.begin(), leftmost.end(), X);
		auto jia = it - leftmost.begin();
		if(X + jia >= Y){
			return ans += Y - X;
		}

		auto fu = leftmost.end() - it;
		auto jing = jia - fu;
		if(jing <= 0) return ans = -1;

	    if(it == leftmost.end()){
			return ans += Y - X;
		}

		auto k = ceil(Y - X - jia, jing);
		k = min(k, ceil(*it - X, jing));
		ans += k * N;
		X += k * jing;		
	}
	return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    using namespace IO;
	A.reserve(200001);
    int nofkase = getInt();
	while(nofkase--){
		N = getInt(); X = getLL(); Y = getLL();
		A.assign(N, 0);
		for(auto & i : A) i = getLL();
		printf("%lld\n", proc());
	}
    return 0;
}


