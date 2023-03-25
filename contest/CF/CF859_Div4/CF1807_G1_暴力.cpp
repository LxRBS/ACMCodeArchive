/**
 * 给定目标数组B，初始时数组A中只含有一个元素1，每次操作，允许向A中添加一个元素，但是该元素必须是任意A已有元素之和。
 * 问能否通过此方法，将A变得与B一样。首先将B排个序，本质上就是问B中的大元素能否表示为若干小元素之和。
 * 可以做个暴力法，打个标记，O(N^2logN)。
 */
#include <bits/stdc++.h>
using namespace std;

#include <bits/extc++.h>
using namespace __gnu_cxx;
using namespace __gnu_pbds;


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
int const SIZE = 21;
#else
int const SIZE = 2E5+10;
#endif

using llt = long long;
using vi = vector<int>;
using vll =vector<llt>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vpii = vector<pii>;
using ull = unsigned long long;
// using i128 = __int128_t;
using Real = long double;

int N;
vi A;

bool proc(){
	if(1 == N) return A[0] == 1;

	sort(A.begin(), A.end());
	if(A[0] != 1 or A[1] != 1) return false;

    vi flag(A[N - 1] + 1, 0);
	flag[1] = flag[2] = 1;
	for(int i=2;i<N;++i){
		if(0 == flag[A[i]]) return false;

        set<int> s;
		for(int j=1;j<flag.size();++j){
			if(1 == flag[j] and j + A[i] < flag.size()){
				s.insert(j + A[i]);
			}
		}
		for(int j : s) flag[j] = 1;
		flag[A[i]] = 1;
	}
	return true;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int nofkase; scanf("%d", &nofkase);
	// int nofkase; cin >> nofkase;
    while(nofkase--){
        A.assign(N = getInt(), 0);
		for(int & i : A) i = getInt();
		puts(proc()?"YES":"NO");
	}
    return 0; 
}


