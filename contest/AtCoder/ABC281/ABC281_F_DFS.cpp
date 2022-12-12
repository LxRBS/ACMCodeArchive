/**
 * 给定N长度的数组A，找一个x，使得所有的Ai^x的最大结果最小
 * 输出这个最小结果
 * 对于所有Ai的第k位，如果第k位全为1，显然x该位为1，如果全为0，显然x该位为0
 * 如果有1有0，则不好判断
 * 考虑将数组按第k位为1或者0分为两半a和b，如果x该位选1，则a中的数无需再考虑；反之亦然。
 * 因此可以写一个dfs，每次去掉一半的数。最后用剩下的数异或x即可。
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
int const SIZE = 2E5+5;
#endif

using vi = vector<int>;
int N;
vi A;
int Ans = 0;

void dfs(int pos, int x, const vi & v){
	if(-1 == pos){
		int ans = 0;
		for(int i : v) ans = max(ans, i ^ x);
		Ans = min(Ans, ans);
		return;
	}

	vi a, b;
	for(int i : v){
		if(i & (1<<pos)){
			a.push_back(i);
		}else{
			b.push_back(i);
		}
	}
    if(a.empty()){
		dfs(pos-1, x, b);
	}else if(b.empty()){
		dfs(pos-1, x| (1<<pos), a);
	}else{
		dfs(pos-1, x | (1<<pos), b);
		dfs(pos-1, x, a);
	}
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    A.assign(N = getInt(), 0);
    for(int & i : A) i = getInt();
	sort(A.begin(), A.end());
	A.erase(unique(A.begin(), A.end()), A.end());
	Ans = 2000000000;
	dfs(30, 0, A);
    cout << Ans << endl;
    return 0;
}
