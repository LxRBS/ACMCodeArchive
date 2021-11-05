/**
 * 平面上有横平竖直的若干条街道，街道有交叉点，可以走
 * 街道上有若干点，问有多少点对满足：其沿着街道走的最短距离大于坐标的曼哈顿距离
 * 首先交叉点上的点直接忽略
 * 然后只有一种情况才会满足条件，就是两个点“隔河相望”
 * 假设同一排阶梯中，每一级分别有a1,a2,...,an个点
 * 则对答案的贡献是a1*(a2+...+an) + a2*(a3+...+an) + a3*(a4+...+an) + ...
 * 所以首先用数据结构统计出所有的a，然后对每一排进行计算，包括横竖。
*/
#include <bits/stdc++.h>
using namespace std;

char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)

int getUnsigned(){
	char ch = __hv007();
	while( ch < '0' || ch > '9' ) ch = __hv007();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = __hv007() ) && ch <= '9' ) ret = (ret<<1) + (ret<<3) + (int)(ch-'0');
	return ret;
}

int getInt(){
	int sgn = 1;
	char ch = __hv007();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = __hv007();
	if ( '-' == ch ) {sgn = 0;ch=__hv007();}

	int ret = (int)(ch-'0');
	while( '0' <= (ch=__hv007()) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return sgn ? ret : -ret;
}

typedef long long llt;

llt getULL(){
	char ch = __hv007();
	while( ch < '0' || ch > '9' ) ch = __hv007();

	llt ret = (llt)(ch-'0');
	while( '0' <= ( ch = __hv007() ) && ch <= '9' ) ret = (ret<<1) + (ret<<3) + (llt)(ch-'0');
	return ret;
}

#ifndef ONLINE_JUDGE
int const SIZE =12;
#else 
int const SIZE = 210000;
#endif

#define pb push_back

typedef vector<int> vll;
typedef unordered_map<int, int> map_int_t;
typedef unordered_map<int, map_int_t> map_map_int_t;

struct Point{
    llt x, y;
}P[SIZE+SIZE];

llt N, M, K;
llt X[SIZE], Y[SIZE];

map_map_int_t X2Cnt, Y2Cnt; 
unordered_set<int> Xcoor, Ycoor;

vll Vec, TT;

llt calc(const map_int_t &m){
	llt ans = 0;
	Vec.clear();
	for(const auto &pp: m){
        Vec.pb(pp.second);
	}
    TT.assign(Vec.begin(), Vec.end());
	for(int i=TT.size()-2;i>=0;--i){
		TT[i] += TT[i+1];
	}
	for(int i=0,n=Vec.size()-1;i<n;++i){
	    ans += Vec[i] * TT[i+1];
	}
	return ans;
}

llt proc(){
    llt ans = 0;
    for(const auto &pp: X2Cnt){
		ans += calc(pp.second);
	}
	for(const auto &pp: Y2Cnt){
		ans += calc(pp.second);
	}
	return ans;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int nofkase = getUnsigned();
	while(nofkase--){
		Xcoor.clear();
		Ycoor.clear();
		X2Cnt.clear();
		Y2Cnt.clear();

		N = getUnsigned();
		M = getUnsigned();
		K = getUnsigned();
        
		for(int i=1;i<=N;++i){
			Xcoor.insert(X[i] = getUnsigned());
			X2Cnt.insert({i, map_int_t()});
		}

		for(int i=1;i<=M;++i){
			Ycoor.insert(Y[i] = getUnsigned());
			Y2Cnt.insert({i, map_int_t()});
		}

		int k = 0;
        for(int i=1;i<=K;++i){
			auto xit = Xcoor.find(P[k].x=getUnsigned());
			auto yit = Ycoor.find(P[k].y=getUnsigned());

			if(xit != Xcoor.end() && yit != Ycoor.end()){
				continue;
			}
            
			if(xit != Xcoor.end()){
                int tmp = lower_bound(Y+1, Y+M+1, P[k].y) - Y;
				++Y2Cnt[tmp][*xit];
			}else{
                int tmp = lower_bound(X+1, X+N+1, P[k].x) - X;
				++X2Cnt[tmp][*yit];
			}

			++k;
		}

		printf("%lld\n", proc());
	}
	return 0;
}
