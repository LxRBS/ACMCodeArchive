/**
    ��ά�ռ����һ���������ϰ���
    �ٸ�������,ȷ���������ڣ�������֮�����̾���
    ���Ƚⷽ�̿��߶������Ƿ��н���
    �����2�����㣬�������������ټ�һ��������
    ����ֱ�����߶γ���
*/
#include <bits/stdc++.h>
using namespace std;

double const EPS = 1E-12;

inline int sgn(double x){if(x>EPS)return 1;return x<-EPS?-1:0;}
inline double myasin(double x){if(x>1.0)x=1.0;else if(x<-1.0)x=-1.0;return asin(x);}
inline double myacos(double x){if(x>1.0)x=1.0;else if(x<-1.0)x=-1.0;return acos(x);}

struct point64f_t{
    double x,y,z;
    double dist2()const{return x*x+y*y+z*z;}
};

double dist2(point64f_t const&a,point64f_t const&b){
    double x=a.x-b.x,y=a.y-b.y,z=a.z-b.z;
    return (x*x+y*y+z*z);
}

int main(){
    //freopen("1.txt","r",stdin);
    int nofkase;
    scanf("%d",&nofkase);
    while(nofkase--){
        point64f_t o,s,t;
        double radius;
        scanf("%lf%lf%lf%lf",&o.x,&o.y,&o.z,&radius);
        scanf("%lf%lf%lf%lf%lf%lf",&s.x,&s.y,&s.z,&t.x,&t.y,&t.z);
        t.x -= o.x, t.y -= o.y, t.z -= o.z;
        s.x -= o.x, s.y -= o.y, s.z -= o.z;

        double r2 = radius*radius;
        //so����
        double ss = s.dist2();
        //to����
        double tt = t.dist2();
        //st����
        double d2 = dist2(s,t);
        //��sot
        double theta = myacos((ss+tt-d2)/(2.0*sqrt(ss)*sqrt(tt)));
        //��s�У�t��
        double sqq = sqrt(ss-r2), tqq = sqrt(tt-r2);
        //��Ƕ�
        double stheta = atan(sqq/radius), ttheta = atan(tqq/radius);
        double cha = theta - stheta - ttheta;
        int r = sgn(cha);
        if(r<=0){
            printf("%.8f\n",sqrt(d2));
        }else{
            printf("%.8f\n",sqq+tqq+radius*cha);
        }
    }
    return 0;
}
