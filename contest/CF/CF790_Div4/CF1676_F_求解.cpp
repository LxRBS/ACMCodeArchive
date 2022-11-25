/**
 * 给定数组和K，求最长的区间[L, R]满足：
 * 该区间内所有的数在数组中均出现了至少K次
 * 用map做一个计数器，然后遍历即可
 */
#include <bits/stdc++.h>
#include <memory>
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
int const SIZE = 2E5+13;
#endif

using llt = long long;
using pii = pair<int, int>;

int N, K;
int A[SIZE];
map<int, int> C;

void proc(){
    unique_ptr<pii> ans = nullptr;
	int a = 0, b = 0;
	auto cur = C.begin();
	auto eit = C.end();
	while(1){
        while(cur != eit && cur->second < K) ++cur;
		if(cur == eit) break;

		a = b = cur->first;
		auto last = cur++;
		while(cur != eit && last->first + 1 == cur->first && cur->second >= K){
            last = cur++;
		}
        b = last->first;

		if(nullptr == ans || b - a > ans->second - ans->first){
			if(ans == nullptr) ans = make_unique<pii>();
			*ans = {a, b};
		}
	}
	if(nullptr == ans) printf("-1\n");
	else printf("%d %d\n", ans->first, ans->second);
	return;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r" ,stdin);
#endif    
    int nofkase = getInt();
	while(nofkase--){
		N = getInt(); K = getInt();
		C.clear();
		for(int i=1;i<=N;++i) ++C[A[i] = getInt()];
		proc();
	}

    return 0;
}