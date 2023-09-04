/**
 * 本质上就是问不可重叠的最长重复子串的长度
 */
#include <bits/stdc++.h>
using namespace std;

#include <bits/extc++.h>
using namespace __gnu_pbds;

using Real = long double;
using llt = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;

#ifndef ONLINE_JUDGE
int const SZ = 101;
#else
int const SZ = 110;
#endif

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

bool check(int x, const SuffixArray & sa){
    int n = sa.sa.size();
    int cur = 0;
    while(1){
        int tmp = cur + 1;
        int m1 = sa.sa[cur], m2 = sa.sa[cur];
        while(tmp < n and sa.height[tmp] >= x){
            m1 = min(m1, sa.sa[tmp]);
            m2 = max(m2, sa.sa[tmp]);
            ++tmp;
            /// 因为是在差分数组上做不重叠的子串，所以这里要多加1
            if(m2 >= m1 + x + 1) return true;
        }
        if((cur = tmp) == n) break;
    }
    return false;
}

int N;
vi A;

int proc(){
    int offset = 100;
    for(int i=0;i+1<N;++i) offset = min(offset, A[i]);
    if(offset <= 0)for(int i=0;i+1<N;++i) A[i] -= offset - 1;
    int m = *max_element(A.begin(), A.end());
    SuffixArray sa(A, m + 1);

    int left = 0, right = N / 2, mid;
    do{
        mid = (left + right) >> 1;
        if(check(mid, sa)) left = mid + 1;
        else right = mid - 1;
    }while(left <= right);
    return right >= 4 ? right + 1 : 0;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N; A.assign(N, 0);
    int pre; cin >> pre;
    for(int a,i=1;i<N;++i){
        cin >> a;
        A[i - 1] = a - pre;
        pre = a;
    }
    cout << proc() << endl;
    return 0;
}