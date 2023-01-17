/**
 * 给一个数组，问能否找出两个不同的子序列，使得其位或和相等。
 * 不需要构造，只需要回答是否。
 * 如果该数组的每一个数，都拥有一个独一无二的位，则否。否则为yes
 * 假设每个数都拥有独一无二的位，则任意子序列的异或和结果均不会相等，所以为NO。
 * 反过来，假设有一个数它没有独一无二的位，即它的所有位分散中其他的数中，则可以构造两个子序列，a为全体，b为全体除去该数，这两个子序列的或和是相等的。
 */
#include <bits/stdc++.h>
using namespace std;
 
char *__abc147, *__xyz258, __ma369[1000000];
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
int const SIZE = 23;
#else
int const SIZE = 3500000;
#endif

using llt = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using vvvi = vector<vvi>;

int N;
vvi A;
map<int, int> Cnt;

bool proc(){
	for(const auto & vec : A){
		bool flag = false;
		for(int i : vec){
			if(1 == Cnt[i]){
				flag = true;
				break;
			}
		}
		if(!flag) return true;
	}
	return false;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int nofkase = getInt();
	while(nofkase--){
		Cnt.clear();
        A.assign(N=getInt(), vi());
		for(auto & vec : A){
			vec.assign(getInt(), 0);
			for(int & i : vec){
				++Cnt[i = getInt()];
			}
		}
		puts(proc()?"YES":"NO");
	}
    return 0;
}


