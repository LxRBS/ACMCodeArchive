/**
 * 给第一个数x，x在1E9，要求另一个数y，满足
 * 1 y是x的倍数
 * 2 二进制表示下，x是y的子串，且y的1比x多
 * 3 y不能超过1E19
 * x显然是30位int，上限显然在64位，所以将x左移30位再加x即可
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

typedef long long llt;
typedef vector<int> IntVecTy;
typedef pair<int, int> PiiTy;

struct pair_hash{
	inline size_t operator()(const PiiTy&p)const{
		return p.first * 1331 + p.second;
	}	
};

#ifndef ONLINE_JUDGE
int const SIZE = 11;
#else
int const SIZE = 1000001;
#endif

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    unsigned long long x;
	cin>>x;
	x = (x << 30)+x;
    cout<<x<<endl;
    return 0;
}
