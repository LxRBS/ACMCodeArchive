/**
 * 等价于一个长度为N的总区间，再给定M个区间[s, e]
 * 选择k个区间使得其交集长度记作x，求min(k, x)的最大值
 * 二分交集长度，对每个长度x，看能不能选出x个区间使得其交集长度不小于x
 * 如何求出M个区间中是否有x个区间的交集长度至少为x？
 * 对每一个区间[s, e]，将[s + x - 1, e]范围内全部加1
 * 这样的话，对于某个 Si = k，说明有k个区间交集长度至少为x。
 * 成段更新单点求和操作，可以使用线段树
 * 也可以变为差分数组，使用树状数组
 * 注意到查询操作实际上可以按顺序进行，因此差分数组无需使用树状数组维护。
 * 所以一次二分是O(N)的。
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
int const SIZE = 130;
#else
int const SIZE = 1.1E6+10;
#endif

using vi = vector<int>;
using pii = pair<int, int>;
using vpii = vector<pii>;

int N, M;
vpii A;
vi C;

bool check(int x){
    fill(C.begin(), C.end(), 0);
	for(const auto & p : A){
		if(p.second + 1 < p.first + x) continue;
		/// [p.first+x-1, p.second]刷1
		++C[p.first + x - 1];
		--C[p.second + 1];
	}
	for(int i=1;i<=N;++i){
		C[i] += C[i - 1];
        if(C[i] >= x) return true;
	}
	return false;
}

int proc(){
	C.assign(N + 2, 0);
	int left = 1, right = N, mid;
	do{
        mid = (left + right) >> 1;
		if(check(mid)) left = mid + 1;
		else right = mid - 1;
	}while(left <= right);
	return right;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif 
    N = getInt(); M = getInt();
	A.assign(M, {});
	for(auto & p : A) p.first = getInt(), p.second = getInt();
	printf("%d\n", proc());
    return 0;
}

