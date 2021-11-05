#include <bits/stdc++.h>
using namespace std;

double const EPS = 1E-8;
inline int sgn(double x){return x>EPS?1:(x<-EPS?-1:0);}
inline bool is0(double x){return 0==sgn(x);}
inline bool isEq(double x,double y){return is0(x-y);}

//Romberg����,��f(x)��[x1,x2]�ϵĶ�����
//r[0]��ʾT���У�r[1]��ʾS����,r[2]��ʾC����,r[3]��ʾR����
double Romberg(double(*f)(double), double x1, double x2,double r[][4]){
    double h = x2 - x1;
    int m = 1;
    r[0][3] = 0.0;

    //���ȼ���T0
    r[0][0] = 0.5 * h * (f(x1)+f(x2));

    for(int i=1;;++i){
        double *now = *(r + i);
        double *prev = *(r + i - 1);
        double h2 = h;
        h *= 0.5, m <<= 1;

        //����Ti
        double x = x1 + h;
        double& sum = now[0];
        sum = 0.0;
        for(int j=1;j<m;j+=2){
            sum += f(x);
            x += h2;
        }
        sum = 0.5 * prev[0] + h * sum;

        //����Si
        now[1] = (4.0*now[0]-prev[0]) / 3.0;
        //����Ci
        now[2] = (16.0*now[1]-prev[1]) / 15.0;
        //����Ri
        now[3] = (64.0*now[2]-prev[2]) / 63.0;
        //cout<<i<<" "<<r[i][0]<<" "<<r[i][3]<<endl;
        //�ж�
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
