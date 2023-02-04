/**
 * N(1E5)个人，M(500)条指令，每条指令代价为B，命令N个人每x个人抱团，没抱团的淘汰
 * 问为了剩下最少的人，所花的最小代价是多少
 * 令 Di 为剩下i个人的最小代价，能够到达i的数量不太好求，但是从i能够到达的j比较容易求
 * 因此使用DP中的刷表法，也就是松弛操作。
 * 在Di已经求出的情况下，遍历指令，对每条指令，可以去向j，可以求出经过i到j的代价，视情况更新答案。
 * O(NM)
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
int const SIZE = 22;
#else
int const SIZE = 110;
#endif

using llt = long long;
using pii = pair<int, int>;
using vpii = vector<pii>;
using vi = vector<int>;

vpii A;
int N, M;
vector<llt> D;


int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
#endif
    N = getInt();
    M = getInt();
    A.reserve(M);
    for(int b,x,i=0;i<M;++i){
        b = getInt(); x = getInt();
        A.emplace_back(x, b);
    }
    sort(A.begin(), A.end());

    D.assign(N+1, -1);
    D[N] = 0;
    for(int i=N;i>=1;--i){
        auto di = D[i];
        if(-1 == di) continue;
        for(const auto & p : A){
            if(i <= p.first) break;

            auto tmp = D[i] + p.second;
            auto j = i - i % p.first;
            if(-1 == D[j] || tmp < D[j]) D[j] = tmp;
        }
    }
    for(int i=0;;++i){
        if(-1 != D[i]){
            cout << D[i] << endl;
            break;
        }
    }
    return 0;
}