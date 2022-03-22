/**
 * ���Ƚ�N��ֳ��������A��B��
 * ����A����¼A�е�������B�е�Ӱ�죬����A1R->B1R����A1ΪRʱ����B1R����Ϊ0����ʼȫΪ1
 * ��A�е�ÿһ��Ⱦɫ���������ܵõ�һ��λ���������õ�һ��λ�����ļ��ϣ�����{X}
 * ����B����ÿһ�������ѵ���B����¼��λ����������B1ΪR��B1R����Ϊ1��ͬ���õ�һ��λ�����ļ��ϼ���{Y}
 * {x}��Լ�����ϣ�{Y}�Ǻ�ѡ���ϣ����裺x = 011��˵��B1R�����ã���һ��y = 1xx��˵������ȡ����y = 0xx��˵�����Լ���
 * ������������xԼ����y����������x&y==y����yû���õ������õ�λ
 * ����f(x)Ϊ{Y}������x��������������������ΪSIGMA{f(x)}
 * ��Ūһ������A(��֮ǰ��AB����)�����е�A[y] = y��Y��?1:0
 * �� f(x) = SIGMA{A[y]}����������f(x)��һ��SOS(sum over subsets)DP���⣬
 * ������n2^n��ɣ�����n��x��λ����
 * ���ǵ�SOSDP�ĸ��Ӷȣ���A���ȶ�λ15��B���ȶ�Ϊ7����ʱ�临�Ӷ�ΪO(3*3^15+3*3^7+21*2^21)��265ms
 * ���B���ȶ�Ϊ6����O(3*3^16+3*3^6+18*2^18)��499ms
 * ���1279ms�������п��������������
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

/// ��ת������ֻ����[0~3*Limit)λ
inline uint flip(uint status){
    uint ans = ~status;
	ans &= MSK[Limit];
	return ans;
}

/// ��idxΪcolor��ɫ����Ķ�������
inline uint f(int idx, int color){
    return 1ULL << (idx+idx+idx+color);
}

/// ��idxȾ��color��ɫ���Ե�ǰforbidden��Ӱ��
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

/// ��ౣ��2^(3*6)
unsigned int X[43046730];
int XCnt = 0;
/// ��ౣ��3^6��
unsigned int Y[3100];
int YCnt = 0;
int A[1<<24] = {0};

/// ����[Limit, N)λ�ж�ǰ��λ��Ӱ�죬��������
/// forbidden��һ��3*Limitλ��λ����
void dfsX(int depth, uint forbidden){
    if(Limit == depth){ // �����ˣ���¼��ǰ����
        X[XCnt++] = flip(forbidden);
		return;
	}
	for(int color=0;color<3;++color){
		uint bit = f(depth, color);
		if(forbidden & bit) continue; // ˵�������������ɫ
		/// �õ��µ�forbidden���ݹ�
        uint nf = f(depth, color, forbidden);
		dfsX(depth-1, nf);
	}
	return;
}

/// ����[0, Limit)���з���������λ�����������һ��3*Limitλ��λ����
void dfsY(int depth, uint forbidden, uint bit){
    if(-1 == depth){
        /// bit ֻ����[0, 3*Limit)λ
		bit = bit & MSK[Limit];
		++A[Y[YCnt++] = bit];
		return;
	}
	for(int color=0;color<3;++color){
        uint c = f(depth, color);
		if(forbidden & c) continue;
		/// ������
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
