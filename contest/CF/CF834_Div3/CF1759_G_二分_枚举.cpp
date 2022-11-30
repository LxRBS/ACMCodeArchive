/**
 * 给定一个偶数N，再给定一个长度为N/2的B数组
 * 要求找出一个1~N的排列，满足
 * 1 Bi是该排列第i对数的较大的那个
 * 2 该排列字典序最小
 * 显然对每一个Bi，在其前面放置允许放置的最小值即可
 * 但这个最小值与后续的B有关，因此要回溯或者记录所有的B
 * 但是反过来迭代，就发现Bi前面应该放置允许放置的最大值，
 * 而这个与之前的B无关，仅仅与当前的Bi有关。
 * 因此用set记录还没有放置的数值，对每一个Bi求一个upper_bound即可
 * 同时set还可以用于判断是否有解
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
int const SIZE = 2E5+13;
#endif

using vi = vector<int>;
using si = set<int>;

vi A, B;
si S;
int N;

void proc(){
	S.clear();
	for(int i=1;i<=N+N;++i)S.insert(i);
	for(auto i : B){
		auto it = S.find(i);
		if(it == S.end()) return (void)printf("-1\n");
		S.erase(it);
	}

	for(int i=N-1;i>=0;--i){
        auto it = S.upper_bound(B[i]);
		if(it == S.begin()) return (void)printf("-1\n");
		--it;
		A[i] = *it;
		S.erase(it);
	}

    for(int i=0;i<N;++i){
		printf("%d %d ", A[i], B[i]);
	}
	printf("\n");
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r" ,stdin);
#endif    
    int nofkase = getInt();
	while(nofkase--){
        A.assign(N = getInt() / 2, 0); 
		B.assign(N, 0);
		for(auto & i :B) i = getInt();
		proc();
	}
    return 0;
}
