/**
    多边形与圆相交求面积
*/
#include <bits/stdc++.h>
using namespace std;

double const PI = acos(-1.0);
double const EPS = 1E-8;
inline int sign(double x){
    if(x>EPS) return 1;
    return x<-EPS?-1:0;
}

inline double myasin(double x){
    if(x>1.0) x=1.0;
    if(x<-1.0) x=-1.0;
    return asin(x);
}

//求解一元二次方程根，返回根的数量，小根在前，大根在后
inline int root(double a,double b,double c,double&x1,double&x2){
    double delta = b*b-4.0*a*c;
    int tmp = sign(delta);

    if(tmp<0) return 0;

    if(0==tmp){
        x1 = x2 = -b / ( a + a );
        return 1;
    }

    delta = sqrt(delta);
    x1 = ( -b - (delta) ) / ( a + a );
    x2 = ( -b + (delta) ) / ( a + a );
    return 2;
}

//点的数据结构
struct point_t{
	double x,y;
	point_t(int a=0,int b=0):x(a),y(b){}
};

//叉积OA×OB
double cross(point_t const&O,point_t const&A,point_t const&B){
	double xoa = A.x - O.x;
	double yoa = A.y - O.y;
	double xob = B.x - O.x;
	double yob = B.y - O.y;
	return xoa * yob - xob * yoa;
}
double dot(point_t const&O,point_t const&A,point_t const&B){
	double xoa = A.x - O.x;
	double yoa = A.y - O.y;
	double xob = B.x - O.x;
	double yob = B.y - O.y;
	return xoa * xob + yob * yoa;
}
double dist2(point_t const&A,point_t const&B){
    double x = A.x - B.x;
    double y = A.y - B.y;
    return x*x+y*y;
}
//返回方向角，在(-180,180]之间，O、A、B各不相同
inline double getAngle(point_t const&O,point_t const&A,point_t const&B){
    double area = cross(O,A,B)*0.5;
    double ddot = dot(O,A,B);
    if(0==sign(area)){//OAB成一条直线
        if(sign(ddot)>0) return 0.0;
        return PI;
    }

    double OA = sqrt(dist2(O,A));
    double OB = sqrt(dist2(O,B));

    //首先求角度
    double theta = myasin(area*2.0/(OA*OB));
    if(sign(ddot)>=0)return theta;//说明是锐角，直接返回
    //正的钝角
    if(sign(area)>0) return PI-theta;
    //负的钝角
    return -theta - PI;
}

//求三角形OAB与圆O相交的有向面积，A、B必然不同
//令AB与圆的交点为P，则P=(1-t)A+tB，且|OP|^2=radius^2
//可以解一个关于t的一元二次方程
//[t(B.x-A.x)+(A.x-O.x)]^2+[t(B.y-A.y)+(A.y-O.y)]^2 = radius^2
//注意计算的是有向面积
double triangleAndCircleArea(point_t const&O,point_t const&A,point_t const&B,double radius){
    double area = cross(O,A,B)*0.5;
    int s = sign(area);
    if(0==s) return 0.0;

    double a = (B.x-A.x)*(B.x-A.x) + (B.y-A.y)*(B.y-A.y);
    double b = 2.0*( (B.x-A.x)*(A.x-O.x)+(B.y-A.y)*(A.y-O.y) );
    double c = (A.x-O.x)*(A.x-O.x)+(A.y-O.y)*(A.y-O.y)-radius*radius;

    double x1,x2;
    int cnt = root(a,b,c,x1,x2);

    double OA = sqrt(dist2(O,A));
    double OB = sqrt(dist2(O,B));
    double AB = sqrt(dist2(A,B));

    //直线A、B与圆无交点，就是扇形面积，只有1个交点也是扇形面积
    if(0==cnt||1==cnt){
        double theta = getAngle(O,A,B);
        return 0.5*radius*radius*theta;
    }

    /**两个根，[0,1]区间将整个实数分为三段，一共有6种可能性*/
    //两个根都不在[0,1]范围内，且在同一边，还是扇形面积
    if( sign(x2) < 0 || sign(x1-1.0) > 0 ){
        double theta = myasin(area*2.0/(OA*OB));
        return 0.5*radius*radius*theta;
    }

    //两个根都不在[0,1]范围内，且各在一边，说明A、B在圆内
    if( sign(x1) < 0 && sign(x2-1.0) > 0 ){
        return area;
    }

    //说明x1不在、x2在范围内，对应A在圆内、B在圆外的情况
    //此时面积是三角形OAP加扇形
    if( sign(x1) < 0 && sign(x2) >= 0 && sign(x2-1.0) <= 0 ){
        double theta = myasin(area*(1.0-x2)*2.0/(radius*OB));
        return area*x2 + 0.5*radius*radius*theta;
    }

    //说明x2不在、x1在范围内，对应B在圆内、A在圆外的情况
    //此时面积是三角形OPB加扇形
    if( sign(x1) >= 0 && sign(x1-1.0) <= 0 && sign(x2-1.0) > 0 ){
        double theta = myasin(area*x1*2.0/(radius*OA));
        return area * (1.0-x1) + 0.5 * radius * radius * theta;
    }

    //x1和x2都在A、B之间，此时面积是两个扇形加一个三角形
    double theta1 = myasin(area*x1*2.0/(radius*OA));
    double theta2 = myasin(area*(1.0-x2)*2.0/(radius*OB));
    return area*(x2-x1) + 0.5*radius*radius*(theta1+theta2);
}

point_t O,P[100100];
double Radius;
point_t T,Speed;
double H;
int main(){
    //freopen("1.txt","r",stdin);
    while(EOF!=scanf("%lf%lf%lf%lf%lf%lf",&T.x,&T.y,&H,&Speed.x,&Speed.y,&Radius)){
        int n;
        scanf("%d",&n);
        for(int i=0;i<n;++i)scanf("%lf%lf",&P[i].x,&P[i].y);
        P[n] = P[0];

        //求下落时间
        double t = sqrt(H/5.0);
        //求圆心
        O.x = T.x + Speed.x * t;
        O.y = T.y + Speed.y * t;

        double ans = 0.0;
        for(int i=0;i<n;++i){
            ans += triangleAndCircleArea(O,P[i],P[i+1],Radius);
        }
        printf("%.2f\n",fabs(ans));
    }
}
