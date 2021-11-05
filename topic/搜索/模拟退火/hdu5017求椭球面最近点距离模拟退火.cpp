/**
    ����һ�������棬�����о���ԭ������ĵ�ľ���
    ģ���˻��㷨
*/
#include <bits/stdc++.h>
using namespace std;

double const EPS = 1E-10;
inline int sign(double x){
     if(x>EPS) return 1;
     return x<-EPS?-1:0;
}

inline double dist2(double x,double y,double z){
    return (x*x+y*y+z*z);
}

inline double myrand(){
    return rand()%10000/10000.0;
}

double a,b,c,d,e,f;

//����x��y����z������ֱ�����������ཻ
double getZ(double x,double y){
    double A = c;
    double B = d*y + e*x;
    double C = a*x*x+b*y*y+f*x*y-1.0;
    double delta = B*B-4.0*A*C;
    if(sign(delta)<0) return 1E300;
    if(0==sign(delta)) return -B/(A+A);

    //����ֵС��
    if(sign(B)>=0) return (-B+sqrt(delta))/(A+A);
    return (-B-sqrt(delta))/(A+A);
}

double const DX[] = {0,1,0,-1,1,1,-1,-1};
double const DY[] = {1,0,-1,0,1,-1,1,-1};

//ģ���˻�
double sa(){
    double T = 1.0;//��ʼ�¶�
    double T_min = EPS;//�����¶�
    double speed = 0.99;//�����ٶ�
    double x = 0.0, y = 0.0, z = sqrt(1.0/c);//��ʼλ��
    double ans2 = 1.0/c;
    double dx,dy,dz;

    while(T>T_min){
        double tmp = 1E300,nx,ny,nz;
        for(int i=0;i<8;++i){
            dx = x + DX[i] * T;
            dy = y + DY[i] * T;
            dz = getZ(dx,dy);

            if(sign(dz-1E100)>=0) continue;

            double tt = dist2(dx,dy,dz);
            if(tt<tmp){
                tmp = tt, nx = dx, ny = dy, nz = dz;
            }
        }
        if( sign(tmp-ans2) < 0 || (fabs((tmp-ans2)/T))<myrand() ){
            ans2 = tmp;
            x=nx,y=ny,z=nz;
        }

        T *= speed;
    }
    return sqrt(ans2);
}
int main(){
    //freopen("1.txt","r",stdin);
    srand((unsigned)time(NULL));
    while(EOF!=(scanf("%lf%lf%lf%lf%lf%lf",&a,&b,&c,&d,&e,&f))){
        printf("%.10f\n",sa());
    }
    return 0;
}
