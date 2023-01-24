#include <bits/stdc++.h>
using namespace std;

namespace DS{

template<typename IT = vector<int>::const_iterator>
struct SparseTable{

using T = pair<int, int>;
using vt = vector<T>; 
using vvt = vector<vt>;

SparseTable() = delete;

IT head;
vvt data;

/// 从s开始的n个数，作为原始数组，建立ST表，索引从0开始
/// 整个ST期间，原始数组的内容不能改变
SparseTable(IT begin, int n):head(begin){
    data.assign(n, vt());

    for(int i=0;i<n;++i) {
		data[i].reserve(21); // 100w用21即可
		data[i].emplace_back(i, i);
	}

	for(int j=1,t;(t=1<<j)<=n;++j){
        for(int i=0;i+t<=n;++i){
			const auto & prv = data[i][j-1];
			const auto & nxt = data[i+(t>>1)][j-1];

			auto first = *(begin + prv.first) <= *(begin + nxt.first) ? prv.first : nxt.first;
			auto second = *(begin + nxt.second) <= *(begin + prv.second) ? prv.second : nxt.second;

			data[i].emplace_back(first, second);
		} 
	}

	return;
}

/// 查询[s, e]区间的极小极大值所在的下标，即距离构造函数begin的偏移量
/// 索引从0开始
T query(int s, int e)const{
    int k = static_cast<int>(log2((double)(e - s + 1)));
	const auto & p1 = data[s][k];
	const auto & p2 = data[e-(1<<k)+1][k];
    return {
        *(head + p1.first) <= *(head + p2.first) ? p1.first : p2.first,
		*(head + p2.second) <= *(head + p1.second) ? p1.second : p2.second 
	};
}


};


};

char *__abc147, *__xyz258, __ma369[1000000];
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
 
int N, M;
vector<int> A;

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    // ios::sync_with_stdio(0); 
    // cin.tie(0); cout.tie(0);

    A.assign(N = getInt(), 0); 
	M = getInt();
	for(int & i : A) i = getInt();

	DS::SparseTable<> st(A.begin(), N);

    for(int a,b,i=0;i<M;++i){
		a = getInt() - 1;
		b = getInt() - 1;
		auto p = st.query(a, b);
		printf("%d\n", A[p.second]);
	}

    return 0;
}