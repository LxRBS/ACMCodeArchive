/*
    判断是否为简单多边形，然后求面积
*/
#include <stdio.h>
#include <algorithm>

using namespace std;

double const EPS = 1E-5;
inline bool is0(double x){
    return -EPS < x && x < EPS;
}

struct point64f_t{
    double x;
    double y;
    int idx;
};

bool operator < (point64f_t const&lhs,point64f_t const&rhs){
    return lhs.idx < rhs.idx;
}

//叉积
inline double cross(point64f_t const&O,point64f_t const&A,point64f_t const&B){
    double xoa = A.x - O.x;
    double yoa = A.y - O.y;
    double xob = B.x - O.x;
    double yob = B.y - O.y;
    return xoa * yob - xob * yoa;
}

//线段AB、CD是否相交
inline bool isInter(point64f_t const&A,point64f_t const&B,point64f_t const&C,point64f_t const&D){
    return min(A.x,B.x) <= max(C.x,D.x)
        && min(A.y,B.y) <= max(C.y,D.y)
        && min(C.x,D.x) <= max(A.x,B.x)
        && min(C.y,D.y) <= max(A.y,B.y)
        && cross(C,A,D) * cross(C,D,B) >= 0
        && cross(A,C,B) * cross(A,B,D) >= 0;
}

//判断p[n]是否为简单多边形
bool isSimple(point64f_t p[],int n){
    p[n] = p[0];

    for(int i=2;i<n-1;++i)if(isInter(p[0],p[1],p[i],p[i+1]))return false;

    for(int i=1;i<n-2;++i)for(int j=i+2;j<n;++j){
        if (isInter(p[i],p[i+1],p[j],p[j+1])){
            return false;
        }
    }
    return true;
}

//求多边形面积
double area(point64f_t p[],int n){
    double ans = 0.0;
    for(int i=1;i<n-1;++i){
        double t = cross(p[0],p[i],p[i+1]);
        ans += t;
    }
    if(ans<0) ans = -ans;
    return ans * 0.5;
}

bool __isOK(point64f_t p[]){
    int a[] = {1,2,3,7,5,6,4};
    for(int i=0;i<7;++i){
        if (p[i].idx != a[i]){
            return false;
        }
    }
    return true;
}
point64f_t P[10];
int main(){
    //freopen("1.txt","r",stdin);
    int kase;
    scanf("%d",&kase);
    while(kase--){
        for(int i=0;i<7;++i)scanf("%lf%lf",&P[i].x,&P[i].y),P[i].idx = i + 1;
        double prob;
        scanf("%lf",&prob);

        do{
            if(__isOK(P)){
                int x = 32;
            }
            bool flag = isSimple(P,7);
            double a = area(P,7);
            a /= 4.0;
            a = a * a * a;
            a = a - prob;
            if ( flag && is0(a) ) break;
        }while(next_permutation(P,P+7));

        printf("%d %d %d %d %d %d %d\n",P[0].idx,P[1].idx,P[2].idx,P[3].idx,P[4].idx,P[5].idx,P[6].idx);
    }
    return 0;
}
