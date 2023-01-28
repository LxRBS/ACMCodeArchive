namespace ZIFUCHUAN{

/// Duval算法实现Lyndon分解
/// 每个字符串都可以唯一分解成若干个Lyndon字符串
/// 返回Lyndon串的数量，ans保存右端点的位置，从0开始编号
template<typename IT>
int Duaval(IT begin, int n, vector<int> & ans){
	ans.clear();
	auto end = begin + n;
	for(auto i=begin;i<end;){ 
        auto j = i;
		auto k = i + 1;
		while(k < end && *j <= *k){
			if(*j < *k) j = i;
			else ++j;
			++k;
		}
		while(i <= j){
			ans.emplace_back(i + (k - j - 1) - begin);
			i += k - j;
		}
	}
	return ans.size();
}

}