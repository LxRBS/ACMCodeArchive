/*
    给定若干线段，问是否存在一条直线使得这些线段在该直线上的投影具有公共交点
    实际上就是问是否存在一条直线与所有线段均相交，转化为线段与直线的相交问题 
*/
#include <iostream>
#include <cmath>

using namespace std;

double const EPS = 1E-8;

#define  isZero(x) ( ( ( x ) < EPS ) && ( ( x ) > -EPS ) )


struct point_t{
	double x;
	double y;
	point_t(double xx=0.,double yy=0.){x=xx;y=yy;}
};

//求OA×OB，叉积
double cross(const point_t &O,const point_t &A,const point_t &B){
	double xA = A.x - O.x;
	double yA = A.y - O.y;
	double xB = B.x - O.x;
	double yB = B.y - O.y;
	return xA * yB - xB * yA; 
}

//返回AB的距离
double dist(const point_t &A,const point_t &B){
	double x = A.x - B.x;
	double y = A.y - B.y;
	return sqrt( x * x + y * y );
}
//判断两点是否重合
bool isEqual(const point_t &A,const point_t &B){
    return isZero( dist(A,B) );
}

struct linesegment_t{
	point_t s;
	point_t e;
	linesegment_t(double sx=0.,double sy=0.,double ex=0.,double ey=0.){
		s.x = sx;
		s.y = sy;
		e.x = ex;
		e.y = ey;
	}
};

point_t point[202];

//ls1是否跨立ls2
//几何意义：如果ls1跨立ls2，说明ls1所在的直线必然与线段ls2相交
//          如果不跨立，则直线与ls2不想交
//注：若线段相交，必要条件之一为相互跨立
//是否跨立可以用叉积判断
bool isCross(const linesegment_t &ls1, const linesegment_t &ls2){
    return cross( ls1.s, ls2.s, ls1.e ) * cross( ls1.s, ls1.e, ls2.e ) >= 0;
}
//直线p1p2是否跨立线段p3p4
bool isCross(const point_t &p1,const point_t &p2, const point_t &p3,const point_t &p4){
	double ans1 = cross( p1, p3, p2 ) ;
	double ans2 = cross( p1, p2, p4 );
//    return  isZero(ans1) || isZero(ans2) || ans1 * ans2 > 0;
	return ans1 * ans2 >= 0;
}

//判断给定的直线p1p2，是否跨立所有的point数组里每两个点所组成的线段
//n是数组的size
bool isCross(const point_t &p1,const point_t &p2,point_t point[], int n){
    int i;
	for ( i=0;i<n;i+=2 ) if ( ! isCross(p1,p2,point[i],point[i+1]) ) return false;
	return true;
}
int main(){
	int T;
	scanf("%d",&T);
	while ( T-- ){
		int i,j,n;
        memset(point,0,sizeof(point));
        scanf("%d",&n);
		n *= 2;
		for ( i=0;i<n;i++ )
             scanf("%lf%lf",&point[i].x,&point[i].y);//将点看做点，而不是线段的端点，后续处理会方便的多
		
		//每两点组成一条直线，看能否与其他线段相交
		for ( i=0;i<n-1;i++ )for( j=i+1;j<n;j++ ){
			if ( ! isEqual(point[i],point[j]) ){//不是同一点，则构成一条线段，与其他线段比较
				if ( isCross(point[i],point[j],point,n) ) { goto LL;}//找到这样的线段则输出yes
			}            
		}
		printf("No!\n");continue;
LL:     printf("Yes!\n");
	}
	return 0;
}
