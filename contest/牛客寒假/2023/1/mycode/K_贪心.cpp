/**
 * 长度为N的01字符串，恰好有M个1。
 * 字符串的每个为3的子串，如果1多于0，则称为坏的。
 * 问上述字符串最少的坏子串的数量。
 * 反过来考虑0的数量，如果只有1个0，发现该0其实是没有用的。
 * 因此必须两个0连续在一起才能减少坏的数量。
 * 同时为了放下更多的1，显然要两个0夹1个1。
 * 因为这样保证坏区间为0，且用了更多的1，这显然是最优的策略。
 * 如果1的数量有多，则所有1都放在最后即可。该情况下很容易计算出坏区间的数量
 * O(1)即可
 * 本题很明显有DP的特征，令D[n][m]，但是很显然无法写转移方程，因为需要考虑结尾
 * 同时不能仅考虑前一位，而需要考虑前二位，加上本位的结尾，一共是8种情况
 * D[i][j][st]为长度为i、j个1，后三位状态为st的最小值。很容易写出转移方程。
 */
#include <bits/stdc++.h>
using namespace std;
 
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
 
#ifndef ONLINE_JUDGE
int const SIZE = 23;
#else
int const SIZE = 450;
#endif

using Real = long double;
using llt = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using prr = pair<Real, Real>;
using mvi = map<int, vi>;

int N, M;

int proc(){
    if(N <= 2) return 0;
    int z = N - M;
    if(z < 2) return N - 2;

    int left = z & 1;
    int t = z / 2;

    int tmp = N - (t * 3);
    if(0 == left) return max(0, tmp - 1);

    tmp = N - (t * 3 + 1);
    return max(0, tmp - 1); 
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    N = getInt(); M = getInt();
    printf("%d\n", proc());
    return 0;
}


