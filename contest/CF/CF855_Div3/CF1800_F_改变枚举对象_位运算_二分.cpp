/**
 * 给定N个字符串，问有多少对字符串连接起来以后满足
 * 1 长度是奇数
 * 2 出现的字符串的种类恰好是25种
 * 3 每种字符出现的数量恰好也是奇数
 * 条件1可以忽略，不用专门考虑。
 * 首先将用Ai表示字符串i出现的字符种类，显然是一个26位的位向量
 * 再用Bi表示字符串i出现的字符的奇偶性，显然也是一个26位的位向量
 * 枚举每一个恰好不出现的字符，记作ch，
 *    首先将所有没有ch的字符串安排一个新的数组，实际上记录Bi即可，令这个数组记作C
 * 然后给C排个序
 * for C中的每个元素ci: 记住此时ci表示一个字符串
 *   在C中寻找与ci每一位均相异的元素的数量
 *   由于ci是固定的，因此与ci每一位均相异的数也是固定的，记作d
 *   实际上就是查找d在C中一共有多少个，用equal_range即可。
 * O(26NlogN)。还要加上预处理时的所有字符串的总长度。
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


int N;
vector<string> S;
vi A, B;

llt proc(int ch){
    vi c; c.reserve(N);
    for(int i=0;i<N;++i){
        if(0 == ((1 << ch) & A[i])){
            c.push_back(B[i]);
        }
    }
    sort(c.begin(), c.end());
    llt ans = 0;
    int msk = ((1 << 26) - 1) ^ (1 << ch);
    for(int i : c){
        auto pp = equal_range(c.begin(), c.end(), i ^ msk);
        ans += pp.second - pp.first;
    }
    return ans;
}

llt proc(){
    A.reserve(N); B.reserve(N);
    for(const auto & s : S){
        int a = 0, b = 0;
        for(char ch : s){
            a |= 1 << ch - 'a';
            b ^= 1 << ch - 'a';
        }
        A.push_back(a);
        B.push_back(b);
    }

    llt ans = 0;
    for(int i=0;i<26;++i){
        ans += proc(i);
    }
    return ans / 2LL;
}


int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	// int nofkase; scanf("%d", &nofkase);
    cin >> N;
    S.assign(N, string());
    for(auto & s : S) cin >> s;
    cout << proc() << endl;
    return 0; 
}