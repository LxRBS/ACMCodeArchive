/**
 * 与G1一模一样，只是N在2E5。首先A中的前两个元素必须都是1，再下一个元素必须是2。
 * 令s为当前的前缀和，猜测每一个前缀和之内的元素都能表示出来。然后依次迭代即可。O(N)
 * 没有证明。
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

    llt limit = 2;
	for(int i=2;i<N;++i){
        if(A[i] > limit) return false;
		limit += A[i];
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

