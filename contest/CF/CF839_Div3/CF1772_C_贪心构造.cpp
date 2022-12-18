/**
 * 构造一个K个元素的数组，内容只能从1到N，要求
 * 1 数组严格升序
 * 2 相邻元素之差的不同值的数量最多
 * 贪心即可，从1、2、4、7、11...
 * 不行的话就挨个加1即可
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
int const SIZE = 23;
#else
int const SIZE = 2E5+10;
#endif

using llt = long long; 
using vi = vector<int>;
using si = set<int>;
using vvi = vector<vi>;
using msi = map<int, si>;
using pii = pair<int, int>;
using vpii = vector<pii>;
using t3t = tuple<int, int, int>;

int N, K;
void proc(){
    vi vec;
	vec.push_back(1);
	int t = 1;
	int left = K - 1;
	while(1){
		if(vec.back() + t <= N - left + 1){
            vec.push_back(vec.back() + t);
			++t; --left;
			if(vec.size() == K) break;
		}else{
            break;
		}
	}
	while(vec.size() != K){
		vec.push_back(vec.back() + 1);
	}
	for(int i : vec) printf("%d ", i);
	printf("\n");
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int nofkase = getInt();
	while(nofkase--){
        K = getInt(); N = getInt();
		proc();
	}
    return 0;
}


