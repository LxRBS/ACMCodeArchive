/**
 * N个人，每个人有一个社交量ai，
 * 即第i个人只能跟ai个人谈话，然后就会离开
 * 问最多能发生多少次谈话。
 * 其实就是给定度数限制，问最多能连多少条边
 * 贪心法：每次选度数最大的两个点连边，直到完毕。
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

typedef pair<int, int> pii;
#define fi first
#define se second

#ifndef ONLINE_JUDGE
int const SIZE = 13;
#else 
int const SIZE = 200010;
#endif

int N;
int A[SIZE];

set<pii> Set;
vector<pii> Ans;

void proc(){
    Set.clear();
    Ans.clear();
    
    for(int i=1;i<=N;++i){
        if(A[i]){
            Set.insert({A[i], i});
        }
    }

    while(Set.size() > 1){
        pii p1 = *--Set.end();
        Set.erase(--Set.end());

        pii p2 = *--Set.end();
        Set.erase(--Set.end());

        Ans.push_back({p2.se, p1.se});
        
        if(--p1.fi) Set.insert(p1);
        if(--p2.fi) Set.insert(p2);
    }

    printf("%d\n", Ans.size());
    for(auto pp: Ans){
        printf("%d %d\n", pp.fi, pp.se);
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int nofkase = getInt();
    while(nofkase--){
        N = getInt();
        for(int i=1;i<=N;++i)A[i] = getInt();
        proc();
    }
    return 0;
}