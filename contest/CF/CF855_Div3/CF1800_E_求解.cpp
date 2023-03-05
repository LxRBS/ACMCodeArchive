/**
 * 给定两个长度为N的字符串S和T。再给定一个K。每次可以将S中两个
 * 相距为K或者K+1的字符交换。问能否通过操作使得S变成T
 * 以K==8为例，很容易发现 
 * 1  2  3  4  5  6  7  8
 * 9 10 11 12 13 14 15 16
 * 当N==2K及其以上，从1就能到达8，且可以到达任何位置
 * 当 N <= K 时，必须 S == T
 * 当 N 在[K+1, 2K-1]之间，则部分可交换，中间必须相等。 
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
int const SIZE = 21;
#else
int const SIZE = 66;
#endif

using llt = long long;
using vi = vector<int>;
using vll =vector<llt>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vpii = vector<pii>;

llt const MOD = 998244353LL;

int N, K;
string S, T;


bool proc(int cnt){
    vi c(26, 0);

    for(int i=1;i<=cnt;++i)++c[S[i-1] - 'a'];
    for(int i=K+1;i<=K+cnt;++i)++c[S[i-1] - 'a'];

    for(int i=1;i<=cnt;++i)--c[T[i-1] - 'a'];
    for(int i=K+1;i<=K+cnt;++i)--c[T[i-1] - 'a'];

    for(int i=0;i<26;++i)if(c[i])return false;
    return true;
}

bool proc(){
    vi c(26, 0);
    for(char ch : S) ++c[ch - 'a'];
    for(char ch : T) --c[ch - 'a'];
    for(int i=0;i<26;++i)if(c[i])return false;
    
    if(K + K <= N) return true;
    if(N <= K) return S == T;
    
    int cha = K + K - N;
    for(int i=K,j=0;j<cha;++j,--i)if(S[i - 1] != T[i - 1])return false;
    
    return proc(K - cha);
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	// int nofkase; scanf("%d", &nofkase);
    int nofkase; cin >> nofkase;
    while(nofkase--){
        cin >> N >> K >> S >> T;
        puts(proc()?"YES":"NO");
    }
    return 0; 
}