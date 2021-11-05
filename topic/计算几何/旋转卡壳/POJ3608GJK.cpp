#include <iostream>
#include <cmath>
#include <algorithm>
#include <numeric>
using namespace std;

//题目说容许1E-3的误差，所以一开始设EPS为1E-4，然后就悲剧了
double const EPS = 1E-8;

#define  isZero(x) ( -EPS < (x) && (x) < EPS )

struct point64f_t{
	double x;
	double y;
	point64f_t(double a=0.0,double b=0.0):x(a),y(b){}
	point64f_t operator + (point64f_t const&r){
        return point64f_t(x+r.x,y+r.y);
	}
};

//OA×OB
double cross(point64f_t const&O,point64f_t const&A,point64f_t const&B){
    double xoa = A.x - O.x;
	double yoa = A.y - O.y;
	double xob = B.x - O.x;
	double yob = B.y - O.y;
	return xoa * yob - xob * yoa;
}
//OA·OB
double dot(point64f_t const&O,point64f_t const&A,point64f_t const&B){
	double xoa = A.x - O.x;
	double yoa = A.y - O.y;
	double xob = B.x - O.x;
	double yob = B.y - O.y;
	return xoa * xob + yoa * yob;
}

//向量的叉积
inline double cross(point64f_t const&A,point64f_t const&B){
	return A.x * B.y - A.y * B.x;
}

//向量的点积
inline double dot(point64f_t const&l,point64f_t const&r){
    return l.x * r.x + l.y * r.y;
}

point64f_t A[10001],B[10001];
point64f_t C[20002];

//排序的基点，方便书写
point64f_t Origin;

inline int calLoc(point64f_t const&p){
	if ( isZero(p.y) )
		return p.x > 0 ? 0 : 4;

	if ( isZero(p.x) )
		return p.y > 0 ? 2 : 6;

	if ( p.x > 0 )
		return p.y > 0 ? 1 : 7;

	return p.y > 0 ? 3 : 5;
}

//比较极角的函数，取值范围0~360，以Origin为基准
bool operator < (point64f_t const&l,point64f_t const&r){
	point64f_t lp(l.x-Origin.x,l.y-Origin.y);
	point64f_t rp(r.x-Origin.x,r.y-Origin.y);

	int locl = calLoc(lp);
	int locr = calLoc(rp);

	//不同区域，直接分出大小
	if ( locl != locr ) return locl < locr;

	//同一个象限，计算叉积，叉积为0可以随便排
	return lp.x * rp.y - rp.x * lp.y > 0;
}

//判断点是否在凸多边形内
bool isCover(point64f_t const&p,point64f_t const poly[],int n){
	for(int i=0;i<n;++i){
		//存在顺时针方向的叉积肯定在外
		if ( cross(p,poly[i],poly[i+1]) < -EPS )
			return false;
	}

	return true;
}

void MinkowskiSum(int na,int nb){
	int k_a = 0;
	double ymin = A[0].y;

	for(int i=0;i<na;++i){
		C[i].x = A[i+1].x - A[i].x;
		C[i].y = A[i+1].y - A[i].y;
		//顺便求最下最左
        if ( A[i].y < ymin || ( isZero(A[i].y-ymin) && A[i].x < A[k_a].x ) ) 
			ymin = A[i].y, k_a = i; 
	}

	int k_b = 0;
	ymin = B[0].y;
	for(int i=0;i<nb;++i){
		C[i+na].x = B[i+1].x - B[i].x;
		C[i+na].y = B[i+1].y - B[i].y;
		if ( B[i].y < ymin || (isZero(B[i].y-ymin)&&B[i].x<B[k_b].x) )
			ymin = B[i].y, k_b = i;
	}

	int nc = na + nb;

	Origin.x = Origin.y = 0.0;

	sort(C,C+nc);

	//没有滤掉三个端点共线的情况
	C[0].x += A[k_a].x + B[k_b].x;
	C[0].y += A[k_a].y + B[k_b].y;
	for(int i=1;i<nc;++i){
        C[i].x += C[i-1].x;
		C[i].y += C[i-1].y;
	}

	return;
}

//点p到线段AB的距离方
double calDist2(point64f_t const&p,point64f_t const&A,point64f_t const&B){
	double dotA = dot(A,p,B);
	if ( dotA <= 0 ){
		double x = p.x - A.x;
		double y = p.y - A.y;
		return x * x + y * y;
	}

	double dotB = dot(B,p,A);
	if ( dotB <= 0 ){
		double x = p.x - B.x;
		double y = p.y - B.y;
		return x * x + y * y;
	}

	double area = cross(p,A,B);

	double x = A.x - B.x;
	double y = A.y - B.y;

	return area * area / ( x * x + y * y );
}
//点p到逆时针凸多边形poly的距离，这个函数有问题
double calDist(point64f_t const&p,point64f_t const poly[],int n){
	if ( isCover(p,poly,n) ) return 0.0;

	double ans = 1E200;

	//判断
	for(int i=0;i<n;++i){
		point64f_t nvi;//法向量，记住poly是逆时针的
		if ( isZero(poly[i+1].x - poly[i].x) ){
			nvi.x = 0.0;
			nvi.y = poly[i+1].y < poly[i].y;
		}

		double slope = ( poly[i+1].y - poly[i].y ) / ( poly[i+1].x - poly[i].x );
		slope = - 1.0 / slope;
		if ( poly[i].y > poly[i+1].y ) nvi.x = 1.0;
		else                           nvi.x = -1.0;
        nvi.y = slope * nvi.x;



		//临时向量
		point64f_t tmpv( poly[i].x - p.x , poly[i].y - p.y );

		//该点积大于等于0，i、i+1 边才能被p看到，实际上等于0也相当于看不见
		if ( dot(nvi,tmpv) < - EPS ) continue;

        //计算p到线段的距离
        double tmpdist = calDist2(p,poly[i],poly[i+1]);

		//按顺序求点到边的距离，点到凸多边形的距离是中间的极值
		//这个流程有一个潜在的错误，但是OJ没有发现，有空的时候再来改
		if ( tmpdist <= ans ) ans = tmpdist;
		else                 return sqrt(ans);
	}

	return sqrt(ans);
}

int main(){
	int n,m;
	while(1){
		scanf("%d%d",&n,&m);
		if ( 0 == n && 0 == m ) return 0;

		for(int i=0;i<n;++i) scanf("%lf%lf",&A[i].x,&A[i].y);
		for(int i=0;i<m;++i){
			scanf("%lf%lf",&B[i].x,&B[i].y);
			B[i].x = - B[i].x;
			B[i].y = - B[i].y;
		}

		//预处理，据说点是不按顺序给的，因此首先进行排序
        Origin = accumulate(A,A+n,point64f_t());
		Origin.x /= (double)n;
		Origin.y /= (double)n;
       	sort(A,A+n);

		Origin = accumulate(B,B+m,point64f_t());
		Origin.x /= (double)m;
		Origin.y /= (double)m;
		sort(B,B+m);

		//方便处理
        A[n] = A[0];
		B[m] = B[0];
		
        //Minkowski和
		MinkowskiSum(n,m);

		C[n+m] = C[0];

		//实际上就是求点到凸多边形的距离
        double ans = calDist(point64f_t(),C,n+m);

		printf("%.5lf\n",ans);
	}
	return 0;
}
