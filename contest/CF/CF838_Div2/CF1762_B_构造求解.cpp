/**
 * 一个N长度的数组是好的，当任意Ai和Aj, min(Ai, Aj)是max(Ai, Aj)的因子
 * 允许的操作是：选择一个Ai和一个小于Ai的X令 Ai += X
 * 最多N次操作，达到目标。给出方案。
 * 首先要观察到 Ai += X 一定可以令Ai变为2的幂
 * 因此对每个Ai将其变为最近的2的幂即可
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
int const SIZE = 13;
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

vi T = {1};

int N;
vi A;
vpii Ans;

void proc(int pos, int target){
	if(target % A[pos] == 0) return;

	while(A[pos] < target / 2) target /= 2;
	Ans.emplace_back(pos+1, target - A[pos]);
}

int proc(){
    int m = *max_element(A.begin(), A.end());
	int k = 0;
	while(T[k] < m) ++k;
	int target = T[k];

    Ans.clear(); Ans.reserve(N);
	for(int i=0;i<N;++i){
		proc(i, target);
	}     
    printf("%d\n", (int)Ans.size());
	for(auto & p : Ans)printf("%d %d\n", p.first, p.second);
	return 0;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    for(int i=1;i<31;++i){
		T.push_back(T.back() * 2);
	}
    int nofkase = getInt(); 
	while(nofkase--){
        A.assign(N=getInt(), 0);
		for(int & i : A) i = getInt();
		proc();
	}

    return 0;
}


