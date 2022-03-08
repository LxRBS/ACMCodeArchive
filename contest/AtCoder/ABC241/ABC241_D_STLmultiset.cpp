/**
 * A集合，初始为空，Q个操作：
 * 1 x：插入x
 * 2 x k：在A中找小于等于x的第k大
 * 3 x k：在A中找大于等于x的第k小
 * 因为k不超过5，所以可以直接使用STLmultiset
*/
#include <bits/stdc++.h>
using namespace std;

char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)

typedef long long llt;

llt getInt(){
	int sgn = 1;
	char ch = __hv007();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = __hv007();
	if ( '-' == ch ) {sgn = 0;ch=__hv007();}

	llt ret = (llt)(ch-'0');
	while( '0' <= (ch=__hv007()) && ch <= '9' ) ret = ret * 10 + (llt)(ch-'0');
	return sgn ? ret : -ret;
}

#ifndef ONLINE_JUDGE
int const SIZE = 13;
#else
int const SIZE = 10030;
#endif  


typedef multiset<llt> _set_t;
_set_t Set;

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    int q = getInt();
	for(int cmd, qi=1;qi<=q;++qi){
        if(1 == (cmd=getInt())){
            llt x = getInt();
			Set.insert(x);
		}else if(2 == cmd){
            llt x = getInt();
			int k = getInt();
			auto p = Set.equal_range(x);
			auto it = p.second;
			while(it != Set.begin() && k) --it, --k;
			if(k) puts("-1");
			else printf("%lld\n", *it);
		}else if(3 == cmd){
            llt x = getInt();
			int k = getInt();
			auto p = Set.equal_range(x);      
			auto it = p.first;
            while(it != Set.end() && k) ++it, --k;
			if(k) puts("-1");
			else printf("%lld\n", *--it);
		}else{
			throw runtime_error("XXX");
		}
	}
    return 0;
}

