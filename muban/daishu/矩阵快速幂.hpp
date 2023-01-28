

namespace DAISHU{


using llt = long long;
using vll = vector<llt>;
using vvll = vector<vll>;

llt const MOD = 1000000007LL;

/// a *= b，ab表示矩阵
void mulAss(vvll & a, const vvll & b){
    assert(a.size() == b.size());

	auto n = a.size();
	vvll r(n, vll(n, 0));
	//// 常数优化
	for(int i=0;i<n;++i){
		auto * ri = r[i].data();
		for(int k=0;k<n;++k){
            const auto aik = a[i][k];
		    const auto * bk = b[k].data();
		    for(int j=0;j<n;++j){
				(*(ri + j) += *(bk + j) * aik) %= MOD;
		    } 
		}
	}
	r.swap(a);
	return;
}

/// a = (a ^ n) a表示矩阵
void powAss(vvll & a, llt n){
    auto sz = a.size();

	vvll ret(sz, vll(sz, 0));
	for(int i=0;i<sz;++i) ret[i][i] = 1;

	while(n){
		if(n & 1) mulAss(ret, a);
		mulAss(a, a);
		n >>= 1;
	}
	ret.swap(a);
	return;
}


}

