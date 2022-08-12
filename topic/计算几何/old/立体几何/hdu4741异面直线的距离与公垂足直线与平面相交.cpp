/**
    空间直线的距离
    设空间直线的方向向量记作L(a,b,c)
    若L1==L2，则两直线重合或者平行
    两直线上各取一点，记作M和N，则(MN×L1)·L2==0，说明两直线相交，即共面
    不等于0说明异面
    异面直线的距离 = 公垂向量·连接向量 / |公垂向量|
    求直线与平面的交点
    交点 = 直线点 + 面法向量·(平面点－直线点)/(面法向量·线方向向量) * 线方向向量
    L2的公垂足，必然在L2与平面（L1与公垂向量构成的平面）的交点上
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
point3D64f_t A,B,C,D;
int main(){
    //freopen("1.txt","r",stdin);
    int nofkase;
    scanf("%d",&nofkase);
    while(nofkase--){
        scanf("%lf%lf%lf%lf%lf%lf",&A.x,&A.y,&A.z,&B.x,&B.y,&B.z);
        scanf("%lf%lf%lf%lf%lf%lf",&C.x,&C.y,&C.z,&D.x,&D.y,&D.z);
        printf("%.6f\n",dist(A,B,C,D));
        point3D64f_t n = cross(A-B,C-D);//公垂向量
        interLineAndPlane(A,B,C,D,C+n).output();
        printf(" ");
        interLineAndPlane(C,D,A,B,B+n).output();
        printf("\n");
    }
    return 0;
}
