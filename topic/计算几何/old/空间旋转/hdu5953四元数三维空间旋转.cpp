#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

double const PI = acos(-1.0);

//旋转矩阵
struct Matrix{
    double data[3][3];
    double* operator [] (int idx) {return data[idx];}
    double const * operator [] (int idx) const{return data[idx];}
};

//四元数
struct Quat{
    double data[4];//表示wxyz
    Quat(double w=0.0,double x=0.0,double y=0.0,double z=0.0){data[0]=w,data[1]=x,data[2]=y,data[3]=z;}
    double& operator [] (int idx){return data[idx];}
    double const& operator [] (int idx)const{return data[idx];}
};

//四元数的叉乘
Quat operator * (Quat const&lhs,Quat const&rhs){
    return Quat(
               lhs[0]*rhs[0] - lhs[1]*rhs[1] - lhs[2]*rhs[2] - lhs[3] * rhs[3],
               0.0,//求出第一项即可
               0.0,
               0.0
           );
}

//根据旋转矩阵求得四元数
void matrix2Quat(Matrix const&mat,Quat&q){
    double tq[4];
    tq[0] = 1. + mat[0][0] + mat[1][1] + mat[2][2];
    tq[1] = 1. + mat[0][0] - mat[1][1] - mat[2][2];
    tq[2] = 1. - mat[0][0] + mat[1][1] - mat[2][2];
    tq[3] = 1. - mat[0][0] - mat[1][1] + mat[2][2];

    int k = 0;
    for(int i=1;i<4;++i)if(tq[k]<tq[i])k=i;

    if ( 0 == k ){
        q[0] = tq[0];
        q[1] = mat[1][2] - mat[2][1];
        q[2] = mat[2][0] - mat[0][2];
        q[3] = mat[0][1] - mat[1][0];
    }else if ( 1 == k ){
        q[0] = mat[1][2] - mat[2][1];
        q[1] = tq[1];
        q[2] = mat[0][1] + mat[1][0];
        q[3] = mat[2][0] + mat[0][2];
    }else if ( 2 == k ){
        q[0] = mat[2][0] - mat[0][2];
        q[1] = mat[0][1] + mat[1][0];
        q[2] = tq[2];
        q[3] = mat[1][2] + mat[2][1];
    }else if ( 3 == k ){
        q[0] = mat[0][1] - mat[1][0];
        q[1] = mat[2][0] + mat[0][2];
        q[2] = mat[1][2] + mat[2][1];
        q[3] = tq[3];
    }else{
        while(1);
    }

    double s = sqrt( 0.25 / tq[k] );
    q[0] *= s, q[1] *= s, q[2] *= s, q[3] *= s;
}

int N;
Matrix Mat[110];
Quat Q[110],IQ[110];
bool read(){
    if ( EOF == scanf("%d",&N) ) return false;
    for(int n=0;n<N;++n){
        for(int i=0;i<3;++i)scanf("%lf%lf%lf",Mat[n][i],Mat[n][i]+1,Mat[n][i]+2);
        matrix2Quat(Mat[n],Q[n]);

        //因为Q是单位四元数，所以其逆就等于其共轭
        IQ[n][0] = Q[n][0];
        IQ[n][1] = -Q[n][1], IQ[n][2] = -Q[n][2], IQ[n][3] = -Q[n][3];
    }
    return true;
}

double Ans[110];
void proc(){
    fill(Ans,Ans+N,1E9);

    for(int i=0;i<N-1;++i)for(int j=i+1;j<N;++j){
        Quat q = IQ[i] * Q[j];
        if ( q[0] > 1.0 ) q[0] = 1.0;
        else if ( q[0] < -1.0 ) q[0] = -1.0;
        double t = 2.0 * acos(q[0]);
        if ( t > PI ) t = 2.0 * PI - t;

        if ( t < Ans[i] ) Ans[i] = t;
        if ( t < Ans[j] ) Ans[j] = t;
    }

    for(int i=0;i<N;++i)printf("%.2f ",Ans[i]);
    printf("\n");
}
int main(){
    //freopen("1.txt","r",stdin);
    while ( read() ) proc();
    return 0;
}
