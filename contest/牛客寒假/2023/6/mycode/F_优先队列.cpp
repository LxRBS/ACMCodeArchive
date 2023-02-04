/**
 * 给定N长度的数组A，每次操作可以将ai改成f(ai)，f(ai)表示ai的二进制的1的数量
 * 现在有Q个询问，每次给出k，问操作k次，数组A的最大值最小是多少
 * Q个询问是独立的。
 * 注意到如果对同一个位置反复操作会迅速令ai变为1，达到驻点。
 * 因此所有可能的操作总数是有限的，超过这个限制，询问的答案肯定是1
 * 所以可以事先求出每一个k次操作的答案，记录在Ans[k]里面。后面直接回答即可
 * 使用优先级队列求即可。每次取出当前最大的数h，记录当前的答案。然后令h = f(h)，再塞回队列。
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
int const SIZE = 1E6+10;
#endif


using llt = long long;
using vll = vector<llt>;
using vi = vector<int>;

int N, Q;
vi A;
vi Ans;

void init(){
    Ans.reserve(1000000);
    priority_queue<int> q;
    for(auto i : A) q.push(i);
    
    while(!q.empty()){
        auto h = q.top(); q.pop();
        Ans.emplace_back(h);

        auto t = __builtin_popcount(h);
        if(t != 1) q.push(t);
    }
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    // ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    // test();
    N = getInt(); Q = getInt();
    A.assign(N, 0);
    for(auto & i : A) i = getInt();
    
    init();

    for(int k,q=1;q<=Q;++q){
        k = getInt();
        if(k < Ans.size()){
            printf("%d\n", Ans[k]);
        }else{
            printf("1\n");
        }
    }
    return 0;
}