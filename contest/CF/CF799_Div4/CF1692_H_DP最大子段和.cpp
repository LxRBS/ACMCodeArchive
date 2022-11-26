/**
 * 给定数组，选定如下三元组(a, s, e)，做如下操作，初始x=1
 * 在数组A[s...e]中，如果Ai==a，则x乘2，否则x除以2
 * 目标是使得x最大，求这个三元组
 * 显然要关心数组元素值的数量以及分布区间，做一个计数器，记住每一个数值出现的区间范围
 * 假设对某个值v，其在数组中出现的范围分别记作:(si, ei)
 * 再令di为以(si, ei)结尾的最大能得到的值，显然
 * di = max(ei-si+1, d[i-1]-(si-e[i-1]-1)+ei-si+1)
 * 即要么将i单独做一段，要么将i连接上前一段，本质上就是一个最大子段和。
 * 更新最大值的同时更新方案即可
 * 最多有N段，因此是O(N)的。
 * 标程用了线段树，动态求最大子段和，O(NlogN).
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
int const SIZE = 18;
#else
int const SIZE = 2E5+13;
#endif

using pii = pair<int, int>;
using vpii = vector<pii>;
using mii = unordered_map<int, vpii>;

int N ;
int A[SIZE];
mii C;

void proc(){
    C.clear();
    int cur = 1;
    while(1){
        int k = cur;
        while(k <= N && A[k] == A[cur]) ++k;
        C[A[cur]].emplace_back(cur, k-1);

        if((cur = k) > N) break;
    }

    tuple<int, int, int, int> ans = {A[1], 1, 1, 1};
    auto check = [&](int t, int a, int s, int e){
        if(t > get<3>(ans)){
            ans = {a, s, e, t};
        }
    };
    for(const auto & p : C){
        auto anchor = p.first;
        auto && vec = p.second;
        int n = vec.size();
        vector<int> d(n, 0);
        d[0] = vec[0].second - vec[0].first + 1;
        check(d[0], anchor, vec[0].first, vec[0].second);
        int left = vec[0].first;
        for(int i=1;i<n;++i){
            int tmp = vec[i].second - vec[i].first + 1;
            int kong = vec[i].first - vec[i-1].second - 1;
            if(d[i-1] >= kong){
                d[i] = d[i-1] - kong + tmp;
                check(d[i], anchor, left, vec[i].second);
            }else{
                d[i] = tmp;
                left = vec[i].first;
                check(d[i], anchor, left, vec[i].second);
            }
        }
    }
    printf("%d %d %d\n", get<0>(ans), get<1>(ans), get<2>(ans));
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int nofkase = getInt();
    for(int kase=1;kase<=nofkase;++kase){
        N = getInt();
        for(int i=1;i<=N;++i) A[i] = getInt();
        // printf("%d: ", kase);
        proc();
    }
    return 0;
}
