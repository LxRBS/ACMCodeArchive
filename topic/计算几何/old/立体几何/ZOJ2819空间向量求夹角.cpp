/**
    三维空间中，给定若干星星坐标，问望远镜能否看得到。
    望远镜给出了方向向量以及张角。
    因此只要判断星星与方向向量的夹角小于张角即可
    空间向量的夹角与平面向量夹角类似:cosθ = |a·b| / ( |a|*|b| )
*/
#include <bits/stdc++.h>
using namespace std;

double const EPS = 1E-8;
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
};

//求OA·OB
double dot(point3D64f_t const&O,point3D64f_t const&A,point3D64f_t const&B){
    double x1 = A.x - O.x;
    double y1 = A.y - O.y;
    double z1 = A.z - O.z;
    double x2 = B.x - O.x;
    double y2 = B.y - O.y;
    double z2 = B.z - O.z;
    return x1*x2 + y1*y2 + z1*z2;
}

//求AB长度的平方
double dist2(point3D64f_t const&A,point3D64f_t const&B){
    double x = A.x - B.x;
    double y = A.y - B.y;
    double z = A.z - B.z;
    return x*x+y*y+z*z;
}

int N,M;
point3D64f_t Star[510];
double D[510];
point3D64f_t const O(0.0,0.0,0.0);
point3D64f_t Tele[55];
double Psai[55];
double DD[55];

bool read(){
    scanf("%d",&N);
    if(0==N) return false;

    //读入星星
    for(int i=0;i<N;++i){
        scanf("%lf%lf%lf",&Star[i].x,&Star[i].y,&Star[i].z);
        D[i] = sqrt(dist2(O,Star[i]));
    }

    //读入望远镜
    scanf("%d",&M);
    for(int i=0;i<M;++i){
        scanf("%lf%lf%lf%lf",&Tele[i].x,&Tele[i].y,&Tele[i].z,Psai+i);
        DD[i] = sqrt(dist2(O,Tele[i]));
    }
    return true;
}

//第idx星星
int f(int idx){
    point3D64f_t const&star = Star[idx];
    double const&d = D[idx];
    for(int i=0;i<M;++i){
        double theta = myacos(dot(O,Tele[i],star)/(d*DD[i]));
        if(sign(theta-Psai[i])<0) {
            return 1;
        }
    }
    return 0;
}

int proc(){
    int ret = 0;
    for(int i=0;i<N;++i)ret+=f(i);
    return ret;
}

int main(){
    //freopen("1.txt","r",stdin);
    while(read()){
        printf("%d\n",proc());
    }
    return 0;
}
