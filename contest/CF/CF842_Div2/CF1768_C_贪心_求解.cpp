/**
 * 给定一个数组A，求两个排列p和q，使得Ai = max(pi, qi)，有可能无解
 * 贪心，对Ai从小到大，考虑某个Ai：
 * p、q之中必有一个Ai，另一个只需选取当前能选的最小的即可，如果当前最小的已经超过了Ai，则NO
 * 如果Ai出现了2次，则是一样的办理
 * 如果Ai出现了3次，则NO
 * 从小到大整理Ai及其位置需要NlogN，后续处理O(N)
 * 标程也是O(NlogN)，但是在前处理中就有更多的判断NO的方法，因此要更快
 * 还有一个O(N)的方法
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
using pii = pair<int, int>;
using ppii = pair<int, pii>;
using vppii = vector<ppii>;
using vi = vector<int>;
using vvi = vector<vi>;
using mvi = map<int, vi>;
using vs = vector<string>;
using vvs = vector<vs>;


int N;
vi A, B, C;
mvi Map;

bool test(){
    for(int i=0;i<N;++i)if(max(B[i], C[i]) != A[i]) return false;
    return true;
}

bool use(vi & ans, vi & flag, int pos, int limit, int & cur){
    while(cur <= limit && flag[cur]) ++cur;   
    if(limit + 1 == cur) return false;

    ans[pos] = cur++;
    return true;   
}

void proc(){
    B.assign(N, 0);
    C.assign(N, 0);
    Map.clear();
    for(int i=0;i<N;++i){
        auto & vec = Map[A[i]];
        vec.push_back(i);
        if(vec.size() >= 3) return (void)printf("NO\n");
    }

    vi flagb(N+1, 0);
    vi flagc(N+1, 0);
    int b = 1, c = 1;
    for(const auto & p : Map){
        int cur = p.first;
        const auto & pos = p.second;
        
        if(1 == pos.size()){
            if(flagb[cur] && flagc[cur]) return (void)printf("NO\n");
            if(flagb[cur]){
                if(!use(B, flagb, pos[0], cur, b)) return (void)printf("NO\n");
                flagc[C[pos[0]] = cur] = 1;                
            }else{
                if(!use(C, flagc, pos[0], cur, c)) return (void)printf("NO\n");
                flagb[B[pos[0]] = cur] = 1;
            }
        }else{
            if(flagb[cur] || flagc[cur]) return (void)printf("NO\n"); 
            if(!use(C, flagc, pos[0], cur, c)) return (void)printf("NO\n");
            flagb[B[pos[0]] = cur] = 1;
            if(!use(B, flagb, pos[1], cur, b)) return (void)printf("NO\n");
            flagc[C[pos[1]] = cur] = 1;
        }
    }

    printf("YES\n");
    for(int i : B) printf("%d ", i); printf("\n");
    for(int i : C) printf("%d ", i); printf("\n");
    assert(test());
    return;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int nofkase = getInt();
    while(nofkase--){
        A.assign(N = getInt(), 0);
		for(int & i : A) i = getInt();
		proc();
    }

    return 0;
}


