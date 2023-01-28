
namespace DAISHU{

using llt = long long;

llt MOD = 0;

/// 求行列式a的值，会改变a的内容
llt determinant(vector<vector<llt>> & a){
    llt ret = 1;
    auto n = a.size();

    for(int i=0;i<n;++i){
		auto * ai = a[i].data();
    	for(int j=i+1;j<n;++j){
			auto * aj = a[j].data();
			auto & aji = *(aj + i);
    		while(aji){
    			auto t = *(ai + i) / aji;
    			for(int k=i;k<n;++k){
					/// 复合赋值更加耗时，导致T
    				// (*(ai + k) -= t * *(aj + k) % MOD) %= MOD;
					*(ai + k) = (*(ai + k) - *(aj + k) * t) % MOD;
				}
				for(int k=i;k<n;++k) swap(*(ai + k),*(aj + k));
				ret = -ret;
			}
		}

		if(0 == *(ai + i)) return 0;
		ret = ret * *(ai + i) % MOD;
	}

	// for(int i=0;i<n;++i) (ret *= a[i][i]) %= MOD;
	if(ret < 0) ret += MOD;
	return ret;
}



}
