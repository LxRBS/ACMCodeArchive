/**
 * 模拟消消乐的游戏，初始有一部分块是已知的，每次操作选两个块
 * 如果两块数值相同，则两块同时消除；否则两块朝上(朝上的块显然不用翻就知道数值)，但不能消除
 * 问最优策略下的全消完的期望步数
 * 有两个策略，1 朝上朝下各选一个，如果匹配则消除，否则，朝上的数量加1，朝下的减一
 * 2 朝下的选两个，如果自匹配就消除；如果这两个分别能够匹配上朝上的也消除(但是注意要加步数)；如果只有一个匹配，则消除一对；否则就是没有发现任何匹配
 * 当朝下多余2的时候总是要选择策略2(不会证明，可能只能小范围暴力观察一下)，显然朝上为0的时候也要选择策略2。
 * 策略1其实只有11、22两种情况。可以直接算出来。
 * 再然后显然是一个期望DP，令Dab为朝上为a、朝下为b的情况下，到达终点的期望步数
 * 终点显然是 D00 = 1
 * 考虑策略2的4种情况:
 * 1. 翻出的2个自己匹配自己，概率是 p = (b - a) / b * 1 / (b - 1), 贡献是 p * (1 + D[a][b-2])
 * 2. 当 a >= 2 时，翻出的2个与朝上的恰好都能匹配， 概率是 p = a / b * (a - 1) / (b - 1)，贡献是 p * (3 + D[a-2][b-2])
 * 3. 当 a >= 1 时，翻出的2个一个匹配一个不匹配，概率是 p = 2 * a / b * (b - a) / (b - 1)， 贡献是 p * (2 + D[a][b-2])
 * 4. 当b >= a + 4 时，翻出2个都不匹配的概率是 p = (b - a) / b * (b - a - 2) / (b - 1)，贡献是 p * (1 + D[a+2][b-2])
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

using llt = long long;
using vll = vector<llt>;
using vvll = vector<vll>;

llt const MOD = 1000000007LL;
inline llt add(llt a, llt b){return (a + b) % MOD;}
inline llt add(llt a, llt b, llt c){return (a + b + c) % MOD;}
inline llt mul(llt a, llt b){return a * b % MOD;}
inline llt mul(llt a, llt b, llt c){return a * b % MOD * c % MOD;}
inline llt mul(llt a, llt b, llt c, llt d){return a * b % MOD * c % MOD * d % MOD;}

int N, M;
int Total;
int Type;

vll Inv;

vvll D;

llt dfs(int a, int b){
    if(a < 0 || b <= 0 || a > b) return 0;
    if(-1 != D[a][b]) return D[a][b];
    if(1 == a && 1 == b) return D[a][b] = 1;
    if(2 == a && 2 == b) return D[a][b] = 5 * Inv[2] % MOD;
     
    llt ans = 0LL;
    if(b > 2 || 0 == a){
        auto fenmu = mul(Inv[b - 1], Inv[b]);
        ans = add(ans, mul(fenmu, b - a, 1 + dfs(a, b - 2)));
        if(a >= 2) ans = add(ans, mul(fenmu, mul(a, a - 1), 3 + dfs(a - 2, b - 2)));
        if(a >= 1) ans = add(ans, mul(fenmu, mul(a + a, b - a), 2 + dfs(a, b - 2)));
        if(b >= a + 4) ans = add(ans, mul(fenmu, b - a, b - a - 2, 1 + dfs(a + 2, b - 2)));
    }
     
    // printf("D[%d][%d] = %lld\n", a, b, ans);
    return D[a][b] = ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    // ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    N = getInt(); M = getInt();
    Total = N * M;
    set<int> ss;
    int cnt = 0;
    for(int a,i=0;i<N;++i)for(int j=0;j<M;++j){
        if(a = getInt()){
            auto it = ss.find(a);
            if(it != ss.end()) ss.erase(it), Total -= 2, ++cnt;
            else ss.insert(it, a);            
        }
    }
           
    Inv.assign(Total + 1, 0LL);
    Inv[1] = 1LL;
    for(int i=2;i<=Total;++i){
        Inv[i] = (MOD - MOD / i) * Inv[MOD % i] % MOD;
    }

    Type = Total >> 1;
    D.assign(Total + 1, vll(Total - ss.size() + 1, -1LL));
    auto ans = dfs(ss.size(), Total - ss.size());
    printf("%lld\n", ans + cnt);
    return 0;
}