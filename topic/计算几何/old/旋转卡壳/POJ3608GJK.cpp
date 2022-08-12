#include <iostream>
#include <cmath>
#include <algorithm>
#include <numeric>
using namespace std;

//��Ŀ˵����1E-3��������һ��ʼ��EPSΪ1E-4��Ȼ��ͱ�����
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

//OA��OB
double cross(point64f_t const&O,point64f_t const&A,point64f_t const&B){
    double xoa = A.x - O.x;
	double yoa = A.y - O.y;
	double xob = B.x - O.x;
	double yob = B.y - O.y;
	return xoa * yob - xob * yoa;
}
//OA��OB
double dot(point64f_t const&O,point64f_t const&A,point64f_t const&B){
	double xoa = A.x - O.x;
	double yoa = A.y - O.y;
	double xob = B.x - O.x;
	double yob = B.y - O.y;
	return xoa * xob + yoa * yob;
}

//�����Ĳ��
inline double cross(point64f_t const&A,point64f_t const&B){
	return A.x * B.y - A.y * B.x;
}

//�����ĵ��
inline double dot(point64f_t const&l,point64f_t const&r){
    return l.x * r.x + l.y * r.y;
}

point64f_t A[10001],B[10001];
point64f_t C[20002];

//����Ļ��㣬������д
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

//�Ƚϼ��ǵĺ�����ȡֵ��Χ0~360����OriginΪ��׼
bool operator < (point64f_t const&l,point64f_t const&r){
	point64f_t lp(l.x-Origin.x,l.y-Origin.y);
	point64f_t rp(r.x-Origin.x,r.y-Origin.y);

	int locl = calLoc(lp);
	int locr = calLoc(rp);

	//��ͬ����ֱ�ӷֳ���С
	if ( locl != locr ) return locl < locr;

	//ͬһ�����ޣ������������Ϊ0���������
	return lp.x * rp.y - rp.x * lp.y > 0;
}

//�жϵ��Ƿ���͹�������
bool isCover(point64f_t const&p,point64f_t const poly[],int n){
	for(int i=0;i<n;++i){
		//����˳ʱ�뷽��Ĳ���϶�����
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
		//˳������������
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

	//û���˵������˵㹲�ߵ����
	C[0].x += A[k_a].x + B[k_b].x;
	C[0].y += A[k_a].y + B[k_b].y;
	for(int i=1;i<nc;++i){
        C[i].x += C[i-1].x;
		C[i].y += C[i-1].y;
	}

	return;
}

//��p���߶�AB�ľ��뷽
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
//��p����ʱ��͹�����poly�ľ��룬�������������
double calDist(point64f_t const&p,point64f_t const poly[],int n){
	if ( isCover(p,poly,n) ) return 0.0;

	double ans = 1E200;

	//�ж�
	for(int i=0;i<n;++i){
		point64f_t nvi;//����������סpoly����ʱ���
		if ( isZero(poly[i+1].x - poly[i].x) ){
			nvi.x = 0.0;
			nvi.y = poly[i+1].y < poly[i].y;
		}

		double slope = ( poly[i+1].y - poly[i].y ) / ( poly[i+1].x - poly[i].x );
		slope = - 1.0 / slope;
		if ( poly[i].y > poly[i+1].y ) nvi.x = 1.0;
		else                           nvi.x = -1.0;
        nvi.y = slope * nvi.x;



		//��ʱ����
		point64f_t tmpv( poly[i].x - p.x , poly[i].y - p.y );

		//�õ�����ڵ���0��i��i+1 �߲��ܱ�p������ʵ���ϵ���0Ҳ�൱�ڿ�����
		if ( dot(nvi,tmpv) < - EPS ) continue;

        //����p���߶εľ���
        double tmpdist = calDist2(p,poly[i],poly[i+1]);

		//��˳����㵽�ߵľ��룬�㵽͹����εľ������м�ļ�ֵ
		//���������һ��Ǳ�ڵĴ��󣬵���OJû�з��֣��пյ�ʱ��������
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

		//Ԥ������˵���ǲ���˳����ģ�������Ƚ�������
        Origin = accumulate(A,A+n,point64f_t());
		Origin.x /= (double)n;
		Origin.y /= (double)n;
       	sort(A,A+n);

		Origin = accumulate(B,B+m,point64f_t());
		Origin.x /= (double)m;
		Origin.y /= (double)m;
		sort(B,B+m);

		//���㴦��
        A[n] = A[0];
		B[m] = B[0];
		
        //Minkowski��
		MinkowskiSum(n,m);

		C[n+m] = C[0];

		//ʵ���Ͼ�����㵽͹����εľ���
        double ans = calDist(point64f_t(),C,n+m);

		printf("%.5lf\n",ans);
	}
	return 0;
}
