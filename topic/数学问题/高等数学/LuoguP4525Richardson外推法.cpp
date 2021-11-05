#include <bits/stdc++.h>
using namespace std;

//Richardson外推法
//计算f(x)在[x1,x2]上的定积分
//r为结果数组，n为计算的次数
double Richardson(double(*f)(double), double x1, double x2,int n,double r[][22]){
    double h = x2 - x1;
    int m = 1;

    //首先计算R[0][0]
    r[0][0] = 0.5 * h * (f(x1)+f(x2));

    for(int i=1;i<=n;++i){
        double *now = *(r + i);
        double *prev = *(r + i - 1);
        double h2 = h;
        h *= 0.5, m <<= 1;

        //计算R[i][0]
        double x = x1 + h;
        double& sum = now[0];
        sum = 0.0;
        for(int j=1;j<m;j+=2){
            sum += f(x);
            x += h2;
        }
        sum = 0.5 * prev[0] + h * sum;

        double fmi = 1.0;
        //计算R[i][j]
        for(int j=1;j<=i;++j){
            fmi = fmi * 4.0;
            now[j] = (now[j-1]*fmi - prev[j-1])/(fmi-1.0);
        }
    }
    return r[n][n];
}//*/

double T[22][22];
double A,B,C,D,L,R;
double f(double x){
    return (C*x+D)/(A*x+B);
}
int main(){
    //freopen("1.txt","r",stdin);
    cin>>A>>B>>C>>D>>L>>R;
    printf("%.6f\n",Richardson(f,L,R,10,T));
    return 0;
}
