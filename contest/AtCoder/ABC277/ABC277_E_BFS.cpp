/**
 * 无向图，每条边上有一个权值{0, 1}，取0表示不通，取1表示通
 * 某些点上有开关，如果走到有开关的点上，就可以选择按一下开关，则每条边的权值都会取反
 * 问从1走到N最少走几步？ 按开关不计算在步数之内
 * 注意到开关本身是没有区别的，且连按两次开关和没有按是一样的
 * 因此令A[i]是从1到i的最短距离且开关按了偶数次，令Bi是从1到i的最短距离且开关按了奇数次
 * 而且每条边的长度都是1，所以用一个广搜即可
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
using vpii = vector<pii>;

int N, M, K;
vpii G[SIZE];
bool Switch[SIZE] = {false};

int A[SIZE], B[SIZE];

int bfs(){
    memset(A, -1, sizeof(A));
    memset(B, -1, sizeof(B));
    queue<pii> q;
    q.push({1, 0});
    A[1] = 0;
    if(Switch[1]) {
        q.push({1, 1});
        B[1] = 0;
    }

    int d = 0;
    while(1){
        int sz = q.size();
        if(0 == sz) break;
        ++d;
        while(sz--){
            auto h = q.front(); q.pop();
            for(auto p : G[h.first]){
                if((h.second+p.second)%2==0) continue;
                if(A[p.first] != -1 && B[p.first] != -1) continue;

                if(p.first == N) return d;

                if(h.second%2 == 0){
                    if(A[p.first] == -1){
                        A[p.first] = d;
                        q.push({p.first, h.second});
                        if(Switch[p.first]){
                            q.push({p.first, h.second+1});
                        }
                    }
                }else{
                    if(B[p.first] == -1){
                        B[p.first] = d;
                        q.push({p.first, h.second});
                        if(Switch[p.first]){
                            q.push({p.first, h.second+1});
                        }
                    }
                }

            }
        }
    }
    return -1;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r" ,stdin);
#endif
    N = getInt(); M = getInt(); K = getInt();
    for(int u,v,a,i=1;i<=M;++i){
        u = getInt();
        v = getInt();
        a = getInt();
        G[u].emplace_back(v, a);
        G[v].emplace_back(u, a);
    }
    for(int i=0;i<K;++i){
        Switch[getInt()] = true;
    }

    int ans = bfs();
    cout << ans << endl;
    return 0;
}
