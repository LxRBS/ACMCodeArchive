/**
 * 依次往栈里放数，如果栈顶2个及其以上的元素相等，这些相等元素就会消失。
 * 问每次push以后栈内数的数量
 * 就是栈模拟。进栈次数是N，出栈次数不会超过N，因此是O(N)
 * 也可以再用一个栈记住位置，这样就不用一个一个pop，可以成段的erase
*/
#include <bits/stdc++.h>
using namespace std;

char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000-1,stdin),__abc147==__xyz258) ? EOF : *__abc147++)

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
int const SIZE = 17;
#else
int const SIZE = 200010;
#endif

int N;
vector<int> Vec;
vector<int> Stack;
int Cnt[SIZE];

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    Vec.reserve(N = getInt());
	
	for(int a,i=1;i<=N;++i){
		a = getInt();
		if(Vec.empty()){
			Vec.push_back(a);
			assert(Stack.empty());
			Stack.push_back(1);
		}else{
			if(a == Vec.back()){
				if(++Stack.back() == a){
					Vec.erase(Vec.end()-a+1, Vec.end());
					Stack.pop_back();
				}else{
					Vec.push_back(a);
				}
			}else{
				Vec.push_back(a);
				Stack.push_back(1);
			}
		}
		printf("%d\n", Vec.size());
	}
    return 0;
}
