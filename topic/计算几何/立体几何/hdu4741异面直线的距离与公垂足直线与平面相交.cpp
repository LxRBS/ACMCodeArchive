/**
    �ռ�ֱ�ߵľ���
    ��ռ�ֱ�ߵķ�����������L(a,b,c)
    ��L1==L2������ֱ���غϻ���ƽ��
    ��ֱ���ϸ�ȡһ�㣬����M��N����(MN��L1)��L2==0��˵����ֱ���ཻ��������
    ������0˵������
    ����ֱ�ߵľ��� = ������������������ / |��������|
    ��ֱ����ƽ��Ľ���
    ���� = ֱ�ߵ� + �淨������(ƽ��㣭ֱ�ߵ�)/(�淨�������߷�������) * �߷�������
    L2�Ĺ����㣬��Ȼ��L2��ƽ�棨L1�빫���������ɵ�ƽ�棩�Ľ�����
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

//����A������B
point3D64f_t cross(point3D64f_t const&A,point3D64f_t const&B){
    return point3D64f_t(A.y*B.z-B.y*A.z,B.x*A.z-A.x*B.z,A.x*B.y-B.x*A.y);
}

//�ж��Ƿ�Ϊ0����
inline bool is0(point3D64f_t const&t){
    return 0==sign(t.x)&&0==sign(t.y)&&0==sign(t.z);
}

//������A��B
double dot(point3D64f_t const&A,point3D64f_t const&B){
    return A.x*B.x+A.y*B.y+A.z*B.z;
}

//��AB���ȵ�ƽ��
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

//����������
point3D64f_t operator * (double lambda,point3D64f_t const&rhs){
    return point3D64f_t(lambda*rhs.x,lambda*rhs.y,lambda*rhs.z);
}

bool operator == (point3D64f_t const&lhs,point3D64f_t const&rhs){
    return is0(lhs-rhs);
}

//��ֱ��AB��CD֮��ľ���
double dist(point3D64f_t const&A,point3D64f_t const&B,point3D64f_t const&C,point3D64f_t const&D){
    point3D64f_t L1 = A - B;
    point3D64f_t L2 = C - D;
    if(L1==L2){
        point3D64f_t n = cross(L1,A-C);
        if(is0(n)) return 0.0;//��ֱ���غ�
        return n.length() / sqrt(dist2(A,B));//��ֱ��ƽ��
    }

    double tmp = dot(cross(L1,A-C),L2);
    if(0==sign(tmp))  return 0.0;//��ֱ���ཻ

    point3D64f_t n = cross(L1,L2);//��������
    return fabs(dot(n,A-C)/n.length());
}

//��ֱ��P1P2��ƽ��ABC�Ľ���
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
        point3D64f_t n = cross(A-B,C-D);//��������
        interLineAndPlane(A,B,C,D,C+n).output();
        printf(" ");
        interLineAndPlane(C,D,A,B,B+n).output();
        printf("\n");
    }
    return 0;
}
