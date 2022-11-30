/**
 * 给定A/B/C/D，找到一对数X/Y，满足
 * XY是AB的倍数且A<X<=C且B<Y<=D
 * 对AB做质因子分解，得到一个map
 * map[i]表示AB之中所含的质因子i的数量
 * 则XY的乘积中至少要等于这个数
 * 再做一个深搜，对每一个i，依次取0,...,map[i]，
 * 最后组合成x，令y=AB/x
 * 再令X=C/x*x, Y=D/y*y，
 * 则可以保证X和Y是当时满足条件的能够取到的最大值
 * 如果此时X和Y还能大于A和B，则成功。
 * 单个质因子的数量不会超过60，不同质因子的总数更不会超过60
 * 所以很快会做完。
 * */
#include <assert.h>
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

char getChar(){
	char ch = __hv007();
	while(!isalpha(ch)) ch = __hv007();
	return ch;
}

#ifndef ONLINE_JUDGE
int const SIZE = 23;
#else
int const SIZE = 2E5+13;
#endif

using llt = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using si = set<int>;
using mii = map<int, int>;

int const SZ = 35000;
bool isComp[SZ] = {false};
int P[SZ] = {0};
int PCnt = 0;
void sieve(){
    llt tmp;
	for(int i=2;i<SZ;++i){
		if ( !isComp[i] ) P[PCnt++] = i;
		
		for(int j=0;j<PCnt&&(tmp=i*P[j])<SZ;++j){
			isComp[tmp] = true;
		}
	}
}

llt A, B, C, D;
mii Pa, Pb;
mii Total;
llt X, Y;

void proc(llt x, mii & c){
	c.clear();
	for(int i=0;i<PCnt&&P[i]*P[i]<=x;++i){
		while(0 == x % P[i]){
			++c[P[i]];
			x /= P[i];
		}
	}
	if(x != 1) ++c[x];
	return;
}

bool dfs(decltype(Total.rbegin()) it, llt x){
	if(it == Total.rend()){
		llt y = A * B / x;
		X = C / x * x;
		Y = D / y * y;
		if(X > A && Y > B){
			return printf("%lld %lld\n", X, Y), true;
		}
		return false;
	}

	llt fac = it->first;
	int cnt = it->second;
	llt k = 1;
	for(int i=0;i<=cnt;++i){
		auto tt = it;
        bool b = dfs(++tt, x * k);
		if(b) return true;
		k *= fac;
	}
	return false;
}

void proc(){
	if(C >= A+A && D >= B+B){
		return (void)printf("%lld %lld\n", A+A, B+B);
	}

    proc(A, Pa); proc(B, Pb);
	
    Total.clear();
	for(auto p : Pa) Total.insert(p);
    for(auto p : Pb) Total[p.first] += p.second;
    auto it = Total.rbegin();
	bool b = dfs(it, 1LL);
	if(!b) printf("-1 -1\n");
    return;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r" ,stdin);
#endif   
    sieve();
    int nofkase = getInt();
	while(nofkase--){
		A = getInt();
		B = getInt();
		C = getInt();
		D = getInt();
		proc();	
	}
    return 0;
}