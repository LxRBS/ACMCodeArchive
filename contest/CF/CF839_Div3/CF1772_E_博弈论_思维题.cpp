/**
 * 给定一个排列，每个元素初始都是红色，A和B俩人下棋
 * 1 任意排列蓝色元素的位置，红色元素位置不变
 * 2 将一个红色元素的颜色改为蓝色
 * 3 略过此轮
 * 如果排列变成升序，则A获胜；降序则B获胜；也有可能平局
 * 给定初始，问结果
 * 如果某人将最后一个红色改为蓝色，则下一步另外一个人必胜，因此每个人均会保证排列中有红色
 * 在保证红色的情况下还要获胜，设本来就升序的元素记作X，降序的记作Y
 * 对A而言，获胜的条件就是X还有红色，其他都已经是蓝色。
 * 因此A的最佳策略就是将Y及其他位置挨个改成蓝色，B的最佳策略就是改X和其他位置
 * 谁先改完，在下一轮用1操作就能获胜，注意A是先手，因此略有区别。
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
int const SIZE = 2E5+10;
#endif

using llt = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using mvi = map<int, vi>;

int N;
vi A;

int proc(){
    int a = 0, b = 0, c = 0;
    for(int i=0;i<N;++i){
        if(A[i] == i + 1) ++a;
        if(A[i] == N - i) ++b;
        if(A[i] != i + 1 && A[i] != N - i) ++c;
    }
    if(b + c <= a) return 1;
    if(a + c < b) return 2;
    return 0;
}

char const Output[][22] = {
    "Tie", "First", "Second"
};

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int nofkase = getInt();
    while(nofkase--){
        A.assign(N = getInt(), 0);
        for(int & i : A) i = getInt();
        puts(Output[proc()]);      
    }
    return 0;
}


