#include <iostream>
#include <algorithm>
using namespace std;

typedef long long int ll_t;

struct point_t{
	ll_t x;
	ll_t y;
	ll_t t;
	point_t(ll_t a=0,ll_t b=0):x(a),y(b),t(1LL){}
};

struct hp_t{
	ll_t a;
	ll_t b;
	ll_t c;//ax+by+c>=0，法向量始终是(a,b)
};
inline int area(ll_t x,ll_t y){
	if ( y >= 0 ) return x > 0 ? 0 : 1;
	return x <= 0 ? 2 : 3;
}
//根据法向量的极角排序0~360，极角相同，越靠近法向量的越小
bool operator < (hp_t const&l,hp_t const&r){
	//分象限
	int al = area(l.a,l.b);
	int ar = area(r.a,r.b);
	if ( al != ar ) return al < ar;

	//算叉积
	ll_t chaji = l.a * r.b - l.b * r.a;
	if ( chaji ) return chaji > 0;

	//更靠近法向量的
	//法向量完全平行，当a为正时
	if ( l.a > 0 ){
		//若hp1比hp2更靠近法向量，则必有a1x+b1y+c1=0而a2x+b2y+c2>0
		return l.c * r.a < l.a * r.c;
	}

	if ( l.a < 0 )return l.c * r.a > l.a * r.c;

	//a如果为0，b必然不为0
	if ( l.b > 0 ) return l.c * r.b < l.b * r.c;
	return l.c * r.b > l.b * r.c;
}
//判断半平面是否平行
bool isPara(hp_t const&left,hp_t const&right){
	return area(left.a,left.b) == area(right.a,right.b)
		&& left.a * right.b == right.a * left.b;
}
ll_t gcd(ll_t a,ll_t b){
	if ( 0 == a ) return b;
	if ( 0 == b ) return a;
	if ( a < 0 ) a = -a;
	if ( b < 0 ) b = -b;

	ll_t r;
	while( a % b ){
		r = a % b;
		a = b;
		b = r;
	}
	return b;
}
//从l到r，保证是逆时针方向，a、b是唯一确定的
inline void genHP(point_t const&l,point_t const&r,hp_t&hp){
    hp.a = l.y - r.y;
	hp.b = r.x - l.x;
    hp.c = l.x * r.y - l.y * r.x;

// 	int g = gcd(hp.a,hp.b);
// 	g = gcd(g,hp.c);
// 
// 	hp.a /= g;
// 	hp.b /= g;
// 	hp.c /= g;
}
//半平面相交求交点，保证有且只有一个交点
inline void inter(hp_t const&l,hp_t const&r,point_t&p){
	p.x = l.b * r.c - r.b * l.c;
	p.y = r.a * l.c - l.a * r.c;
	p.t = l.a * r.b - r.a * l.b;
}
//判断点是否在半平面内
inline bool isIn(point_t const&p,hp_t const&hp){
	ll_t r = p.x * hp.a + p.y * hp.b + p.t * hp.c;
	return p.t > 0 ? r >= 0 : r <= 0;
}
//排序增量法，会改变hp里面的内容
bool sandi(hp_t hp[],int n){
    int bot = 0;
	int top = 1;
	for(int i=2;i<n;++i){
		//最前端的两个半平面相交
		while( bot < top ){
			point_t p;
			inter(hp[top-1],hp[top],p);
			//p在当前半平面外，出队列
			if ( isIn(p,hp[i]) ) break;
			else                 --top;
		}
		//最底端的两个半平面相交
		while( bot < top ){
			point_t p;
			inter(hp[bot],hp[bot+1],p);
			//p在当前半平面外，出队列
			if ( isIn(p,hp[i]) ) break;
			else                 ++bot;
		}
		//赋值
		hp[++top] = hp[i];
	}
	//后处理
	while( bot < top ){
		point_t p;
		inter(hp[top-1],hp[top],p);
		//p在当前半平面外，出队列
		if ( isIn(p,hp[bot]) ) break;
		else                   --top;
	}
	while( bot < top ){
		point_t p;
		inter(hp[bot],hp[bot+1],p);
		//p在当前半平面外，出队列
		if ( isIn(p,hp[top]) ) break;
		else                   ++bot;
	}
	return top - bot > 1;
}

point_t P[55];
hp_t Hp[55];
int main(){
	int n;
	while( scanf("%d",&n) && n ){
		for(int i=0;i<n;++i)scanf("%lld%lld",&P[i].x,&P[i].y);
		P[n] = P[0];
		//生成半平面
        for(int i=0;i<n;++i) genHP(P[i],P[i+1],Hp[i]);
		//排序
        sort(Hp,Hp+n);
		//完全平行的半平面只取一个
		hp_t* p = unique(Hp,Hp+n,isPara);
		//待处理的半平面个数 
		n = p - Hp;
		//S&I
		printf(sandi(Hp,n)?"1\n":"0\n");
	}
	return 0;
}
