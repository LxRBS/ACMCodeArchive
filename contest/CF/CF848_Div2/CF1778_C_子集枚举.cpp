/**
 * 给定字符串A和B，其中A中互异的字母最多只有10个
 * 现在可以更改A中的字母，改动的字母类型最多不超过K种
 * 问改完以后，任意(i, j)满足A[i:j] == B[i:j]一共有多少对
 * 首先，显然有贪心原则，能改动的字母越多越好，所以肯定是顶格
 * 其次注意到能修改的不同字母组合是C(10, K)，最大也就252
 * 最后，枚举(i, j)其实只需要O(N)即可，N在1E5
 * 因此总数是O(2.5E7)
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
int const SIZE = 1E5+10;
#endif

using llt = long long;
using pii = pair<int, int>;
using vpii = vector<pii>;
using vi = vector<int>;

int N, K;
char A[SIZE], B[SIZE];
vector<char> Alpha;
vector<char> Select;
llt Ans;

llt proc(const vector<char> & vec){
    const set<char> ss(vec.begin(), vec.end());

    llt ans = 0LL;
    int k = 0;
    while(1){
        int offset = 0;
        while(k + offset < N && (A[k + offset] == B[k + offset] || ss.count(A[k + offset]))){
            ++offset;
        }    
        ans += (offset + 1LL) * offset / 2;
        if(N == (k += offset)) break;

        while(k < N && A[k] != B[k] && !ss.count(A[k])) ++k;
        if(k == N) break;
    }
    return ans;
}

void dfs(int cur){    
    if(K == Select.size()){
        Ans = max(Ans, proc(Select));
        return;
    }
    if(cur == Alpha.size()) return;

    Select.emplace_back(Alpha[cur]);
    dfs(cur + 1);
    Select.pop_back();

    dfs(cur + 1);
    return;
}

llt proc(){
    Alpha.clear();
    Select.clear();
    int cnt[256] = {0};
    for(char const *p=A;*p;++p){
        if(1 == ++cnt[*p]) Alpha.emplace_back(*p);
    }
    int n = Alpha.size();
    K = min(n, K);
    Ans = 0;
    dfs(0);
    return Ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    // ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int nofkase; scanf("%d", &nofkase);
    while(nofkase--){
        scanf("%d%d%s%s", &N, &K, A, B);
        printf("%lld\n", proc());
    }
    return 0;
}