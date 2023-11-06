/**
    给定三角形以及一个点P
    如果点P在三角形的边上，还要再找一个在边上的点Q
    使得PQ平分三角形的面积
*/
#include <bits/stdc++.h>
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

double const EPS = 1E-12;
inline int sgn(double x){
    if(x>EPS) return 1;
    return x<-EPS?-1:0;
}
double myacos(double x){
    if(x>1.0) x = 1.0;
    else if(x<-1.0) x= -1.0;
    return acos(x);
}

struct point64f_t{
    double x,y;
};

//叉积
double cross(point64f_t const&O,point64f_t const&A,point64f_t const&B){
    double xoa = A.x - O.x;
    double yoa = A.y - O.y;
    double xob = B.x - O.x;
    double yob = B.y - O.y;
    return xoa * yob - xob * yoa;
}

//判断点在线段上
bool isIn(point64f_t const&p, point64f_t const&A, point64f_t const&B){
    return 0==sgn(cross(p,A,B))
        && min(A.x,B.x)<=p.x && p.x<=max(A.x,B.x)
        && min(A.y,B.y)<=p.y && p.y<=max(A.y,B.y);
}

//求两点距离的平方
double dist2(point64f_t const&A,point64f_t const&B){
    double x = A.x - B.x;
    double y = A.y - B.y;
    return x*x+y*y;
}

//判断两点是否重合
inline bool isEqual(point64f_t const&A,point64f_t const&B){
    return 0 == sgn(dist2(A,B));
}

point64f_t A,B,C,P;
point64f_t T[4],Ans;

void proc(){
    //判断P是否在线段上，如果在，总在01上
    if(isIn(P,A,B)){
        T[0]=T[3]=A,T[1]=B,T[2]=C;
    }else if(isIn(P,B,C)){
        T[0]=T[3]=B,T[1]=C,T[2]=A;
    }else if(isIn(P,C,A)){
        T[0]=T[3]=C,T[1]=A,T[2]=B;
    }else{//不在边上
        printf("-1\n");
        return;
    }

    //如果点P与T0重合
    if(isEqual(P,T[0])){
        printf("%.8lf %.8lf\n",(T[1].x+T[2].x)*0.5,(T[1].y+T[2].y)*0.5);
        return;
    }
    if(isEqual(P,T[1])){
        printf("%.8lf %.8lf\n",(T[0].x+T[2].x)*0.5,(T[0].y+T[2].y)*0.5);
        return;
    }

    //计算三角形的面积
    double area = fabs(0.5*cross(A,B,C));

    //首先计算角201
    double a01 = dist2(T[0],T[1]);
    double a02 = dist2(T[0],T[2]);
    double a12 = dist2(T[1],T[2]);
    double theta = myacos((a01+a02-a12)/(2.0*sqrt(a01)*sqrt(a02)));

    //计算P点与0点的距离
    double p0 = sqrt(dist2(P,T[0]));

    //计算三角形P02的面积
    double tmp = 0.5 * p0 * sqrt(a02) * sin(theta);
    int s = sgn(0.5*area-tmp);
    if(0==s){
        printf("%.12lf %.12lf\n",T[2].x,T[2].y);
        return;
    }else if(s>0){//说明答案在12上
        swap(T[0],T[1]);
        p0 = sqrt(dist2(P,T[0]));
    }

    //在02上寻找答案
    double t = area / ( p0 * sin(theta) );
    t = t / sqrt(a02);
    double x = T[0].x*(1-t) + T[2].x*t;
    double y = T[0].y*(1-t) + T[2].y*t;
    printf("%.12lf %.12lf\n",x,y);
}
int main(){
    //freopen("1.txt","r",stdin);
    int nofkase = getInt();
    while(nofkase--){
        A.x = getInt(), A.y = getInt();
        B.x = getInt(), B.y = getInt();
        C.x = getInt(), C.y = getInt();
        P.x = getInt(), P.y = getInt();
        proc();
    }
    return 0;
}