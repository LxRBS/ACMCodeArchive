/**
 * 有N个怪物，每个怪物有Ai的血。每次可以对一个怪物造成1点伤害，或者对所有怪物造成1点伤害。
 * 第二种操作中，如果有怪物死掉，则可以反复操作。
 * 第一种操作可以任意次，第二种操作最多只能进行1次。
 * 问最少要多少次第一种操作可以杀死所有怪物。
 * 显然将怪物的血排成一个阶梯形状，再进行第二次操作是最有利的。
 * 排序以后枚举一下即可。 
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
int const SIZE = 1E6+1;
#else
int const SIZE = 1E6+1;
#endif

using llt = long long;
using vll = vector<llt>;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vpii = vector<pii>;

llt const MOD = 998244353LL;

int N;
vi A;

llt proc(){
    sort(A.begin(), A.end());
    llt ans = 0;
    int need = 1;
    for(int i : A){
        if(i == need) ++need;
        else if(i > need) ans += i - need, ++need;
        else ;
    }
    return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int nofkase = getInt();
    while(nofkase--){
        A.assign(N = getInt(), 0);
        for(int & i : A) i = getInt();
        printf("%lld\n", proc()); 
    }

    return 0;
}