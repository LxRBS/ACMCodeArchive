

namespace ZIFUCHUAN{

struct SuffixArray{

using vi = vector<int>;

// 从i位置开始的后缀记作后缀i,i从0开始
const vi & r;
const int mm;

vi sa;    // 排名第i为的后缀是sa[i]，排名从0开始，因此sa[0]总是n-1
vi rank;  // 后缀i的排名是rank[i]，排名从0开始，因此rank[n-1]总是0
vi height; // height[i]表示排名第i-1和第i的后缀的公共前缀的长度，height[0]和heigth[1]总是0

/// source是源数组，最好令结尾是最小的元素，其余则大于0
/// m为r中不同取值的数量
SuffixArray(const vi & source, int m):r(source), mm(m){
    da(); 
	calHeight();
}

void da(){ // 倍增
    int n = r.size();
	int m = mm;
    sa.assign(n, 0);

	assert(0 == r[n-1]);
	for(int i=0;i<n-1;++i) assert(0 < r[i] && r[i] < m);

    _ws.assign(max(n, m), 0); // 桶的数量是多少？
	_wv.assign(n, 0);
	_wa.assign(n, 0);
	_wb.assign(n, 0);

	// auto * x = _wa.data();
	// auto * y = _wb.data();
	auto x = _wa.begin();
	auto y = _wb.begin();

	int i,j,p;
    // for(i=0;i<m;i++) _ws[i] = 0;
    for(i=0;i<n;i++) _ws[x[i] = r[i]]++;
    for(i=1;i<m;i++) _ws[i] += _ws[i-1];
    for(i=n-1;i>=0;i--) sa[--_ws[*(x+i)]]=i;
    for(j=1,p=1;p<n;j<<=1,m=p){
        for(p=0,i=n-j;i<n;i++) *(y+p++)=i;
        for(i=0;i<n;i++) if(sa[i]>=j) *(y+p++)=sa[i]-j;
        for(i=0;i<n;i++) _wv[i]=*(x+*(y+i));
        fill(_ws.begin(), _ws.begin()+m, 0);
        for(i=0;i<n;i++) _ws[_wv[i]]++;
        for(i=1;i<m;i++) _ws[i] += _ws[i-1];
        for(i=n-1;i>=0;i--) sa[--_ws[_wv[i]]] = *(y+i);
		for(swap(x, y),p=1,*(x+sa[0])=0,i=1;i<n;i++){
            *(x+sa[i])=_cmp(y,sa[i-1],sa[i],j)?p-1:p++;
		}
    }
    return;
}

void calHeight(){
	int n = sa.size();
	rank.assign(n, 0);
	height.assign(n, 0);
	int k = 0;
    for(int i=0;i<n;++i) rank[sa[i]] = i;
	for(int i=0,j;i<n-1;height[rank[i++]] = k){
		for(k ? k-- : 0, j=sa[rank[i] - 1]; r[i + k] == r[j + k]; ++k);
	}
	return;
}

int _cmp(vi::iterator x, int a, int b, int l){
	return *(x+a) == *(x+b) &&  a + l < r.size() && b + l < r.size() &&  *(x+a+l) == *(x+b+l);
}

vi _wa, _wb;
vi _wv, _ws;


};


}

