
namespace DAISHU{

using llt = long long;
llt const MOD = 1000000007LL;

llt qpow(llt a, llt n){
	llt ret = 1LL;
	a %= MOD;
	while(n){
		if(n & 1) (ret *= a) %= MOD;
		(a *= a) %= MOD;
		n >>= 1;
	}
	return ret;
}

inline llt inv(llt a){return qpow(a, MOD-2LL);}

/// 矩阵求逆, src的元素保证在[0, MOD)之间
/// 函数结束, ret为结果, src会变为单位阵 
/// 使用vector需要做一些常数时间加速，否则会T 
int invAss(vector<vector<llt>> & a){
	auto n = a.size();
	vector<vector<llt>> b(n, vector<llt>(n, 0));
	for(int i=0;i<n;++i) b[i][i] = 1;

    for(int row=0;row<n;++row){
        //整型不需要找列主元，只需找非零元即可
        int maxr = row;
        while(maxr < n && 0 == a[maxr][row]) ++maxr;
        //无解
        if(n == maxr) return 0;
        //交换
        if(row != maxr) a[row].swap(a[maxr]), b[row].swap(b[maxr]);
        
        //求逆元
        auto tmp = inv(a[row][row]);
        //更新当前行
		auto * arow = a[row].data();
		auto * brow = b[row].data();
        for(int j=0;j<n;++j){
			(*(arow + j) *= tmp) %= MOD;
			(*(brow + j) *= tmp) %= MOD;
        }
        //更新其余行
        for(int i=0;i<n;++i)if(i!=row){
            // auto & ai = a[i];
			// auto & bi = b[i];
			/// 换成指针访问，比直接方括号要快，
			/// 方括号比迭代器要快
			auto * ai = a[i].data();
			auto * bi = b[i].data();
            auto tt = MOD - ai[row];
			for(int j=0;j<n;++j){
				(*(ai + j) += *(arow + j) * tt % MOD) %= MOD;
				(*(bi + j) += *(brow + j) * tt % MOD) %= MOD;
            }
        }
    }
	a.swap(b);
    return 1;
}


}
