/**
 * 首先将N格分成两半记作A和B，
 * 深搜A，记录A中的条件对B中的影响，例如A1R->B1R，则当A1为R时，将B1R设置为0，初始全为1
 * 对A中的每一种染色方案，都能得到一个位向量，最后得到一个位向量的集合，记作{X}
 * 深搜B，对每一个可以搜到的B，记录其位向量，流入B1为R则将B1R设置为1，同样得到一个位向量的集合记作{Y}
 * {x}是约束集合，{Y}是候选集合，假设：x = 011，说明B1R不能用，而一旦y = 1xx，说明不可取，而y = 0xx，说明可以计数
 * 于是所有满足x约束的y符合条件：x&y==y，即y没有用到不让用的位
 * 记作f(x)为{Y}中满足x条件的数的数量，所求为SIGMA{f(x)}
 * 再弄一个数组A(与之前的AB区分)，所有的A[y] = y在Y中?1:0
 * 则 f(x) = SIGMA{A[y]}，求这样的f(x)是一个SOS(sum over subsets)DP问题，
 * 可以在n2^n完成，其中n是x的位长度
 * 考虑到SOSDP的复杂度，将A长度定位15，B长度定为7，则时间复杂度为O(3*3^15+3*3^7+21*2^21)，265ms
 * 如果B长度定为6，则O(3*3^16+3*3^6+18*2^18)，499ms
 * 标程1279ms，不过有可能是输入的问题
*/
#include <bits/stdc++.h>
using namespace std;

char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000-1,stdin),__abc147==__xyz258) ? EOF : *__abc147++)

int getInt(){
	int sgn = 1;
	char ch = __hv007();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = __hv007();
	if ( '-' == ch ) {sgn = 0;ch=__hv007();}

	int ret = (int)(ch-'0');
	while( '0' <= (ch=__hv007()) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return sgn ? ret : -ret;
}

char getChar(){
	char ch = __hv007();
	while(ch != 'R' && ch != 'G' && ch != 'B') ch = __hv007();
	return ch;
}

inline int tr(char ch){
	if('R' == ch) return 0;
	if('G' == ch) return 1;
	if('B' == ch) return 2;
	throw runtime_error("XX");
	return -1;
}

typedef unsigned long long uint;
typedef long long llt;
typedef pair<int, int> pii;
typedef vector<pii> vpii;
typedef map<pii, vpii> _map_t;

_map_t Conditions;

uint const MSK[] = {
	0x7, 0x3F,0x1FF, 0xFFF,
	0x7FFF, 0x3FFFF, 0x1FFFFF
};

int N, M, Limit;

/// 翻转，并且只保留[0~3*Limit)位
inline uint flip(uint status){
    uint ans = ~status;
	ans &= MSK[Limit];
	return ans;
}

/// 第idx为color颜色代表的二进制数
inline uint f(int idx, int color){
    return 1ULL << (idx+idx+idx+color);
}

/// 第idx染成color颜色，对当前forbidden的影响
inline uint f(int idx, int color, uint forbidden){
    uint ans = forbidden;
    auto it = Conditions.find({idx, color});
	if(it == Conditions.end()){
		return ans;
	} 
	for(const auto &p: it->second){
		ans |= f(p.first, p.second);
	}
	return ans;
}

/// 最多保存2^(3*6)
unsigned int X[43046730];
int XCnt = 0;
/// 最多保存3^6个
unsigned int Y[3100];
int YCnt = 0;
int A[1<<24] = {0};

/// 搜索[Limit, N)位中对前面位的影响，反过来搜
/// forbidden是一个3*Limit位的位向量
void dfsX(int depth, uint forbidden){
    if(Limit == depth){ // 到底了，记录当前变量
        X[XCnt++] = flip(forbidden);
		return;
	}
	for(int color=0;color<3;++color){
		uint bit = f(depth, color);
		if(forbidden & bit) continue; // 说明不能用这个颜色
		/// 得到新的forbidden，递归
        uint nf = f(depth, color, forbidden);
		dfsX(depth-1, nf);
	}
	return;
}

/// 搜索[0, Limit)格中符合条件的位向量，结果是一个3*Limit位的位向量
void dfsY(int depth, uint forbidden, uint bit){
    if(-1 == depth){
        /// bit 只保留[0, 3*Limit)位
		bit = bit & MSK[Limit];
		++A[Y[YCnt++] = bit];
		return;
	}
	for(int color=0;color<3;++color){
        uint c = f(depth, color);
		if(forbidden & c) continue;
		/// 可以用
		uint nf = f(depth, color, forbidden);
		uint nb = bit | c;
		dfsY(depth-1, nf, nb);
	}
	return;
}

llt D[1<<24] = {0};
llt proc(){
	if(0 == M){
		llt ans = 1;
		for(int i=0;i<N;++i) ans *= 3;
		return ans;
	}
    int left = min(7, N/3);
	Limit = left - 1;
	dfsX(N-1, 0);
	dfsY(Limit, 0, 0);
	int n = (Limit+1) * 3;
	for(int i=0;i<(1<<n);++i){
		D[i] = A[i];
	}
	for(int i=0;i<n;++i){
		for(int mask=0;mask<(1<<n);++mask){
			if(mask & (1<<i)){
				D[mask] += D[mask ^ (1<<i)];
			}
		}
	}
	llt ans = 0LL;
	for(int i=0;i<XCnt;++i){
		ans += D[X[i]];
	}
	return ans;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    N = getInt(); M = getInt();
	for(int a,c1,b,c2,i=0;i<M;++i){
        a = getInt() - 1; c1 = tr(getChar());
		b = getInt() - 1; c2 = tr(getChar());
		// Conditions[{a, c1}].emplace_back(b, c2);
		Conditions[{b, c2}].emplace_back(a, c1);
	}
	cout<<proc()<<endl;
    return 0;
}
