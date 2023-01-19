/**
 * 与F题目类似。给定一个N*3的地图，每一次只能向下或者向右走，
 * 可以反复的从左上走到右下，要求尽可能多的经过所有能经过的格子
 * 再给定K次操作，每次操作将某一格在障碍与通路之间翻转
 * 对每一次操作，问操作之后的能够通过的格子数量
 * 对于第一列，显然要找到距离1最近的障碍物，前一个空格记作t1，从1到t1是可走的候选，t1以后必然都不能走
 * 对于第三列，显然要找到距离N最近的障碍物，后一个空格记作t3，从t3到N是可走的候选，t3之前必然都不能走
 * 再根据t1和t3的大小分情讨论，比较麻烦的是t1大于t3的情况
 * 无论那种情况，都需要在第二列中找一些东西。
 * 障碍物用1表示，通路用0表示，原始数组显然是01数组，其前缀和数组显然是递增的
 * 因此所有查找都可以使用二分完成。
 * 显然又要支持单点修改操作，因此需要树状数组上的二分。
 */
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
int const SIZE = 130;
#else
int const SIZE = 1.1E6+10;
#endif

using llt = long long;
using vi = vector<int>;
using vvi = vector<vi>;

struct bit_t{

int n;
vi c;

static int lowbit(int x){return x & -x;}

void init(int nn){c.assign((n=nn)+1, 0);}

void modify(int pos, int d){
	for(int i=pos;i<=n;i+=lowbit(i)) c[i] += d;
}

int query(int pos)const{
	int ans = 0;
	for(int i=pos;i;i-=lowbit(i))ans += c[i];
	return ans;
}

int query(int s, int e)const{return query(e) - query(s-1);}

}B[4];

int Row, Col;
int N, K;
vvi A;

/// 从pos位置找左边第一个0，保证pos位置本身是0
int findZeroLeft(int index, int pos){
	assert(0 == A[index][pos]);
	const auto & b = B[index];
    int left = 0, right = pos, mid;
	int level = b.query(pos);
	do{
		mid = (left + right) >> 1;
        if(b.query(mid) != level) left = mid + 1;
		else right = mid - 1; 
	}while(left <= right);
    return left + 1;
}

/// 从pos位置找右边第一个0，保证pos位置本身是0
int findZeroRight(int index, int pos){
    assert(0 == A[index][pos]);
	const auto & b = B[index];
	int left = pos, right = N, mid;
	int level = b.query(pos);
	do{
        mid = (left + right) >> 1;
		if(b.query(mid) != level) right = mid - 1;
		else left = mid + 1;
	}while(left <= right);
	return right;
}

/// 从pos位置找到左边第一个0，保证pos位置本身是1
int findFirstLeftZero(int index, int pos){
    assert(1 == A[index][pos]);
	const auto & b = B[index];
	int left = 1, right = pos, mid;
	int level = b.query(pos);
	do{
		mid = (left + right) >> 1;
        if(pos - mid + 1 == level - b.query(mid - 1)) right = mid - 1;
		else left = mid + 1; 
	}while(left <= right);
	return left - 1;
}

/// 从pos位置找到右边第一个0，保证pos位置本身是1
int findFirstRightZero(int index, int pos){
    assert(1 == A[index][pos]);
	const auto & b = B[index];
	int left = pos, right = N, mid;
	int level = b.query(pos - 1);
	do{
		mid = (left + right) >> 1;
        if(mid + 1 - pos == b.query(mid) - level) left = mid + 1;
		else right = mid - 1;
	}while(left <= right);
	return right + 1;
}

int procEqual(int t){
	if(1 == A[2][t]) return 0;

	auto s = findZeroLeft(2, t);
	auto e = findZeroRight(2, t);
	assert(s <= e);

	return t + (N - t + 1) + (e - s + 1);
}

int procOneBig(int t1, int t3){
    int e = -1;
	if(1 == A[2][t1]) e = findFirstLeftZero(2, t1);
	else e = findZeroRight(2, t1);
	assert(-1 != e);
	if(e < t3) return 0;

	int s = -1;
    if(1 == A[2][t3]) s = findFirstRightZero(2, t3);
	else s = findZeroLeft(2, t3);
	assert(s != -1);
	if(s > t1) return 0;

	return min(e, t1) + (N - max(s, t3) + 1) + (e - s + 1 - B[2].query(s, e));
}

int procOneLess(int t1, int t3){
    if(1 == A[2][t1]) return 0;
	if(1 == A[2][t3]) return 0;

	const auto & b = B[2];
    if(b.query(t1) != b.query(t3)) return 0;
	
	auto s = findZeroLeft(2, t1);
	auto e = findZeroRight(2, t3);
	assert(s < e);
    return t1 + (N - t3 + 1) + (e - s + 1);
}

int proc(){
    auto & a = A[Row][Col];
	if(a) B[Row].modify(Col, -1);
	else B[Row].modify(Col, 1);
	a ^= 1;

	auto t1 = findZeroRight(1, 1);
	auto t3 = findZeroLeft(3, N);

	assert(t1 >= 1 && t3 <= N);

	if(t1 == t3){
        return procEqual(t1);
	}else if(t1 > t3){
        return procOneBig(t1, t3);
	}else if(t1 < t3){
        return procOneLess(t1, t3);
	}
	assert(0);
	return 0;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif 
    int nofkase = getInt();
    while(nofkase--){
		A.assign(4, vi((N = getInt()) + 1, 0));
		K = getInt();
		for(int i=1;i<=3;++i) B[i].init(N);

	    for(int i=0;i<K;++i){
            Col = getInt(); Row = getInt();
            auto tmp = proc();
            if(tmp) tmp -= 1;
			printf("%d\n", tmp);
		}	 
	}
    return 0;
}
