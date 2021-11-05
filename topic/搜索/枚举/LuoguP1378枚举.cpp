/**
   长方形，N个点
   每次选一个点进行圆形扩展，直到圆碰到之前的圆或者边界
   问最后剩下的空间最少是多少
   N不超过6
*/
#include <bits/stdc++.h>
using namespace std;

double const PI = acos(-1.0);
double const EPS = 1E-8;
int sgn(double x){if(fabs(x)<EPS)return 0;return x>0?1:-1;}

int const FAC[] = {1,1,2,6,24,120,720};
double X[11],Y[11];
int A[] = {0,1,2,3,4,5};
int N;
int Left,Bottom,Top,Right;

double R[11];
//计算以当前顺序得到的面积
double f(){
    double ans = (Right-Left)*(Top-Bottom);
    for(int i=0;i<N;++i){
        int ai = A[i];
        //计算第i个点的合法半径
        //首先计算与矩形四周的半径
        double r = X[ai]-Left;
        r = min(r,Right-X[ai]);
        r = min(r,Top-Y[ai]);
        r = min(r,Y[ai]-Bottom);
        //计算与之前的圆接触的半径
        for(int j=0;j<i;++j){
            int aj = A[j];
            double x = X[ai]-X[aj], y = Y[ai]-Y[aj];
            double tmp = sqrt(x*x+y*y) - R[aj];
            r = min(r,tmp);
            if(sgn(r)<=0){
                r = 0;
                break;
            }
        }
        R[ai] = r;
        ans -= PI*r*r;
    }
    return ans;
}

int main(){
    //freopen("1.txt","r",stdin);
    scanf("%d%d%d%d%d",&N,&Left,&Bottom,&Right,&Top);
    for(int i=0;i<N;++i)scanf("%lf%lf",X+i,Y+i);
    if(Left>Right)swap(Left,Right);
    if(Bottom>Top)swap(Bottom,Top);

    double ans = (Right-Left)*(Top-Bottom);
    for(int i=0,n=FAC[N];i<n;++i){
        ans = min(ans,f());
        next_permutation(A,A+N);
    }
    printf("%.0f\n",ans);
    return 0;
}
