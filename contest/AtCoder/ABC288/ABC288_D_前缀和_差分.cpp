/**
 * N长度的数组，给定一个K，K<=min(10, N)
 * 允许的操作是将数组中K长度的子区间统一加c，c可以任意指定，子区间也可以任意选定，只要长度为K
 * Q个询问，每次询问给出[s, e]
 * 问能否通过上述操作将[s, e]清零。每次询问是独立的。
 * 标程采用的是差分，因为原数组上成段增加，等价于差分数组上的两个单点修改，因此可以转化一下
 * 另一种做法本质上应该是一样的，
 * 首先确定操作顺序是不影响结果的。所以可以从左到右依次操作
 * 将区间按K分段
 * 发现为了变0，其实就是将每个周期上对应位置的数加起来减去别的位置的周期和
 * 因为K只有10，所以按照每个位置求一个前缀和，对每个询问依次检查即可
 * O(KN+Q)
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
int const SIZE = 33;
#else
int const SIZE = 1E6+10;
#endif

using llt = long long;
using vll = vector<llt>;
using vi = vector<int>;
using vvi = vector<vi>;

int N, K, Q;
vi A;
vector<vector<llt>> S;

bool proc(int a, int b){
    auto tmp = S[0][b] - S[0][a - 1];
    for(int i=1;i<K;++i){
        if(tmp != S[i][b] - S[i][a - 1]) return false;
    }
    return true;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    N = getInt(); K = getInt();
    A.assign(N + 1, 0);
    S.assign(K, vector<llt>(N + 1, 0LL));
    for(int i=1;i<=N;++i){
        A[i] = getInt();
        for(int j=0;j<K;++j){
            S[j][i] = S[j][i - 1] + (i % K == j ? A[i] : 0);
        }
    }

    Q = getInt();
    for(int a,b,q=1;q<=Q;++q){
        a = getInt(); b = getInt();
        puts(proc(a, b) ? "Yes" : "No");
    }
    return 0;
}