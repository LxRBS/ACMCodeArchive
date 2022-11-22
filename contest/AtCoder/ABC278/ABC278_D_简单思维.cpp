/**
 * 一个N长度的数组A，三种操作：
 * 1 x： 将A中所有元素赋值为x
 * 2 i x：令Ai加x
 * 3 i：打印Ai的值
 * 设置两个全局变量，记录1操作即可，2操作直接做
 * 3操作需要查询全局变量视情况而定
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
using llt = long long;

msi Map;
int N, Q;
llt A[SIZE];
llt Level;
si flag;
void proc(){
    int cmd = getInt(); 
    if(1 == cmd){
        llt x = getInt();
        Level = x;
        flag.clear();
    }else if(2 == cmd){
        int pos = getInt();
        llt x = getInt();
        if(-1 == Level){
            A[pos] += x;
        }else{
            auto it = flag.find(pos);
            if(it == flag.end()){
                A[pos] = Level + x;
                flag.insert(it, pos); 
            }else{
                A[pos] += x;
            }
        }
    }else{
        int pos = getInt();
        if(-1 == Level){
            printf("%lld\n", A[pos]);
        }else if(flag.count(pos)){
            printf("%lld\n", A[pos]);
        }else{
            printf("%lld\n", Level);
        }
    }
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r" ,stdin);
#endif
    N = getInt(); 
    for(int i=1;i<=N;++i) A[i] = getInt();
    Q = getInt();
    Level = -1;
    while(Q--) proc();
    return 0;
}
