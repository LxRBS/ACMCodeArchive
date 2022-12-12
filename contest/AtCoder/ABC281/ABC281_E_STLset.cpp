/**
 * 给定一个长度为N的数组A，再给定M和K，要求对A中的每M个数，求出其前K小数之和
 * 弄两个set，用KSet记录前K小数，XSet记录剩下的M-K个数，用ans记录KSet中的数的和
 * 对每一个Ai，将A[i-M]从集合中删除，将Ai加入集合
 * 并根据情况维护和ans即可
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

using llt = long long;
using pii = pair<llt, int>;
using SetTy = multiset<pii>;

int N, M, K;
vector<int> A;

SetTy KSet, XSet;

void proc(){
    A.assign(N+1, 0);
    llt ans = 0;
    for(int i=1;i<=M;++i){
        ans += A[i] = getInt();
    }
    printf("%lld ", ans);
    for(int i=M+1;i<=N;++i){
        ans += A[i] = getInt();
        ans -= A[i-M];
        printf("%lld ", ans);
    }
    printf("\n");
}


llt proc(int index, llt ans){
    /// 首先将A[index-M]删除，从XSet或者从KSet
    pii p = {A[index-M], index-M};
    if(XSet.count(p)){
        XSet.erase(p);
    }else{ // 一定在KSet里面
        KSet.erase(p);
        ans -= p.first;
        /// 从KSet中删除一个，就要从XSet中加入一个
        auto tmp = *XSet.begin();
        XSet.erase(XSet.begin());
        KSet.insert(tmp);
        ans += tmp.first;
    }
    /// 然后将A[index]加入
    p = *--KSet.end();
    if(A[index] >= p.first){
        XSet.insert({A[index], index});
    }else{ /// 要加入KSet 
        KSet.erase(--KSet.end());
        ans -= p.first;
        ans += A[index];
        KSet.insert({A[index], index});
        XSet.insert(p);
    }
    return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    N = getInt();
    M = getInt();
    K = getInt();
    if(K == M) return proc(), 0;

    A.assign(N+1, 0LL);
    vector<pii> vec(M+1);
    for(int i=1;i<=M;++i){
        A[i] = vec[vec[i].second = i].first = getInt();
    }
    sort(vec.begin()+1, vec.end());
    llt ans = 0;
    for(int i=1;i<=K;++i){
        ans += vec[i].first;
        KSet.insert(vec[i]);
    }
    for(int i=K+1;i<=M;++i) XSet.insert(vec[i]);
    printf("%lld ", ans);
    for(int i=M+1;i<=N;++i){
        A[i] = getInt();
        printf("%lld ", ans = proc(i, ans));
    }
    printf("\n");
    return 0;
}