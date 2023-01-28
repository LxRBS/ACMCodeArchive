

namespace ZIFUCHUAN{

/// 返回具体begin的位置，begin传指针
template<typename IT>
int minRepresentation(IT begin, int n){
    int i = 0, j = 1, k = 0;
    while(i < n && j < n && k < n){
        while(k < n && *(begin + (i + k) % n) == *(begin + (j + k) % n)) ++k;
		if(k == n) break;
		
		if(*(begin + (i + k) % n) < *(begin + (j + k) % n)) j += k + 1;
		else i += k + 1;
		if(i == j) ++i;
		k = 0;
	}
    return min(i, j);
}

}

