/**
 * N个人，三种操作：
 * 1 a b：a和b建立跟随关系，注意跟随关系是有向的
 * 2 a b：a和b撤销跟随关系
 * 3 a b：如果a和b互相跟随，输出Yes，否则输出No
 * 使用map记录跟随关系即可
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
int const SIZE = 2E5+13;
#endif

using si = unordered_set<int>;
using msi = unordered_map<int, si>;

msi Map;
int N, Q;

void proc(){
    int cmd = getInt();
    int a = getInt();
    int b = getInt();

    if(1 == cmd){
        Map[a].insert(b);
    }else if(2 == cmd){
        Map[a].erase(b);
    }else{
        if(Map[a].count(b) && Map[b].count(a)){
            puts("Yes");
        }else{
            puts("No");
        }
    }
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r" ,stdin);
#endif
    N = getInt(); Q = getInt();
    while(Q--){
        proc();
    }
    return 0;
}
