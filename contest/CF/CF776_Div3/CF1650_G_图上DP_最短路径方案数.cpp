/**
 * 给定一个无向图，给定S和T，假设S到T的最短路径长度为d，
 * 求S到T的路径长度为d或者d+1的路径的数量。
 * 假设Di为S到i的路径数量，Di=SIGAM{Dj, j到i有一条边}
 * 考虑使用刷表法，配合队列，对当前每一个j，令Di += Dj，j到i有一条边
 * 同时需要记录两个D，D0表示最短距离的数量，D1表示比最短距离多1的数量
 * 同时为了控制距离，使用成批扩展的BFS
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
int const SIZE = 15;
#else
int const SIZE = 2E5+5;
#endif

typedef long long llt;
llt const MOD = 1E9+7;

typedef vector<int> vi;
struct _q_t : public queue<int>{
    void clear(){c.clear();}
}Q;

int N, M, S, T;
vi G[SIZE];
llt D[2][SIZE];
int Cnt[SIZE];
int A[SIZE];

llt proc(){
    fill(A, A+N+1, 0);
    fill(Cnt, Cnt+N+1, 0);
    fill(D[0], D[0]+N+1, 0);
    fill(D[1], D[1]+N+1, 0);

    Q.clear(); Q.push(S);
    D[0][S] = 1;
    int k = 0;
    int d = 2000000000;
    
    while(!Q.empty()){
        ++k;
        int sz = Q.size();
        while(sz--){
            int h = Q.front(); Q.pop();
            int b = 0;
            if(h > MOD) h -= MOD, b = 1;
            for(auto v: G[h]){
                if(v == S) continue;
                if(v == T && k < d) d = k; // 用来求最短路径
                if(0 == Cnt[v]){ // 说明v是第一次入队
                    A[v] = k;
                    Cnt[v] = 1;
                    (D[0][v] += D[b][h]) %= MOD;
                    Q.push(v);
                }else if(1 == Cnt[v]){
                    if(k == A[v]){ // 说明v此时还在队列中，是同一批
                        (D[0][v] += D[b][h]) %= MOD;
                    }else if(k > A[v]){ // 说明v此时不在队列中，需要第二次入队
                        A[v] = k;
                        ++Cnt[v];
                        (D[1][v] += D[b][h]) %= MOD;
                        Q.push(v + MOD);                            
                    }
                }else if(2 == Cnt[v]){ // 说明v此时还在队列中，是同一批
                    if(k == A[v]){
                        (D[1][v] += D[b][h]) %= MOD;                   
                    }
                }else{
                    throw runtime_error("XXX");
                }
            }
        }
        if(d + 1 == k) break;
    }
    return (D[0][T] + D[1][T]) % MOD;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    int nofkase = getInt();
    while(nofkase--){
        N = getInt(); M = getInt();
        S = getInt(); T = getInt();
        for(int i=1;i<=N;++i) G[i].clear();
        for(int a,b,i=0;i<M;++i){
            a = getInt();
            b = getInt();
            G[a].push_back(b);
            G[b].push_back(a);
        }
        printf("%lld\n", proc());
    }
    return 0;
}
