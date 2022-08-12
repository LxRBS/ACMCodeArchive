#include <iostream>
#include <algorithm>
#include <deque>
using namespace std;

long double const EPS = 1E-8;

#define isZero(x) ( - EPS < (x) && (x) < EPS )

inline long double cross(double a1,double b1,double a2,double b2){
	return a1 * b2 - a2 * b1;
}

struct point64f_t{
	long double x;
	long double y;
	point64f_t(long double a=0.0,long double b=0.0):x(a),y(b){}
	bool operator == (point64f_t const&r){
		return isZero(x-r.x) && isZero(y-r.y);
	}
};

long double cross(point64f_t const&O,point64f_t const&A,point64f_t const&B){
	long double xoa = A.x - O.x;
	long double yoa = A.y - O.y;
	long double xob = B.x - O.x;
	long double yob = B.y - O.y;
	return xoa * yob - xob * yoa;
}

struct hp_t{
	long double a,b,c; //ax+by+c>0，法向量就是(a, b)
	hp_t(long double aa=0.0,long double bb=0.0,long double cc=0.0):
	a(aa),b(bb),c(cc){}
}Hp[20000+4+3];

//a/b为法向量，不可能同时为0，极角从0~360
inline int calLoc(long double a,long double b){
	if ( isZero(a) ) return b > 0 ? 2 : 6;
	if ( isZero(b) ) return a > 0 ? 0 : 4;
	if ( a > 0 ) return b > 0 ? 1 : 7;
	return b > 0 ? 3 : 5;
}

// 半平面比大小，利用法向量的极角
bool operator < (hp_t const&l,hp_t const&r){
    int locl = calLoc(l.a,l.b);
	int locr = calLoc(r.a,r.b);
	if ( locl != locr ) return locl < locr;

	long double chaji = cross(l.a,l.b,r.a,r.b);
    if ( !isZero(chaji) ) return chaji > 0;

	//叉积等于0，半平面平行。越靠近法向量方向的越小
	if ( l.a > EPS ){
		//即a为正的情况下
		//若hp1比hp2更靠近法向量，则必有a1x+b1y+c1=0而a2x+b2y+c2>0
		return l.c * r.a < l.a * r.c;
	}

	if ( l.a < -EPS ) return l.a * r.c < l.c * r.a;

	//剩下则为a取值为0的情况，此时考虑b即可
	if ( l.b > EPS ) return l.c * r.b < l.b * r.c;

	//若b为负，a、b不可能同时为0
	return l.b * r.c < l.c * r.b;
}
//判断点是否在hp上
inline bool isIn(point64f_t const&p,hp_t const&hp){
	double v = hp.a * p.x + hp.b * p.y + hp.c;
	return isZero(v) || v > 0;
}
//判断l与r是否平行，即法向量是否方向一致
inline bool isParallel(hp_t const&l,hp_t const&r){
	return calLoc(l.a,l.b) == calLoc(r.a,r.b) 
		&& isZero( l.a * r.b - l.b * r.a );
}
//半平面相交求直线的交点，保证l与r有交点
inline void inter(hp_t const&l,hp_t const&r,point64f_t&p){
	double xishu = l.a * r.b - r.a * l.b;
	p.x = ( l.b * r.c - r.b * l.c ) / xishu;
	p.y = ( l.c * r.a - l.a * r.c ) / xishu;
}

//排序增量法
void sandi(hp_t hp[],int n,deque<point64f_t>&ans){
	//预处理，将平行的半平面只保留最小的也就是最靠近法向量的
	Hp[n] = Hp[0];//方便处理，第一个与最后一个绝对不会平行
	int k = 0;
	for(int i=1;i<n;){
		while( isParallel(Hp[k],Hp[i]) ) ++i;
		if ( i == n ) break;
		Hp[k+1] = Hp[i];
		k = k + 1;
		++i;
	}
	//n是预处理以后的半平面个数
	n = k + 1;

	int bot = 0, top = 1;
	for(int i=2;i<n;++i){
		//最前端两个半平面相交
		while( bot < top ){
			point64f_t p;
			inter(hp[top-1],hp[top],p);
			//在半平面内，入队列
			if ( isIn(p,hp[i]) ){
				break;

			//在半平面外，出队列
			}else{
				--top;
			}
		}

		//最后端两个半平面相交
		while( bot < top ){
			point64f_t p;
			inter(hp[bot],hp[bot+1],p);

			if ( isIn(p,hp[i]) ){
				break;
			}else{
				++bot;
			}
		}

	    //赋值
        hp[++top] = hp[i];
	}

	//如果最后的半平面少于三个肯定不对，因外加了包围盒以后一定会围成一个封闭的区域
	if ( top - bot <= 1 ){
		ans.clear();
		return;
	}

	//后处理
	while( bot < top ){
		point64f_t p;
		inter(hp[top-1],hp[top],p);
		
		//在最后端的半平面外，则出队列
		if ( isIn(p,Hp[bot]) ){
			break;
		}else{
			--top;
		}
	}
	while( bot < top ){
		point64f_t p;
		inter(hp[bot],hp[bot+1],p);
		
		if ( isIn(p,Hp[top]) ){
			break;
		}else{
			++bot;
		}
	}

	if ( top - bot <= 1 ){
		ans.clear();
		return;
	}

	//剩余的半平面求交点
	hp[top+1] = hp[bot];
	ans.clear();
	for(int i=bot;i<=top;++i){
		point64f_t p;
		inter(hp[i],hp[i+1],p);
		ans.push_back(p);
	}

	//去除重合的点，此处不需要，因为只要有一个点就可以满足题意
	deque<point64f_t>::iterator it;
	it = unique(ans.begin(),ans.end());
	ans.erase(it,ans.end());
	return;
}

int main(){
	int n;
	scanf("%d",&n);
	for(int i=0;i<n;++i){
		long double x1,y1,x2,y2;
		scanf("%Lf%Lf%Lf%Lf",&x1,&y1,&x2,&y2);
		Hp[i].a = y1 - y2;
		Hp[i].b = x2 - x1;
		Hp[i].c = x1 * y2 - x2 * y1;
	}
	//栅栏
	Hp[n].a = 1.0;Hp[n].b = 0.0;Hp[n].c = 0.0;
	Hp[++n].a = 0.0;Hp[n].b = 1.0;Hp[n].c = 0.0;
	Hp[++n].a = -1.0;Hp[n].b = 0.0;Hp[n].c = 10000.0;
	Hp[++n].a = 0.0;Hp[n].b = -1.0;Hp[n].c = 10000.0;

	n = n + 1;

    //排序
	sort(Hp,Hp+n);

	deque<point64f_t> ans;
	sandi(Hp,n,ans);

	//求凸多边形的面积
	if ( ans.size() <= 2 ){
		printf("0.0\n");
		return 0;
	}

	long double area = 0.0;
	for(unsigned int i=1;i<ans.size()-1;++i){
        area += cross(ans[0],ans[i],ans[i+1]);
	}
	if ( area < 0 ) area = -area;

	printf("%.1Lf\n",area/2.0);
	return 0;
}
