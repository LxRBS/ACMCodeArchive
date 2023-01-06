/**
 * 给一个排列，每次操作允许交换任意两个元素
 * 问最少要多少次操作，将排列变为只有一个逆序对
 * 将排列看作是置换，即排列p看做是
 * | 1  2  ... n  |
 * | p1 p2 ... pn |
 * 令I为单位元，即123...n
 * 则将p通过交换变为I的最少操作次数记作d(I, p)，为Caylay距离
 * d(I, p) = N - p的轮换的数量
 * 任意两个置换p、q的Caylay距离 d(p, q) = d(I, p^(-1)q)
 * 由于目标是一个逆序对，则所有可能的p有N-1个，格式必然为
 * 123...(k-1)(k+1)k(k+2)...n
 * 因此只要枚举这N-1个可能的pi，计算d(I, pi^(-1)q)即可
 * 假设q的轮回的数量是x个，由于p的特殊性，简单验证可以发现，
 * 如果k和k+1在q中位于不同的轮换，则pi^(-1)q的轮换数量为x-1
 * 否则为x+1
 * 因此只需要求出输入排列的轮换即可，O(N)
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
int const SIZE = 2e5+5;
#endif

using Real = long double; 
using llt = long long;
using vi = vector<int>; 
using vvi = vector<vi>;
using vvvi = vector<vvi>;
using si = set<int>;
using vsi = vector<si>;

int N, K;
vi A;

bool check(){
	int cnt = 0;
	for(int i=1;i<=N;++i){
		if(i == A[i]) continue;

        if(i+1 == A[i] && i == A[i+1]){
			if(++cnt > 1) return false;
			++i;
			continue;
		}

		return false;
	}
	return 1 == cnt;
}

int proc(){
	if(check()) return 0;
	// vi flag(N+1, 0);
	// vsi sss;
    int stamp = 0;
	vi index(N+1, -1);
    for(int i=1;i<=N;++i){
        if(-1 != index[A[i]]) continue;
		
		int target = i;
		int cur = A[i];
		assert(-1 == index[i]);
		index[target] = stamp;
		
		if(i == A[i]) {++stamp; continue;}

		while(1){
			assert(-1 == index[cur]);
			index[cur] = stamp;
			if(A[cur] == target) break;
			cur = A[cur]; 
		}
        ++stamp;
	}

    int n = stamp;
	int ans = N;
    for(int i=1;i<N;++i){
        if(index[i] == index[i+1]){
			ans = min(ans, N - (n + 1));
		}else{
			ans = min(ans, N - (n - 1));
		}
	}
	return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int nofkase = getInt();
    while(nofkase--){
        A.assign((N = getInt())+1, 0);
		for(int i=1;i<=N;++i) A[i] = getInt();
		printf("%d\n", proc());
    }
    return 0;
}