/**
 * 使用默认哈希会被hack
 */
#include <assert.h>
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
int const SIZE = 1E5+13;
#endif

using pii = pair<int, int>;
using vpii = vector<pii>;
using vi = vector<int>;

size_t Seed;
vpii G[SIZE];
int N, A, B;
int D[SIZE], Z[SIZE];
bool Flag[SIZE];
unordered_set<int, function<size_t(int)>, function<bool(int, int)>> S(
    1000000,
    [](int x)->size_t{return x ^ Seed;},
    [](int a, int b){return a == b;}
);

bool proc(){
    S.clear();
    fill(Flag, Flag+N+1, false);
    queue<int> q;
    q.push(B); D[B] = 0; Flag[B] = true;
    while(!q.empty()){
        int h = q.front(); q.pop();
        for(auto p : G[h]){
            int v = p.first;
            if(Flag[v]) continue;
            
            Flag[v] = true;
            S.insert(D[v] = D[h] ^ p.second);
            q.push(v);
        }
    }

    if(S.count(0)) return true;

    fill(Flag, Flag+N+1, false);
    q.push(A); Flag[A] = true; Z[A] = 0;
    while(!q.empty()){
        int h = q.front(); q.pop();
        for(auto p : G[h]){
            int v = p.first;
            if(Flag[v]) continue;
            if(v == B) continue;

            Flag[v] = true;
            if(S.count(Z[v] = Z[h] ^ p.second)) return true;
            q.push(v);
        }
    }
    return false;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r" ,stdin);
#endif    
    srand((unsigned)time(nullptr));
    Seed = rand();
    int nofkase = getInt();
	while(nofkase--){
        N = getInt(); A = getInt(); B = getInt();
        for(int i=1;i<=N;++i) G[i].clear();
        for(int a,b,w,i=1;i<N;++i){
            a = getInt();
            b = getInt();
            w = getInt();
            G[a].emplace_back(b, w);
            G[b].emplace_back(a, w);
        }
        puts(proc()?"YES":"NO");
	}
    return 0;
}
