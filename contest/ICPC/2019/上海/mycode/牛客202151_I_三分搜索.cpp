/**
   一个矩形，内有一对传送门，通过传送门不需要时间
   求：在矩形中找两个点，使其距离最远
   猜测必有一点在顶点，另外一点应该在边上，搜
*/

#include <bits/stdc++.h>
using namespace std;

double const EPS = 1E-7;

inline int sgn(double x){return x<-EPS?-1:(x>EPS?1:0);}
inline bool is0(double x){return sgn(x)==0;}
inline bool isEq(double x,double y){return is0(x-y);}

double A, B, X1, Y1, X2, Y2;

inline double dist(double x1,double y1,double x2,double y2){
    double x = x1 - x2;
    double y = y1 - y2;
    return sqrt(x*x+y*y);
}

//求两点之间的距离
double f(double x1,double y1,double x2,double y2){
    return min(min(dist(x1,y1,X1,Y1)+dist(X2,Y2,x2,y2),dist(x1,y1,X2,Y2)+dist(X1,Y1,x2,y2)), dist(x1,y1,x2,y2));
}

double trinary(double ox,double oy,double ax,double ay,double bx,double by,double&ansx,double&ansy){
    double t,m1,m2,left,right;
    if(isEq(ay,by)){//水平线
        left=ax,right=bx;
        do{
            t = (right-left)/3.0;
            m1 = left + t;
            m2 = right - t;
            if(f(ox,oy,m1,ay)>f(ox,oy,m2,by)) right = m2;
            else left = m1;
        }while(!isEq(left,right));
        return f(ox,oy,ansx=right,ansy=ay);
    }else if(isEq(ax,bx)){
        left=ay,right=by;
        do{
            t = (right-left)/3.0;
            m1 = left + t;
            m2 = right - t;
            if(f(ox,oy,ax,m1)>f(ox,oy,ax,m2)) right = m2;
            else left = m1;
        }while(!isEq(left,right));
        return f(ox,oy,ansx=ax,ansy=right);
    }else{
        throw runtime_error("wrong xy");
    }
}


void cmp(double ox,double oy,double ax,double ay,double bx,double by,double&ans,double&x1,double&y1,double&x2,double&y2){
    double tmp, ansx, ansy;
    tmp = trinary(ox,oy,ax,ay,bx,by,ansx,ansy);
    if(sgn(ans-tmp)<0){
        ans = tmp;
        x1 = ox, y1 = oy, x2 = ansx, y2 = ansy;
    }
}

void proc(){
    //依次固定4个端点，搜4条边
    double ans = -1E-100;
    double x1,y1,x2,y2;
    //0,0的
    cmp(0,0,0,B,A,B,ans,x1,y1,x2,y2);
    cmp(0,0,A,0,A,B,ans,x1,y1,x2,y2);
    cmp(0,0,0,0,0,B,ans,x1,y1,x2,y2);
    cmp(0,0,0,0,A,0,ans,x1,y1,x2,y2);
    //A0的
    cmp(A,0,0,0,0,B,ans,x1,y1,x2,y2);
    cmp(A,0,0,B,A,B,ans,x1,y1,x2,y2);
    cmp(A,0,0,0,A,0,ans,x1,y1,x2,y2);
    cmp(A,0,A,0,A,B,ans,x1,y1,x2,y2);
    //0B
    cmp(0,B,0,0,A,0,ans,x1,y1,x2,y2);
    cmp(0,B,A,0,A,B,ans,x1,y1,x2,y2);
    cmp(0,B,0,B,A,B,ans,x1,y1,x2,y2);
    cmp(0,B,0,0,0,B,ans,x1,y1,x2,y2);
    //AB
    cmp(A,B,0,0,0,B,ans,x1,y1,x2,y2);
    cmp(A,B,0,0,A,0,ans,x1,y1,x2,y2);
    cmp(A,B,0,B,A,B,ans,x1,y1,x2,y2);
    cmp(A,B,A,0,A,B,ans,x1,y1,x2,y2);
    printf("%.8f %.8f\n",x1,y1);
    printf("%.8f %.8f\n",x2,y2);
}

int main(){
    //freopen("1.txt","r",stdin);
    int nofkase;
    scanf("%d",&nofkase);
    for(int kase=1;kase<=nofkase;++kase){
        scanf("%lf%lf%lf%lf%lf%lf",&A,&B,&X1,&Y1,&X2,&Y2);
        printf("Case #%d:\n", kase);
        proc();
    }
}
