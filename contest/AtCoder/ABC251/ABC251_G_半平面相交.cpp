/**
 * 给一个N边形，N在55.
 * 对其做M次平移（每次都从原始位置），M在2E5
 * 由此形成了M个多边形，因此有一个交集
 * 再给定Q个点，Q在2E5，对每个点问是否在交集内
 * 坐标绝对值在1E8
 * 很明显是半平面相交并判断点是否在交集内
 * 首先不能那N*M个半平面求交集，肯定会T
 * 注意到一共有N组平行的半平面，每一组内部都是平行的
 * 只需取最靠近法向量的即可，因此最后参与相交的半平面实际上只有N个
 * 由于N很小，也不必再求半平面相交，直接验证即可
 * 其次，由于坐标很大，longlong不行，要用double或者int128
 * 因为计算半平面乘了一次，判断点在半平面内又乘了一次，因此最大可到1E24
 * 如果是真正求出了半平面相交，double可能也不够，需要long double
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
int const SIZE = 13;
#else
int const SIZE = 2E5+5;
#endif
 
using llt = __int128_t;
using Real = long double;
using vi = vector<int>; 

struct point_t{
    llt x,y;
    point_t(llt xx=0,llt yy=0):x(xx),y(yy){}
};

struct hp_t{
	llt a, b, c;
};

bool operator < (const hp_t&l, const hp_t&r){
	//法向量分别位于x轴上下，可以直接得到结果
	int ly = l.b >= 0 ? 1 : -1;
	int ry = r.b >= 0 ? 1 : -1;
	if(ly != ry) return ly < ry;

	//如果都位于x轴上，且一个朝东一个朝西
	if(0 == l.b && 0 == r.b && l.a * r.a < 0) return l.a < r.a;

	//计算叉积，如果叉积不为零
	llt chaji = l.a * r.b - l.b * r.a;
	if(chaji) return chaji > 0;

	//能到此处说明法向量平行
	if(l.a > 0){
		//若hp1比hp2更靠近法向量，则必有a1x+b1y+c1=0而a2x+b2y+c2>0
        return l.c * r.a < l.a * r.c;
	}
	if(l.a < 0){
		return l.c * r.a > l.a * r.c;
	}

	//a如果为0，b必然不为0
	if(l.b > 0){
		return l.c * r.b < l.b * r.c;
	}
	return l.c * r.b > l.b *r.c;
}

//从l到r，保证是逆时针方向，a、b是唯一确定的
inline void genHP(point_t const&l,point_t const&r,hp_t&hp){
	hp.a = l.y - r.y;
	hp.b = r.x - l.x;
	hp.c = l.x * r.y - l.y * r.x;
}

//判断点是否在半平面内
inline bool isIn(point_t const&p,hp_t const&hp){
	llt v = hp.a * p.x + hp.b * p.y + hp.c;
	return v >= 0;
}

int N, M;
point_t P[55];
hp_t Hp[55];
hp_t Th[SIZE];
point_t Tp[SIZE];


bool isIn(const point_t &p){
	for(int i=0;i<N;++i){
		if(isIn(p, Hp[i])) continue;
		return false;
	}
	return true;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    N = getInt();
	for(int i=0;i<N;++i){
		P[i].x = getInt(); P[i].y = getInt();
	}
	P[N] = P[0];

	M = getInt();
	for(int i=0;i<M;++i){
		Tp[i].x = getInt();
		Tp[i].y = getInt();
	}

	for(int i=0;i<N;++i){
		for(int j=0;j<M;++j){
			genHP(point_t(P[i].x+Tp[j].x, P[i].y+Tp[j].y), point_t(P[i+1].x+Tp[j].x, P[i+1].y+Tp[j].y), Th[j]);
			if(j) Hp[i] = min(Hp[i], Th[j]);
            else Hp[i] = Th[0];
		}
	}

	int q = getInt();
	for(int x,y,qi=1;qi<=q;++qi){
        x = getInt(); y = getInt();
		puts(isIn(point_t(x, y))?"Yes":"No");
	}
    return 0;
}
