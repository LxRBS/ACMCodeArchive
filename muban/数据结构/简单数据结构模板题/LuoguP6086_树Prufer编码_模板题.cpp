#include <bits/stdc++.h>
using namespace std;

namespace IO{

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

using llt = long long;

llt getLL(){
	int sgn = 1;
	char ch = __hv007();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = __hv007();
	if ( '-' == ch ) {sgn = 0;ch=__hv007();}
 
	llt ret = (int)(ch-'0');
	while( '0' <= (ch=__hv007()) && ch <= '9' ) ret = ret * 10LL + (llt)(ch-'0');
	return sgn ? ret : -ret;    
}

char getChar(function<bool(char)> ok){
    char ch = __hv007();
    while(!ok(ch)) ch = __hv007();
    return ch;
}

}

namespace DS{

using vi = vector<int>;
using vvi = vector<vi>;

/// 给定一个以N为根!!!的树，转成prufer序列，树通过father数组的形式给定，
/// 同时给定儿子的数量的数组，从1开始编号
/// 度数数组会被清零
void PruferFromTree(const vi & father, vi & deg, vi & prufer){
	prufer.clear();
    auto n = father.size() - 1;
	if(n <= 2) return;
	prufer.reserve(n - 1);
	for(int t,i=1,j=1;i<=n-2;++i,++j){
		while(deg[j]) ++j;
		prufer.emplace_back(t = father[j]);
		while(i<=n-2 && !--deg[t] && t < j){
			prufer.emplace_back(t = father[t]);
			++i;
		}
	}
	/// prufer的最后一个元素会多一个n，删之
	prufer.pop_back();
	assert(n - 2 == prufer.size());
    return;
}

/// 给定Prufer序列，还原树。
/// 同时需要给出prufer序列中元素的cnt数组
/// 节点从1开始编号，但是Pru本身从0开始，确保prufer以n结尾
/// 树以father数组的形式给出,i的父亲是father[i]，n是根节点
void PruferToTree(const vi & prufer, vi & cnt, vi & father){
    auto n = prufer.size() + 1;
	assert(prufer.back() == n);
	father.assign(n + 1, 0);
	father[n - 1] = n;
	/// prufer从0开始编号
	for(int i=0,j=1;i+1<n;++i,++j){
		while(cnt[j]) ++j;
		father[j] = prufer[i];
		while(i + 1 < n && ! --cnt[prufer[i]] && prufer[i] < j) father[prufer[i]] = prufer[i + 1], ++i;
	}
	return;
}

}

int N, M;
vector<int> Father;
vector<int> Deg;
vector<int> Pru;

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    // ios::sync_with_stdio(0); 
    // cin.tie(0); cout.tie(0);	
    using namespace IO;
    N = getInt();
	M = getInt();
	auto ans = 0LL;
	if(1 == M){
        Father.assign(N + 1, 0);
		Deg.assign(N + 1, 0);
		for(int i=1;i<N;++i) ++Deg[Father[i] = getInt()];
		DS::PruferFromTree(Father, Deg, Pru);
		auto k = 0LL;	
		for(int i : Pru) ans ^= ++k * i;
	}else{
        Pru.assign(N - 2, 0);
		Deg.assign(N + 1, 0);
		for(int & i : Pru) ++Deg[i = getInt()];Pru.emplace_back(N);
		DS::PruferToTree(Pru, Deg, Father);
		for(long long i=1;i<=N;++i) ans ^= i * Father[i];
	}
	printf("%lld\n", ans);
	return 0;
}