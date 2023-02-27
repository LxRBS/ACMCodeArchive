/**
 * 给定一个排列，定X为某个区间的第二大值，求所有区间的第二大值之和。
 * N在1E4，直接暴力暴力枚举一下。
 * 对每一个开始位置start，可以在线性时间内求出以start开头的所有区间的最大值和次大值
 * O(N^2)
 */
#include <bits/stdc++.h>
using namespace std;

char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)
 
using llt = long long; 
llt getInt(){
	int sgn = 1;
	char ch = __hv007();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = __hv007();
	if ( '-' == ch ) {sgn = 0;ch=__hv007();}
 
	llt ret = (llt)(ch-'0');
	while( '0' <= (ch=__hv007()) && ch <= '9' ) ret = ret * 10LL + (llt)(ch-'0');
	return sgn ? ret : -ret;
}



#ifndef ONLINE_JUDGE
int const SIZE = 21;
#else
int const SIZE = 2e5+5;
#endif


using vi = vector<int>;
using vll =vector<llt>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vpii = vector<pii>;

llt const MOD = 998244353LL;

using t3t = tuple<llt, llt, llt>;
using vt3t = vector<t3t>;

int N;
vi A;
int Level;

llt proc(int pos){
	llt ans = 0;
    int high = A[pos];
	int second = -1;
	for(int i=pos+1;i<N;++i){
        if(high < A[i]){
			second = high;
			high = A[i];
		}else if(-1 == second || second < A[i]){
			second = A[i];
		}
		ans += second;
		if(second + 2 == Level){
			ans += second * (N - i - 1LL);
			break;
		}
	}
	return ans;
}

llt proc(){
	Level = N + 1;
	llt ans = 0;
    for(int i=0;i<N;++i){
		ans += proc(i);
		if(Level == A[i] + 1) Level = A[i];
	}
	return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	// int nofkase; cin >> nofkase;
    N = getInt();
    A.assign(N, 0);
	for(int & i : A) i = getInt();
	cout << proc() << endl;
    return 0; 
}