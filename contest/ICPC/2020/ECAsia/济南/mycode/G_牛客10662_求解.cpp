/**
 * 给定X和Y，X>Y，要求做最多5步亦或操作，使得X变成Y
 * 且每次亦或的数不能大于当前的X。
 * 最多只需2步即可。
 * 第一步把X的低位变得与Y一模一样，第二步把X的高位去掉即可
 * 注意移位运算要用1LL<<k，不能用1<<k，否则也有问题。
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
int const SIZE = 22;
#else
int const SIZE = 220;
#endif

typedef unsigned long long ull;
ull X, Y;
vector<ull> Ans;

void proc(){
	Ans.clear();
    ull y = Y, tmp = 0;
    for(int k=0;y;++k){
		y >>= 1;
		tmp |= ( (Y&(1LL<<k))^(X&(1LL<<k) ) ? 1LL : 0) << k;
	}
	if(tmp)	Ans.push_back(tmp);
	if((X^tmp) - Y) Ans.push_back((X^tmp) - Y);
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
#endif
L:
    if(!(cin>>X>>Y)) return 0;
	proc();
	cout<<Ans.size()<<endl;
	for(auto i: Ans) cout<<i<<" ";
	cout<<endl;
#ifndef ONLINE_JUDGE
    ull ans = X;
	for(auto i: Ans){
		if(i >= ans){
			cout<<"A = "<<i<<", now X = "<<ans<<endl;
			throw runtime_error("A > X, wrong");
		}
		ans ^= i;
	}
	if(ans != Y){
		cout<<"Y = "<<Y<<", ans is "<<ans<<endl;
		throw runtime_error("the last ans is not right");
	}
#endif	
    goto L;
    return 0;
}

