/**
 * 给定N个点的坐标，并且给定前进方向，只能向左或者向右
 * 问是否会发生碰撞
 * 对所有y坐标相同的，按x坐标排序，然后从左向右检查即可
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
typedef unordered_map<int, vector<pii> > _map_t;
int N;
vector<pii> Pos;
char A[SIZE];
_map_t Map;

bool proc(){
    for(int i=0;i<N;++i){
        Map[Pos[i].second].emplace_back(Pos[i].first, 'R'==A[i]?0:1);
    }
    for(auto &p: Map){
        int x = p.first;
        auto &vec = p.second;
        sort(vec.begin(), vec.end());
        int k = 0;
        int n = vec.size();
        while(k<n && vec[k].second!=0) ++k;
        if(k == n) continue;
        int t = k + 1;
        while(t < n && vec[t].second != 1) ++t;
        if(t == n) continue;
        return true;
    }
    return false;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    scanf("%d", &N); Pos.reserve(N);
    for(int a,b,i=0;i<N;++i){
        scanf("%d%d", &a, &b);
        Pos.emplace_back(a, b);
    }
    scanf("%s", A);
    puts(proc()?"Yes":"No");
    return 0;
}