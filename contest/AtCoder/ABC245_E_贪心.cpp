/**
 * 给N个矩形，给定宽和高
 * 再给定M个矩形作为盒子，也有宽和高，且M大于N
 * 问是否能将前N个矩形装入后M个盒子中，一个装一个
 * N和M在2e5
 * 贪心，只选最靠近的盒子装即可
 * 首先所有矩形按w排序，w相同将盒子排在前面
 * 然后for一遍，如果是盒子就放入set中
 * 如果是矩形，就在set中找一个h最靠近的即可
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
int const SIZE = 10;
#else
int const SIZE = 2E5+5;
#endif

struct _t{
    int w;
    int h;
    int idx;
}A[SIZE<<1];

function<bool(const _t&, const _t&b)> cmp = [](const _t &a, const _t&b){
    if(a.h != b.h) return a.h < b.h;
    if(a.idx != b.idx) return a.idx > b.idx;
    return a.w < b.w;
};

multiset<_t, function<bool(const _t&, const _t&b)> > Set(cmp);

int N, M;

bool proc(){
    sort(A, A+N+M, [](const _t &a, const _t&b){
        if(a.w != b.w) return a.w > b.w;
        return a.idx < b.idx;
    });

    for(int i=0;i<N+M;++i){
        const _t &a = A[i];
        if(1 == a.idx){
            Set.insert(a); continue;
        }

        auto it = Set.lower_bound(a);
        if(it == Set.end()) return false;
        Set.erase(it);
    }
    return true;
}

int main() {    
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    N = getInt(); M = getInt();
    for(int i=0;i<N;++i){
        A[i].w = getInt();        
        A[i].idx = 2;
    }
    for(int i=0;i<N;++i) A[i].h = getInt();
    for(int i=N;i<M+N;++i){
        A[i].w = getInt();
        A[i].idx = 1;
    }
    for(int i=N;i<N+M;++i) A[i].h = getInt();
    puts(proc()?"Yes":"No");
    return 0;
}

