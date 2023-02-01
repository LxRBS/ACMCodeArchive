/**
 *  N个怪物，每个怪物有Hi的血，每隔1s，回复Vi的血。
 * 每T秒攻击一次，攻击力为A。问至少在何时可以杀死所有怪物，不能做到输出-1
 * 首先确定，每个怪物是独立的，杀死i和j无关。因此可以枚举每个怪物。
 * 对怪物i，首先特判，如果 A >= Hi, 则1次即可；再如果 A <= Vi，则永远杀不死
 * 否则，显然每回合可以令怪物掉血 A - Vi，然后只要怪物的血掉到了A及其一下，再来一刀即可。
 * 令前面回合数为x，即 H - x * (A - V) <= A, 所以 x >= (H - A) / (A - V)
 * 所以x是右边的数向上取整，然后再加1则是该怪物的刀数。
 * 注意攻击的周期是T，而回血周期是1s，因此首先将怪物的Vi都乘以T，再讨论。
 * 最后再乘回T得到时间。
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
int const SIZE = 13;
#else
int const SIZE = 3E5+10;
#endif

using llt = long long;
using pll = pair<llt, llt>;
using vpll = vector<pll>;

int N;
llt T;
llt Attack;
vpll Guaiwu;

llt proc(llt h, llt v){
    if(Attack >= h) return 1;
    if(Attack <= v) return -1;

    llt huihe = (h - Attack) / (Attack - v);
    if((h - Attack) % (Attack - v)) ++huihe;
    ++huihe;
    return huihe;
}

llt proc(){
    llt ans = 0;
    for(const auto & p : Guaiwu){
        auto tmp = proc(p.first, p.second);
        if(-1 == tmp) return -1;
        ans += tmp;
    }   
    return (ans - 1) * T + 1;
}


int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    // ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    N = getInt(); T = getInt(); Attack = getInt();
    Guaiwu.assign(N, {});
    for(auto & p : Guaiwu) p.first = getInt(), p.second = T * getInt();
    printf("%lld\n", proc());
    return 0;
}