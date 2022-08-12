/**
    求四面体的体积，设四面体为OABC
    则体积=(OA×OB)·OC / 6
    输入6个棱长
*/
#include <bits/stdc++.h>
using namespace std;

double const EPS = 1E-10;
inline int sign(double x){
     if(x>EPS) return 1;
     return x<-EPS?-1:0;
}

inline double myacos(double x){
    if(x>1.0)x=1.0;
    if(x<-1.0)x=-1.0;
    return acos(x);
}

struct point3D64f_t{
    double x,y,z;
    point3D64f_t(double a=0.,double b=0.,double c=0.):x(a),y(b),z(c){}
    double norm()const{return x*x+y*y+z*z;}
    double length()const{return sqrt(norm());}
    void output()const{printf("%.6f %.6f %.6f",x,y,z);}
};

//向量A×向量B
point3D64f_t cross(point3D64f_t const&A,point3D64f_t const&B){
    return point3D64f_t(A.y*B.z-B.y*A.z,B.x*A.z-A.x*B.z,A.x*B.y-B.x*A.y);
}

//判断是否为0向量
inline bool is0(point3D64f_t const&t){
    return 0==sign(t.x)&&0==sign(t.y)&&0==sign(t.z);
}

//求向量A·B
double dot(point3D64f_t const&A,point3D64f_t const&B){
    return A.x*B.x+A.y*B.y+A.z*B.z;
}

//求AB长度的平方
double dist2(point3D64f_t const&A,point3D64f_t const&B){
    double x = A.x - B.x;
    double y = A.y - B.y;
    double z = A.z - B.z;
    return x*x+y*y+z*z;
}

point3D64f_t operator - (point3D64f_t const&lhs,point3D64f_t const&rhs){
    return point3D64f_t(lhs.x-rhs.x,lhs.y-rhs.y,lhs.z-rhs.z);
}

point3D64f_t operator + (point3D64f_t const&lhs,point3D64f_t const&rhs){
    return point3D64f_t(lhs.x+rhs.x,lhs.y+rhs.y,lhs.z+rhs.z);
}

//向量的数乘
point3D64f_t operator * (double lambda,point3D64f_t const&rhs){
    return point3D64f_t(lambda*rhs.x,lambda*rhs.y,lambda*rhs.z);
}

bool operator == (point3D64f_t const&lhs,point3D64f_t const&rhs){
    return is0(lhs-rhs);
}

//求直线AB与CD之间的距离
double dist(point3D64f_t const&A,point3D64f_t const&B,point3D64f_t const&C,point3D64f_t const&D){
    point3D64f_t L1 = A - B;
    point3D64f_t L2 = C - D;
    if(L1==L2){
        point3D64f_t n = cross(L1,A-C);
        if(is0(n)) return 0.0;//两直线重合
        return n.length() / sqrt(dist2(A,B));//两直线平行
    }

    double tmp = dot(cross(L1,A-C),L2);
    if(0==sign(tmp))  return 0.0;//两直线相交

    point3D64f_t n = cross(L1,L2);//公垂向量
    return fabs(dot(n,A-C)/n.length());
}

//求直线P1P2与平面ABC的交点
point3D64f_t interLineAndPlane(
    point3D64f_t const&P1,point3D64f_t const&P2,
    point3D64f_t const&A,point3D64f_t const&B,point3D64f_t const&C
){
    point3D64f_t mf = cross(A-B,A-C);
    point3D64f_t xfx = P2 - P1;
    return P1 + dot(mf,A-P1) / dot(mf,xfx) * xfx;
}
point3D64f_t A,B,C;
point3D64f_t const O(0.0,0.0,0.0);
int main(){
    //freopen("1.txt","r",stdin);
    //分别是AB,AC,AO,BC,BO,CO，令O是原点
    double a,b,c,d,e,f;
    while(EOF!=scanf("%lf%lf%lf%lf%lf%lf",&a,&b,&c,&d,&e,&f)){
        A = O;A.x = c;
        B = O;B.x = (c*c-a*a+e*e)/(c+c);B.y=sqrt(e*e-B.x*B.x);
        C = O;C.x = (c*c-b*b+f*f)/(c+c);
        C.y=(B.x*B.x+B.y*B.y-2.0*C.x*B.x-d*d+f*f)/(B.y+B.y);
        C.z=sqrt(f*f-C.x*C.x-C.y*C.y);
        double area = dot(cross(A-O,B-O),C-O)/6.0;
        printf("%.4f\n",fabs(area));
    }
    return 0;
}
