#include <bits/stdc++.h>
using namespace std;

double const EPS = 1E-8;
inline int sgn(double x){return x>EPS?1:(x<-EPS?-1:0);}
inline bool is0(double x){return 0==sgn(x);}
inline bool isEq(double x,double y){return is0(x-y);}

//Romberg积分,求f(x)在[x1,x2]上的定积分
//r[0]表示T序列，r[1]表示S序列,r[2]表示C序列,r[3]表示R序列
double Romberg(double(*f)(double), double x1, double x2,double r[][4]){
    double h = x2 - x1;
    int m = 1;
    r[0][3] = 0.0;

    //首先计算T0
    r[0][0] = 0.5 * h * (f(x1)+f(x2));

    for(int i=1;;++i){
        double *now = *(r + i);
        double *prev = *(r + i - 1);
        double h2 = h;
        h *= 0.5, m <<= 1;

        //计算Ti
        double x = x1 + h;
        double& sum = now[0];
        sum = 0.0;
        for(int j=1;j<m;j+=2){
            sum += f(x);
            x += h2;
        }
        sum = 0.5 * prev[0] + h * sum;

        //计算Si
        now[1] = (4.0*now[0]-prev[0]) / 3.0;
        //计算Ci
        now[2] = (16.0*now[1]-prev[1]) / 15.0;
        //计算Ri
        now[3] = (64.0*now[2]-prev[2]) / 63.0;
        //cout<<i<<" "<<r[i][0]<<" "<<r[i][3]<<endl;
        //判断
        if(isEq(prev[3],now[3])) return now[3];
    }
    throw runtime_error("XXXXXX");
}//*/

double T[10010][4];
double A,B,C,D,L,R;
double f(double x){
    return (C*x+D)/(A*x+B);
}
int main(){
    //freopen("1.txt","r",stdin);
    cin>>A>>B>>C>>D>>L>>R;
    printf("%.6f\n",Romberg(f,L,R,T));
    return 0;
}
