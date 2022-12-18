/**
 * 给定一个数组，问能否选定一个数x，使得Ai=|Ai - x|
 * 最后能令数组A有序
 * 对每个相邻的A[i-1]和A[i]
 * 如果A[i-1]>A[i]，则x需要大于等于(A[i-1]+A[i])/2
 * 如果小于，则x需要小于等于(A[i-1]+A[i])/2
 * 等于则随意
 * 维护一个区间，每次求一个交集即可
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
int const SIZE = 23;
#else
int const SIZE = 2E5+10;
#endif

using llt = long long; 
using vi = vector<int>;
using si = set<int>;
using vvi = vector<vi>;
using msi = map<int, si>;
using pii = pair<int, int>;
using vpii = vector<pii>;
using t3t = tuple<int, int, int>;

llt const INF = 3000000000LL;
int N;
vi A;

llt proc(){
    pair<llt, llt> ans = {-INF, INF};
	for(int i=1;i<N;++i){
		if(A[i-1] == A[i]) continue;
		if(A[i-1] > A[i]){
			llt t = A[i-1] + A[i];
			if(t & 1) t = t / 2 + 1;
			else t = t / 2;
			if(t > ans.second){
				ans = {-1, -1};
				break;
			}else if(t >= ans.first){
				ans.first = t;
			}else{
				;;
			}
		}else{
			llt t = A[i-1] + A[i];
			t = t / 2;
			if(t < ans.first){
				ans = {-1, -1};
				break;
			}else if(t <= ans.second){
				ans.second = t;
			}else{
				;;
			}
		}
	}

	if(-1 == ans.first) return -1;
	if(ans.first != -INF) return ans.first;
	if(ans.second != INF) return ans.second;
	return 0;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int nofkase = getInt();
	while(nofkase--){
        A.assign(N = getInt(), 0);
		for(int & i : A) i = getInt();
		printf("%lld\n", proc());
	}
    return 0;
}


