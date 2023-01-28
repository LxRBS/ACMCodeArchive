/**
 * 一个数对(x, y)是luck的如果gcd(x, y)=1
 * 一个数列(x, y)(x+1, y+1)...是luck的如果所有数对都是luck的
 * 给定(x, y)，问以它为起点的luck数列最长是多少
 * 假设(x+k, y+k)不是luck的，设公约数为g，则
 * x + k = ag, y + k = bg, 所以 y - x = (b - a)g
 * 表示 y - x 一定有大于1的因子，进一步的检查质因子即可
 * 对 y - x 的每个质因子，求出k，并且保存能够找到的最小的k
 * 如果没有质因子，可以特判。
 * 对于 Y > 2X, 令k = Y - 2X，则可以变为(Y-X, 2(Y-X))，显然到此为止
 * 到此还没有答案，Y - X必然是一个小质数。令 X = ap + u, Y = bp + u
 * 只要将X和Y都加到p的倍数即可，即p - u，当场写的 Y - X - 1，why?
 * 复杂度较高，刚好卡在4s过，因为每次都对 Y - X 查找质因子。
 * 标程用筛法的时候，直接筛出了所有数的最小质因子，会快很多。
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
int const SIZE = 2E5+10;
#endif

using llt = long long;
using vi = vector<int>;
using si = set<int>;
using vvi = vector<vi>;
using msi = map<int, si>;

vector<bool> isComp(3500, false);
vi P;

void init(){
	for(int i=2;i<3500;++i){
		if(isComp[i]) continue;

		P.push_back(i);
		for(int j=i*i;j<3500;j+=i){
			isComp[j] = true;
		}
	}
}

using llt = long long;

llt gcd(llt a, llt b){
	while(b){
		llt r = b;
		b = a % b;
		a = r;
	}
	return a;
}

llt X, Y;

llt proc(llt m, llt g){
	if(0 == X % g) return 0;
	if(0 == Y % g) return 0;
	llt a = X / g + 1;
	llt k = a * g - X;
	llt b = m / g + a;
	assert(X+k == a*g && Y+k == b*g);
	
	b = Y / g + 1;
	llt k2 = b * g - Y;
	a = b - m / g;
	assert(X+k2 == a*g && Y+k2 == b*g);

	return min(k, k2);
}

llt proc(){
	if(gcd(X, Y) != 1) return 0;
	if(X + 1 == Y) return -1;

	llt m = Y - X;
	llt ans = -1;
	llt n = m;
	for(int i=0,pcnt=P.size();i<pcnt&&P[i]*P[i]<=n;++i){
		if(m % P[i]) continue;
		llt t = P[i];
        llt tmp = proc(m, t);
		if(-1 == ans || tmp < ans) ans = tmp;
		t = m / t;
        tmp = proc(m, t);
		if(-1 == ans || tmp < ans) ans = tmp;
		while(n % P[i] == 0) n /= P[i];
		if(P[i]*P[i] > n) break;
	}
	if(1 != n){
		llt tmp = proc(m, n);
		if(-1 == ans || tmp < ans) ans = tmp;
	}
	if(-1 != ans) return ans;
	if(Y > X + X) return Y - X - X;
	
	return Y - X - 1;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    init();
    int nofkase = getInt();
	while(nofkase--){
        X = getInt(); Y = getInt();
		printf("%lld\n", proc());
	}

    return 0;
}