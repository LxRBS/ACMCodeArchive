#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

double const EPS = 1E-11;
double const INF = 1E9;

#define is0(x) ( - EPS <= (x) && (x) <= EPS )
#define isEq(x,y) is0( (x) - (y) )

struct point_t{
	int x;
	int y;
}P[203];

struct point64f_t{
	double x;
	double y;
};

struct hp_t{
	double a;
	double b;
	double c;//ax+by+c>=0,(a,b)即法向量
}Hp[210];

//根据法向量的极角排序(0~360)，极角相同，越靠近法向量的越小
bool operator < (hp_t const&l,hp_t const&r){
	//法向量分别位于x轴上下，可以直接得到结果
	int ly = l.b >= 0 ? 1 : -1;
	int ry = r.b >= 0 ? 1 : -1;
	if ( ly != ry ) return ly > ry;
	//如果都位于x轴上
	if ( is0(l.b) && is0(r.b) && l.a * r.a < 0 )
		return l.a > r.a;

	double chaji = l.a * r.b - l.b * r.a;

	if ( !is0(chaji) ) return chaji > 0;

	//法向量完全平行，当a为正时
	if ( l.a > EPS ){
		//若hp1比hp2更靠近法向量，则必有a1x+b1y+c1=0而a2x+b2y+c2>0
		return l.c * r.a < l.a * r.c;
	}

	if ( l.a < - EPS )return l.c * r.a > l.a * r.c;

	//a如果为0，b必然不为0
	if ( l.b > EPS ) return l.c * r.b < l.b * r.c;
	return l.c * r.b > l.b * r.c;
}

//判断半平面是否平行
bool isPara(hp_t const&l,hp_t const&r){
	int ly = l.b >= 0 ? 1 : -1;
	int ry = r.b >= 0 ? 1 : -1;
	if ( ly != ry ) return false;
	if ( is0(l.b) && is0(r.b) ) return l.a * r.a > 0;
	return is0( l.a * r.b - r.a * l.b );
}

//从l到r，保证是逆时针方向
inline void genHP(point_t const&l,point_t const&r,hp_t&hp){
    hp.a = (double)( l.y - r.y );
	hp.b = (double)( r.x - l.x );
	hp.c = (double)( l.x * r.y - l.y * r.x );
}

//半平面相交求交点，保证有且只有一个交点
inline void inter(hp_t const&l,hp_t const&r,point64f_t&p){
	double xishu = l.a * r.b - r.a * l.b;
	p.x = ( l.b * r.c - r.b * l.c ) / xishu;
	p.y = ( l.c * r.a - l.a * r.c ) / xishu;
}

//判断点是否在半平面内
inline bool isIn(point64f_t const&p,hp_t const&hp){
	double v = hp.a * p.x + hp.b * p.y + hp.c;
	return v >= - EPS;
}

//排序增量法，会改变hp里面的内容
bool sandi(hp_t hp[],int n){
	int bot = 0;
	int top = 1;
	for(int i=2;i<n;++i){
		//最前端的两个半平面相交
		while( bot < top ){
			point64f_t p;
			inter(hp[top-1],hp[top],p);
			//p在当前半平面外，出队列
			if ( isIn(p,hp[i]) ) break;
			else                 --top;
		}
		//最底端的两个半平面相交
		while( bot < top ){
			point64f_t p;
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
		point64f_t p;
		inter(hp[top-1],hp[top],p);
		//p在当前半平面外，出队列
		if ( isIn(p,hp[bot]) ) break;
		else                   --top;
	}
	while( bot < top ){
		point64f_t p;
		inter(hp[bot],hp[bot+1],p);
		//p在当前半平面外，出队列
		if ( isIn(p,hp[top]) ) break;
		else                   ++bot;
	}
	//剩下3个或更多的半平面才有交集
	return top - bot > 1;
}
//将多边形往内移动radius距离
void moveHP(hp_t hp[],int n,double radius){
	for(int i=0;i<n;++i)
		hp[i].c -= radius * sqrt(hp[i].a*hp[i].a+hp[i].b*hp[i].b);
	//半平面向法向移动，只改变c的值
}
int main(){
	int n;
	while( scanf("%d",&n) && n ){
		int xmin = INT_MAX, xmax = INT_MIN;
		for(int i=0;i<n;++i){
			scanf("%d%d",&P[i].x,&P[i].y);
			if ( P[i].x < xmin ) xmin = P[i].x;
			if ( P[i].x > xmax ) xmax = P[i].x;
		}
		P[n] = P[0];
		//生成半平面
		for(int i=0;i<n;++i)genHP(P[i],P[i+1],Hp[i]);
		//左开右闭二分法
		double left = 0.00001;                        //可能的最小值
		double right = (double)( xmax - xmin ) / 2.0; //可能的最大值
		double mid;
		hp_t hp[210];
		do{			
			copy(Hp,Hp+n,hp);
			//将多边形往内移动mid距离
            mid = ( left + right ) / 2;
			moveHP(hp,n,mid);
			int nn = n;
			//排序
			sort(hp,hp+nn);
			//完全平行的半平面只取一个
			hp_t* p = unique(hp,hp+nn,isPara);
			nn = p - hp;
			if ( sandi(hp,nn) ) left = mid; //+ 0.000001;//这个地方加减1E-5始终过不了，改成1E-6就OK了
			else                right = mid; // - 0.000001;//完全可以不加...
		}while( left + 0.000001 <= right + EPS );
		printf("%lf\n",right);
	}
	return 0;
}
