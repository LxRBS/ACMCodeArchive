/**
 * 给定一个N位P进制数，然后依次让其加1，问最少要加多少个1，可以使得0到P-1的所有数均出现过
 * 例如3进制数2，只需要加1就可实现目标，因为2+1=10，于是012均出现过了
 * N在100，但是P在1E9
 * 注意到无论其他位是几，只要将个位连续加P-1次，肯定能实现目标。
 * 显然可以二分。
 * 由于P非常大，因此不能使用单独的标记数组，需要成段成段的记录
 * 使用set<pair<int, int>>记录还没有出现过的数字的片段
 * 判断增加x次，是否能够覆盖set中所有的片段，如果A0+x没有进位的话，那只需判断一段即可
 * 如果有进位，需要考虑高位的影响，但是高位本质上只有一种影响，
 * 如果高位不是9，则多出了一个Ak+1的数字。
 * 如果高位是9，则还需往更高位进位，最后要么是某个Ak+1，要么就是1
 * 因此对每个x，最多能形成三个片段来覆盖set，但其中大部分情况是两个片段
 * 只有一种情况是三个片段，且中间的片段只有一个单独的数字。因此可以特判。
 * 大部分功能可以用STL完成。
 */
#include <assert.h>
#include <bits/stdc++.h>
using namespace std;

char *__abc147, *__xyz258, __ma369[100000];
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

#ifndef ONLINE_JUDGE
int const SIZE = 13;
#else
int const SIZE = 2E5+13;
#endif

using pii = pair<int, int>;
using spii = set<pii>;
using vi = vector<int>;
using pit = pair<int, spii::iterator>;

int N, P;
vi A;
spii S;

// 在s中查找x，如果x被s中的片段覆盖，返回{1, it}，it表示覆盖x的片段
// 如果x恰好落在s的空隙处，返回{0, it}，it表示x右边的第一个片段
pit find(const spii & s, int x){
    spii::iterator it = s.upper_bound({x, P});
	if(it == s.begin()){ // 表示x在最左边的空档
		return {0, it};
	}
	--it;
	assert(it->first <= x);
	if(x <= it->second){ // 表示x被it覆盖
		return {1, it};
	}
	return {0, ++it};
}

bool isCover(const spii & s, const pii & p){
	return p.first <= s.begin()->first && (--s.end())->second <= p.second;
}

bool isCover(const spii & s, const pii & a, const pii & b){
	if(b.first <= a.second + 1){
		return isCover(s, {a.first, b.second});
	}
	if(isCover(s, a) || isCover(s, b)) return true;
	
	if(s.begin()->first < a.first) return false;
	if(b.second < (--s.end())->second) return false;

	auto pa = find(s, a.second);
    auto pb = find(s, b.first);
	if(0 == pa.first){ // a落在空隙
		if(0 == pb.first){ // b也落在空隙，需要落在同一处
			return pa.second == pb.second;
		}
		// b不在空隙，则b需要落在a的右边，且是开头
		assert(pb.second != s.end());
		return pa.second == pb.second && b.first == pb.second->first;
	}
	// a落在某个片段, a必须落在最后一个点
	assert(pa.second != s.end());
	if(a.second != pa.second->second) return false;
	// b落在空隙，或者下一段
	auto it = pa.second;
	++it;
	if(it != pb.second) return false;
	if(pb.first){
		assert(pb.second != s.end());
		return pb.second->first == b.first;
	} 
	return true;
}

bool check(int x){
	int tmp = A[0] + x;
	if(tmp < P){
		return isCover(S, {A[0], tmp});
	}

	int k = 1;
	int carry = 1;
	while(k < N && A[k] == P - 1) ++k;

	int m = k == N ? 1 : A[k] + 1;
	int left = tmp % P;

	if(m <= left || A[0] <= m){
		return isCover(S, {0, left}, {A[0], P - 1});
	}

	if(left + 1 == m){
		return isCover(S, {0, m}, {A[0], P - 1});
	}

	if(m + 1 == A[0]){
		return isCover(S, {0, left}, {m, P - 1});
	}

	auto p = find(S, m);
	if(0 == p.first){ // 说明m不在S中
        return isCover(S, {0, left}, {A[0], P - 1});
	}

	auto it = S.find({m, m});
	if(it == S.end()) return false;

	S.erase(it);
	bool ans = true;
	if(!S.empty()) ans = isCover(S, {0, left}, {A[0], P - 1});
	S.insert({m, m});
	return ans;
}

int proc(){
	S.clear(); S.insert({0, P-1});
    for(auto i : A){
        auto p = find(S, i);
		if(0 == p.first) continue;
		auto it = p.second;
		// 裂开
		if(it->first != i) S.insert({it->first, i-1});
		if(it->second != i) S.insert({i+1, it->second});
		// 插入操作不影响set的迭代器
		S.erase(it);
	}	
	if(S.empty()) return 0;
	int left = 0, right = P, mid;
	do{
		mid = (left + right) >> 1;
		if(check(mid)) right = mid - 1;
		else left = mid + 1;
	}while(left <= right);
	return left;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r" ,stdin);
#endif    
    int nofkase = getInt();
	while(nofkase--){
        A.assign(N = getInt(), 0); P = getInt();
		for(int i=N-1;i>=0;--i) A[i] = getInt();
		printf("%d\n", proc());
	}
    return 0;
}
