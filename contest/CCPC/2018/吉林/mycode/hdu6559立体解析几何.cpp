/**
  给定一个圆锥以及一条射线，问射线何时与圆锥相交，保证相交
  首先做坐标变换，将圆锥的顶点移到原点，则锥面方程为
  x^2/r^2+y^2/r^2-z^2/h^2=0 (-h<=z<=0)
  射线的参数方程为
  x=x0+vxt
  y=y0+vyt
  z=z0+vzt
  代入求解即可
  还要考虑与圆锥底面相交的情况，当z=-h时（坐标变换之后），
  检查x^2+y^2<=r^2是否满足
  综合取较小的解即可
  C++编译报错（报y0是函数??），G++通过。
*/

#include <stdio.h>
#include <math.h>
double const EPS = 1E-8;

inline bool is0(double x){
    return -EPS<=x&&x<=EPS;
}

double r,h,x0,y0,z0,vx,vy,vz;
double a,b,c;
double x1,x2,x3;
int ans;

//解一元二次方程
void f(){
    if(is0(a)){
        x1 = -c/b;
        //检查z是否符合范围
        double z = z0 + vz*x1;
        if(is0(z+h)||is0(z)||(-h<z&&z<0.0)){
            ans = 1;
        }else{
            ans = 0;
        }
        return;
    }

    double delta = b*b-4.0*a*c;
    if(is0(delta)){
        x1 = -b/(a+a);
        //检查z是否符合范围
        double z = z0 + vz*x1;
        if(is0(z+h)||is0(z)||(-h<z&&z<0.0)){
            ans = 1;
        }else{
            ans = 0;
        }
        return;
    }

    //两个解
    x2 = (-b+sqrt(delta))/(a+a);
    x1 = (-b-sqrt(delta))/(a+a);

    //检查z
    double z = z0 + vz*x1;
    if(is0(z+h)||is0(z)||(-h<z&&z<0.0)){
        ans = 1;
        return;
    }

    z = z0 + vz*x2;
    if(is0(z+h)||is0(z)||(-h<z&&z<0.0)){
        ans = 1;
    }else{
        ans = 0;
    }
    return;
}

void f2(){
    if(is0(vz))return;

    double t = (-h-z0)/vz;

    double x = x0+vx*t;
    double y = y0*vy*t;

    double t2341 = x*x+y*y;
    if(is0(t2341-r*r)||t2341<r*r){
        ans = ans | 0x2;
        x3 = t;
    }
}

int main(){
    //freopen("1.txt","r",stdin);

    int nofkase;
    scanf("%d",&nofkase);
    for(int kase=1;kase<=nofkase;++kase){

        scanf("%lf%lf%lf%lf%lf%lf%lf%lf",&r,&h,&x0,&y0,&z0,&vx,&vy,&vz);
        z0 -= h;

        double r2 = r*r;
        double h2 = h*h;//平方

        a = (vx*vx+vy*vy)/r2-vz*vz/h2;
        b = 2.0*(vx*x0+vy*y0)/r2-2.0*vz*z0/h2;
        c = (x0*x0+y0*y0)/r2-z0*z0/h2;

        f();//与锥面相交解方程

        f2();//与底面相交

        double ret = x3;
        if(3==ans){
            ret = x1 < x3 ? x1 : x3;
        }else if(1==ans){
            ret = x1;
        }
        printf("Case %d: %.12f\n",kase,ret);
    }
    return 0;
}
