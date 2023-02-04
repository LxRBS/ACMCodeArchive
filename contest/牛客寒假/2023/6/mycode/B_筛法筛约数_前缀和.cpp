/**
 * 给定N长度数组A，再给定Q个操作，两种类型
 * 1 x：在A后面添加x
 * 2 x：查询Ax之后有多少Ai是Ax的倍数
 * N/Q/Ai均在2E5
 * 2E5以内约数数量最多的数是166320和196560，均有160个约数。
 * 因此可以考虑O(160N)的做法。
 * 首先筛法筛出2E5内所有数的各自的约数。这一步是O(NlogN)
 * 令Di记录i的倍数出现的数量，每添加一个Ai，如果x是Ai的约数，就++D[x]
 * 同时记录一个U[i] = D[Ai]，在每一个Ui都记录了到i位置为止Ai的倍数的数量
 * 对于询问操作，D[Ax]是当前所有Ax的倍数数量，再减去Ux即可
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

using vi = vector<int>;
using vvi = vector<vi>;

int N, Q;
vi A;
vvi Fac;
vi D, U;

void init(){
    int sz = 200000+1;
    D.assign(sz, 0);
    Fac.assign(sz, vi());
    for(int i=1;i<sz;++i){
        for(int j=i;j<sz;j+=i){
            Fac[j].emplace_back(i);
        }
    }
    
    // sz = 0;
    // for(const auto & vec : Fac){
    //     sz = max(sz, (int)vec.size());
    // }
    // cout << sz << endl;
    return;
}

void proc(int pos, int val){
    for(auto i : Fac[val]) ++D[i];
    U[pos] = D[val];
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    // ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    init();    
    N = getInt(); Q = getInt();
    A.reserve(N + Q + 1); A.push_back(0);
    U.assign(N+N+1, 0);
    for(int a,i=1;i<=N;++i){
        a = getInt();
        A.emplace_back(a);
        proc(i, a);
    }
    int k = 0;
    for(int op,x,i=1;i<=Q;++i){
        op = getInt(); x = getInt();
        if(1 == op){
            A.emplace_back(x);
            proc(N + (++k), x);
        }else{
            printf("%d\n", D[A[x]] - U[x]);
        }
    }
    return 0;
}