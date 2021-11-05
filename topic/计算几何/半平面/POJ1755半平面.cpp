#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

double const EPS = 1E-17;
double const INF = 1E100;

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
double cross(point64f_t const&O,point64f_t const&A,point64f_t const&B){
	double xoa = A.x - O.x;
	double yoa = A.y - O.y;
	double xob = B.x - O.x;
	double yob = B.y - O.y;
	return xoa * yob - xob * yoa;
}
//随便定个顺序
bool operator < (point64f_t const&l,point64f_t const&r){
	return l.x < r.x || ( isEq(l.x,r.x) && l.y < r.y );
}
bool operator == (point64f_t const&l,point64f_t const&r){
	return isEq(l.x,r.x) && isEq(l.y,r.y);
}
//以相对于确定点的坐标的极角排序
point64f_t Origin;
bool cmp(point64f_t const&l,point64f_t const&r){
	double xl = l.x - Origin.x;
	double yl = l.y - Origin.y;
	double xr = r.x - Origin.x;
	double yr = r.y - Origin.y;
	double chaji = xl * yr - yl * xr;
	return chaji > 0 || ( isZero(chaji) && l.x * l.x + l.y * l.y < r.x * r.x + r.y * r.y );
}
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
//从l到r，保证是逆时针方向，a、b是唯一确定的
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
	//当还剩至少3个半平面，说明>=0肯定有解，但本题要求>0的解
	//求交点
    vector<point64f_t> v(top-bot+1);
	inter(hp[top],hp[bot],v[top-bot]);
	for(int i=bot;i<top;++i) 
		inter(hp[i],hp[i+1],v[i-bot]);
	
	//剔除重复的点
	sort(v.begin(),v.end());
	vector<point64f_t>::iterator it = unique(v.begin(),v.end());
    v.erase(it,v.end());
	
	if ( v.size() <= 2 ) return false;
	//还要求剩下的点不能共线，这以下的代码似乎麻烦了点
	int k = 0;
	for(unsigned int i=1;i<v.size();++i){
		if ( v[i].y < v[k].y || ( isEq(v[i].y,v[k].y) && v[i].x < v[k].x ) )
			k = i;
	}
    Origin = v[k];
	v[k] = v[0];
	v[0] = Origin;
	sort(v.begin()+1,v.end(),cmp);
       //求面积
	double area=0.0;
	for(unsigned int i=1;i<v.size()-1;++i) 
		area += cross(v[0],v[i],v[i+1]);
	if ( isZero(area) ) return false;
	return true;
}

point_t P[55];
hp_t Hp[105];
int V[105],U[105],W[105];

int main(){
	int n;
	while( EOF != scanf("%d",&n) ){
		for(int i=0;i<n;++i)scanf("%d%d%d",V+i,U+i,W+i);
		//对每一个参赛者构造一组半平面进行求解
		for(int kase=0;kase<n;++kase){
			bool flag = false;
			int k = 0;
			for(int i=0;i<n;++i){
				if ( i == kase ){
					k = 1;
					continue;
				}
				if ( V[i] >= V[kase] && U[i] >= U[kase] && W[i] >= W[kase] ){
				    flag = true;
					break;
				}
                Hp[i-k].a = (double)(V[kase]-V[i])/(double)V[i]/(double)V[kase];
				Hp[i-k].b = (double)(U[kase]-U[i])/(double)U[i]/(double)U[kase];
				Hp[i-k].c = (double)(W[kase]-W[i])/(double)W[i]/(double)W[kase];
			}

			if ( flag ){
				printf("No\n");
				continue;
			}

			int nn = n - 1;
			//加一个包围盒
			Hp[nn].a = 0.0;
			Hp[nn].b = -1.0;
			Hp[nn].c = INF;
			++nn;
			Hp[nn].a = 0.0;
			Hp[nn].b = 1.0;
			Hp[nn].c = 0.0;
			++nn;
			Hp[nn].a = 1.0;
			Hp[nn].b = 0.0;
			Hp[nn].c = 0.0;
			++nn;
			Hp[nn].a = - 1.0;
			Hp[nn].b = 0.0;
			Hp[nn].c = INF;
			++nn;

			//排序
			sort(Hp,Hp+nn);

			//完全平行的半平面只取一个
			hp_t* p = unique(Hp,Hp+nn,isPara);

			//待处理的半平面个数 
			nn = p - Hp;

			//S&I
			printf(sandi(Hp,nn)?"Yes\n":"No\n");
		}
	}
	return 0;
}
