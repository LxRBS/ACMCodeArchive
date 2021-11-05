#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

double const EPS = 1E-9;

#define isZero(x) ( - EPS <= (x) && (x) <= EPS )
#define isEq(x,y) isZero( (x) - (y) )

struct point_t{
	int x;
	int y;
	point_t(int a=0,int b=0):x(a),y(b){}
};
struct point64f_t{
	double x;
	double y;
	point64f_t(double a=0.0,double b=0.0):x(a),y(b){}
};
struct hp_t{
	double a;
	double b;
	double c;//ax+by+c>=0，法向量始终是(a,b)
};
//根据法向量的极角排序(-180,180]，极角相同，越靠近法向量的越小
bool operator < (hp_t const&l,hp_t const&r){
	//法向量分别位于x轴上下，可以直接得到结果
	int ly = l.b >= 0 ? 1 : -1;
	int ry = r.b >= 0 ? 1 : -1;
	if ( ly != ry ) return ly < ry;
	//如果都位于x轴上
	if ( isZero(l.b) && isZero(r.b) && l.a * r.a < 0 )
		return l.a > r.a;

	double chaji = l.a * r.b - l.b * r.a;

	if ( !isZero(chaji) ) return chaji > 0;

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
	if ( isZero(l.b) && isZero(r.b) ) return l.a * r.a > 0;
	return isZero( l.a * r.b - r.a * l.b );
}
//从l到r，保证是顺时针方向，a、b是唯一确定的
inline void genHP(point_t const&l,point_t const&r,hp_t&hp){
	hp.a = - (double)( l.y - r.y );
	hp.b = - (double)( r.x - l.x );
	hp.c = - (double)( l.x * r.y - l.y * r.x );
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
//计算距离方
inline double calDist2(point64f_t const&l,point64f_t const&r){
	double x = l.x - r.x;
	double y = l.y - r.y;
	return x * x + y * y;
}
//排序增量法，会改变hp里面的内容
bool sandi(hp_t hp[],int n,point64f_t ans[]){
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
	//题意保证有解，求交点
	vector<point64f_t> vp;
	hp[top+1] = hp[bot];
	for(int i=bot;i<=top;++i){
		point64f_t p;
		inter(hp[i],hp[i+1],p);
		vp.push_back(p);
	}
	//求交点中相距最远的2点
	double dst = 0.0;
	int k1 = 0,k2 = 0;
	for(unsigned int i=0;i<vp.size()-1;++i)for(unsigned int j=i+1;j<vp.size();++j){
		double dtmp = calDist2(vp[i],vp[j]);
		if ( dtmp > dst ) dst = dtmp, k1 = i, k2 = j;
	}
    ans[0] = vp[k1];
	ans[1] = vp[k2];
	return true;
}

//将多边形往内移动radius距离
void moveHP(hp_t hp[],int n,double radius){
	for(int i=0;i<n;++i)
		hp[i].c -= radius * sqrt(hp[i].a*hp[i].a+hp[i].b*hp[i].b);
	//半平面向法向移动，只改变c的值
}

point_t P[105];
hp_t Hp[105];


int main(){
	int n,r;
	while( EOF != scanf("%d%d",&n,&r) ){
		for(int i=0;i<n;++i)scanf("%d%d",&P[i].x,&P[i].y);
		P[n] = P[0];
		//生成半平面
		for(int i=0;i<n;++i) genHP(P[i],P[i+1],Hp[i]);
		//排序
		sort(Hp,Hp+n);
		//完全平行的半平面只取一个
		hp_t* p = unique(Hp,Hp+n,isPara);
		//待处理的半平面个数 
		n = p - Hp;
		moveHP(Hp,n,(double)r);
		//S&I
		point64f_t ansp[2];
		sandi(Hp,n,ansp);
		printf("%.4lf %.4lf %.4lf %.4lf\n",ansp->x,ansp->y,ansp[1].x,ansp[1].y);
	}
	return 0;
}
