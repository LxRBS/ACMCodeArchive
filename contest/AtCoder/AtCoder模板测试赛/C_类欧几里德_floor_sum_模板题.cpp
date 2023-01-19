#include <bits/stdc++.h>
using namespace std;

#include <bits/extc++.h>
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

namespace FloorSum{

using llt = long long;
using t3t = tuple<llt, llt, llt>;

llt const MOD = 998244353LL;
llt const INV_TWO = 499122177LL; // 2的逆
llt const INV_SIX = 166374059LL; // 6的逆

llt fNoMod(llt n, llt a, llt b, llt c){
    llt ans = 0;
    if(a < 0){
        auto a2 = (a % c + c) % c;
        ans -= n * (n - 1) / 2 * ((a2 - a)/ c);
        a = a2;
    }
    if(b < 0){
        auto b2 = (b % c + c) % c;
        ans -= n * ((b2 - b) / c);
        b = b2;
    }
    while(1){
        if(a >= c){
            ans += n * (n - 1) / 2 * (a / c);
            a %= c;
        }
        if(b >= c){
            ans += n * (b / c);
            b %= c;
        }       
        auto y_max = a * n + b;
        if(y_max < c) break;

        n = y_max / c;
        b = y_max % c;
        swap(c, a); 
    }
    return ans;
}



};

using llt = long long;
using vll = vector<llt>;



int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif 
    int nofkase = getInt();
    while(nofkase--){
        llt n = getInt();
        llt c = getInt();
        llt a = getInt();
        llt b = getInt();
        cout << FloorSum::fNoMod(n, a, b, c) << endl;
    }
    return 0;
}
