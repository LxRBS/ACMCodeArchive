/**
 * 给定平面上的若干个点，对每个点求曼哈顿距离最近的且不在给定点集中的点
 * 首先，假设给定点周围有空位，显然这个点的最近点就很容易求得
 * 比较麻烦的是被围在中间的点，但是可以发现这些点的最近点一定是某个外围的最近点
 * 所以答案一定是之前已经出现过的
 * 写一个BFS即可
 * 使用unordered_map超时，4sTLE，使用map只跑了654ms
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

typedef pair<int, int> pii;
struct pair_hash{
	inline size_t operator()(const pii&p)const{
		return p.first * 1331 + p.second;
	}	
};
typedef map<pii, int> _set_t;

int const DR[] = {-1, 1, 0, 0};
int const DC[] = {0, 0, -1, 1};

int N;
pii A[SIZE];
pii B[SIZE];
_set_t Set;
bool Flag[SIZE];
queue<int> Q;

void proc(){
    for(int nr,nc,i=1;i<=N;++i){
        const pii & a = A[i];
        for(int o=0;o<4;++o){
            nr = a.first + DR[o];
            nc = a.second + DC[o];
            if(Set.count({nr, nc})) continue;
            B[i] = {nr, nc};
            if(!Flag[i]){
                Q.push(i); Flag[i] = true;
            }
        }
    }

    while(!Q.empty()){
        int h = Q.front(); Q.pop();
        const pii & a = A[h];
        for(int nr,nc,o=0;o<4;++o){
            nr = a.first + DR[o];
            nc = a.second + DC[o];
            auto it = Set.find({nr, nc});
            if(Set.end() == it || Flag[it->second]) continue;
            B[it->second] = B[h];
            Flag[it->second] = true;
            Q.push(it->second);
        }
    }

    for(int i=1;i<=N;++i)printf("%d %d\n", B[i].first, B[i].second);
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    N = getInt();
    for(int i=1;i<=N;++i){
        A[i].first = getInt();
        A[i].second = getInt();
        Set.insert({A[i], i});
    }
    proc();
    return 0;
}