/**
 * 给一个无向图，问从1出发能够到达的最大节点编号
 * 做一个广搜即可，维持一个全局答案
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

using llt = long long;
using pii = pair<int, int>;
using vi = vector<int>;

int N;
unordered_map<int, vi> G;
unordered_set<int> Flag;

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r" ,stdin);
#endif
    N = getInt();
    for(int a,b,i=0;i<N;++i) {
        a = getInt();
        b = getInt();
        G[a].push_back(b);
        G[b].push_back(a);
    }
    queue<int> q;
    q.push(1);
    Flag.insert(1);

    int ans = 1;
    while(!q.empty()){
        int h = q.front(); q.pop();
        for(auto v : G[h]){
            if(Flag.count(v)) continue;
            ans = max(ans, v);
            q.push(v);
            Flag.insert(v);
        }
    }
    printf("%d\n", ans);
    return 0;
}
