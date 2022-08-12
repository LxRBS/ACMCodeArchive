/*
    ���������߶Σ����Ƿ����һ��ֱ��ʹ����Щ�߶��ڸ�ֱ���ϵ�ͶӰ���й�������
    ʵ���Ͼ������Ƿ����һ��ֱ���������߶ξ��ཻ��ת��Ϊ�߶���ֱ�ߵ��ཻ���� 
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

//��OA��OB�����
double cross(const point_t &O,const point_t &A,const point_t &B){
	double xA = A.x - O.x;
	double yA = A.y - O.y;
	double xB = B.x - O.x;
	double yB = B.y - O.y;
	return xA * yB - xB * yA; 
}

//����AB�ľ���
double dist(const point_t &A,const point_t &B){
	double x = A.x - B.x;
	double y = A.y - B.y;
	return sqrt( x * x + y * y );
}
//�ж������Ƿ��غ�
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

//ls1�Ƿ����ls2
//�������壺���ls1����ls2��˵��ls1���ڵ�ֱ�߱�Ȼ���߶�ls2�ཻ
//          �������������ֱ����ls2���뽻
//ע�����߶��ཻ����Ҫ����֮һΪ�໥����
//�Ƿ���������ò���ж�
bool isCross(const linesegment_t &ls1, const linesegment_t &ls2){
    return cross( ls1.s, ls2.s, ls1.e ) * cross( ls1.s, ls1.e, ls2.e ) >= 0;
}
//ֱ��p1p2�Ƿ�����߶�p3p4
bool isCross(const point_t &p1,const point_t &p2, const point_t &p3,const point_t &p4){
	double ans1 = cross( p1, p3, p2 ) ;
	double ans2 = cross( p1, p2, p4 );
//    return  isZero(ans1) || isZero(ans2) || ans1 * ans2 > 0;
	return ans1 * ans2 >= 0;
}

//�жϸ�����ֱ��p1p2���Ƿ�������е�point������ÿ����������ɵ��߶�
//n�������size
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
             scanf("%lf%lf",&point[i].x,&point[i].y);//���㿴���㣬�������߶εĶ˵㣬��������᷽��Ķ�
		
		//ÿ�������һ��ֱ�ߣ����ܷ��������߶��ཻ
		for ( i=0;i<n-1;i++ )for( j=i+1;j<n;j++ ){
			if ( ! isEqual(point[i],point[j]) ){//����ͬһ�㣬�򹹳�һ���߶Σ��������߶αȽ�
				if ( isCross(point[i],point[j],point,n) ) { goto LL;}//�ҵ��������߶������yes
			}            
		}
		printf("No!\n");continue;
LL:     printf("Yes!\n");
	}
	return 0;
}
