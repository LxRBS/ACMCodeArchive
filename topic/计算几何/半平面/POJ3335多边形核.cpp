#include <iostream>
#include <algorithm>
using namespace std;

struct point_t{
	int x;
	int y;
	int t;
	point_t(int a=0,int b=0):x(a),y(b),t(1){}
};
int cross(point_t const&O,point_t const&A,point_t const&B){
	int xoa = A.x - O.x;
	int yoa = A.y - O.y;
	int xob = B.x - O.x;
	int yob = B.y - O.y;
	return xoa * yob - xob * yoa;
}

struct hp_t{
	int a;
	int b;
	int c;//ax+by+c>=0，法向量始终是(a,b)
};

int gcd(int a,int b){
	if ( 0 == a ) return b;
	if ( 0 == b ) return a;
	if ( a < 0 ) a = -a;
	if ( b < 0 ) b = -b;

	int r;
	while( a % b ){
		r = a % b;
		a = b;
		b = r;
	}
	return b;
}

inline int area(int x,int y){
	if ( y >= 0 ) return x > 0 ? 0 : 1;
	return x <= 0 ? 2 : 3;
}

//根据法向量的极角排序0~360,极角相同，越靠近法向量的越小
bool operator < (hp_t const&l,hp_t const&r){
    //分象限
	int al = area(l.a,l.b);
	int ar = area(r.a,r.b);
	if ( al != ar ) return al < ar;

	//算叉积
	int chaji = l.a * r.b - l.b * r.a;
	if ( chaji ) return chaji > 0;

	//更靠近法向量的
	return l.c < r.c;
}

//判断半平面是否平行
inline bool isPara(hp_t const&left,hp_t const&right){
    	return area(left.a,left.b) == area(right.a,right.b)
		&& left.a * right.b == right.a * left.b;
}
//从l到r，保证是逆时针方向，a、b是唯一确定的,作了归一化
inline void genHP(point_t const&l,point_t const&r,hp_t&hp){
	hp.a = l.y - r.y;
	hp.b = r.x - l.x;
	hp.c = l.x * r.y - l.y * r.x;

	int g = gcd(hp.a,hp.b);
	g = gcd(g,hp.c);

	hp.a /= g;
	hp.b /= g;
	hp.c /= g;
}
//半平面相交求交点，保证有且只有一个交点
inline void inter(hp_t const&l,hp_t const&r,point_t&p){
	p.x = l.b * r.c - r.b * l.c;
	p.y = r.a * l.c - l.a * r.c;
	p.t = l.a * r.b - r.a * l.b;
}
//判断点是否在半平面内
inline bool isIn(point_t const&p,hp_t const&hp){
	int r = p.x * hp.a + p.y * hp.b + p.t * hp.c;

	if ( p.t > 0 ) return r >= 0;
	return r <= 0;
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

point_t P[105];
hp_t Hp[105];
int main(){
	int kase;
	scanf("%d",&kase);
	while(kase--){
		int n;
		scanf("%d",&n);
		for(int i=0;i<n;++i)scanf("%d%d",&P[i].x,&P[i].y);
		P[n] = P[0];
		//确定顺逆
		int itmp = 0;
        for(int i=1;i<n-1;++i) itmp += cross(*P,P[i],P[i+1]);
		//生成半平面
		if ( itmp > 0 )for(int i=0;i<n;++i) genHP(P[i],P[i+1],Hp[i]);
		else           for(int i=n;i;--i)   genHP(P[i],P[i-1],Hp[i-1]);
		//排序
		sort(Hp,Hp+n);
		//完全平行的半平面只取一个
		hp_t* p = unique(Hp,Hp+n,isPara);
		//待处理的半平面个数 
		n = p - Hp;
		//S&I
		printf(sandi(Hp,n)?"YES\n":"NO\n");
	}
	return 0;
}
