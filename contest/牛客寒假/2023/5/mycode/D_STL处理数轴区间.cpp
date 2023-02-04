/**
 * 使用pair表示区间，使用set维护区间
 * 有新的插入，就去找到相应位置，根据已有内容合并生成新的区间，将新区间插入，
 * 删除需要删除的空间即可。
 * 使用STLset，所有操作均为log级别。
 */
#include <bits/stdc++.h>
using namespace std;

#include <bits/extc++.h>
using namespace __gnu_pbds;

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
int const SIZE = 810;
#endif

using pii = pair<int, int>;
using TreeTy = set<pii>;
using vpii = vector<pii>;

int const INF = 2000000000;

TreeTy Sha, Ya;
int N;
vpii A, B;

int proc(TreeTy & tree, int a, int b){
    pii toInsert;
    TreeTy::iterator toDelBegin, toDelEnd;

    auto sit = tree.lower_bound({a, INF});
    assert(sit != tree.begin() && sit != tree.end() && sit->first > a);
    --sit;

    if(sit->second+1 >= a){
        toInsert.first = sit->first;
        toDelBegin = sit;
    }else{
        toInsert.first = a;
        toDelBegin = ++sit;
    }

    auto eit = tree.lower_bound({b, INF});
    assert(eit != tree.begin() && eit != tree.end() && eit->first > b);

    if(eit->first == b + 1){
        toInsert.second = eit->second;
        toDelEnd = ++eit;
    }else{
        toDelEnd = eit;
        --eit;
        toInsert.second = max(eit->second, b);
    }

    if(toDelBegin != toDelEnd){
        tree.erase(toDelBegin, toDelEnd);
    }
    tree.insert(toInsert);

    return tree.begin()->second;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    // ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    Sha.insert({0, 0});
    Ya.insert({0, 0});
    Sha.insert({INF, INF});
    Ya.insert({INF, INF});
    
    N = getInt();
    A.reserve(N); B.reserve(N);
    for(int i=0;i<N;++i){
        int a = getInt();
        int b = getInt();
        A.emplace_back(a, b);
    }
    for(int i=0;i<N;++i){
        int a = getInt();
        int b = getInt();
        B.emplace_back(a, b);
    }

    for(int a,b,i=0;i<N;++i){
        auto sha = proc(Sha, A[i].first, A[i].second);
        auto ya = proc(Ya, B[i].first, B[i].second);
        // disp(Sha);disp(Ya);
        // printf("sha = %d, ya = %d\n", sha, ya);
        if(sha == ya){
            printf("win_win!\n0\n");
        }else if(sha > ya){
            printf("sa_win!\n%d\n", sha - ya);
        }else{
            printf("ya_win!\n%d\n", ya - sha);
        }         
    }
    return 0;
}