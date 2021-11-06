/**
    给定若干个点，有加点和删点操作，每一次操作要求：
    S(x) = SIGMA{SIGMA{dij^2}}
    其中dij表示i点和j点在某个直线上投影的距离
    相当于主成分分析，当旋转坐标轴以后，取第一维为x轴，则
    S(x) = sqrt(2 * Var(x))
    对原维度有协方差矩阵
    [cov(x, x), cov(x, y)]
    [cov(x, y), cov(y, y)]
    该矩阵的较大特征值就是所求
    cov(x, y) = E[(x-Ex)(y-Ey)]
    cov(x, x) = E[(x-Ex)^2] = var(x) 就是方差
    对于方差
    var(x) = 1/n*(x1^2+x2^2+...+nx平均^2-2(x1+x2+...)x平均)
           = 1/n*(SIGMA{xi^2} - x平均^2
           = E(x^2) - (Ex)^2
    对于协方差
    cov(x, y) = E(xy) - E(x)*E(y)
    因此对于动态，只需维护一些总和即可
    2×2的矩阵的特征值方程：x^2-(a11+a22)x+(a11a22-a21a12)=0
    使用longlong会WA，要用int128
*/
//#include <bits/stdc++.h>
#include <stdio.h>
#include <math.h>
using namespace std;

int getInt(){
	int sgn = 1;
	char ch = getchar();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = getchar();
	if ( '-' == ch ) {sgn = 0;ch=getchar();}

	int ret = (int)(ch-'0');
	while( '0' <= (ch=getchar()) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return sgn ? ret : -ret;
}

typedef __int128_t llt;

//解一元二次方程，返回较大的解
double f(double a,double b,double c){
    double delta = b*b-4.0*a*c;
    if(delta<0) delta = 0.0;
    return (-b+sqrt(delta))*0.5/a;
}

llt X[1000010],Y[1000010];
int main(){
    //freopen("1.txt","r",stdin);

    int nofkase = getInt();
    while(nofkase--){
        int q = getInt();
        int cmd, n = 0;


        int cnt = 0;
        llt x, y;
        llt x2 = 0LL, y2 = 0LL;
        llt xy = 0LL;
        llt xs = 0LL, ys = 0LL;

        for(int qi=1;qi<=q;++qi){
            if(1==(cmd=getInt())){
                ++cnt;

                x = X[qi] = getInt();
                y = Y[qi] = getInt();

                x2 += x * x;
                y2 += y * y;
                xy += x * y;
                xs += x;
                ys += y;


            }else{
                --cnt;

                int t = getInt();
                x = X[t];
                y = Y[t];

                x2 -= x * x;
                y2 -= y * y;
                xy -= x * y;
                xs -= x;
                ys -= y;

            }

            double a11 = (x2 - xs*xs/(double)(cnt))/(double)cnt;
            double a22 = (y2 - ys*ys/(double)(cnt))/(double)cnt;
            double a12 = (xy - xs*ys/(double)(cnt))/(double)cnt;

            printf("%.12f\n",sqrt(2.0*f(1.0,-(a11+a22),a11*a22-a12*a12)));
        }
    }
    return 0;
}
