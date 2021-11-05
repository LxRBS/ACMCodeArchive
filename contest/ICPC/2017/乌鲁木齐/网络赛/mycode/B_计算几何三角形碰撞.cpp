/*
    2个三角形分别以各自的速度前进，问是否相撞
    以其中一个三角形为参照系，看另外一个三角形的运动轨迹是否与之相交
    再交换2个三角形的角色，再算一遍
    但是不能使用longlong，要使用double
*/
#include <stdio.h>
#include <iostream>
#include <algorithm>
using namespace std;

typedef double llt;
llt const MAX = 1E9+1;

struct Point{
    llt x,y;
    Point(llt a=0LL,llt b=0LL):x(a),y(b){}
};

llt cross(Point const&O,Point const&A,Point const&B){
    llt xoa = A.x - O.x;
    llt xob = B.x - O.x;
    llt yoa = A.y - O.y;
    llt yob = B.y - O.y;
    return xoa * yob - xob * yoa;
}

bool isInter(Point const&A,Point const&B,Point const&C,Point const&D){
    return min(A.x,B.x) <= max(C.x,D.x)
        && min(A.y,B.y) <= max(C.y,D.y)
        && min(C.x,D.x) <= max(A.x,B.x)
        && min(C.y,D.y) <= max(A.y,B.y)
        && cross(A,C,B) * cross(A,B,D) >= 0LL
        && cross(C,B,D) * cross(C,D,A) >= 0LL;
}

//p为定点，求出射线方向的最远点
Point mkLimit(Point const p,llt const speed[]){
    if ( 0LL == speed[0] && 0LL == speed[1] ) return p;
    if ( 0LL == speed[0] ) return Point(p.x,speed[1]>0?MAX:-MAX);
    if ( 0LL == speed[1] ) return Point(speed[0]>0?MAX:-MAX,p.y);

    llt kx,ky;
    if ( speed[0] > 0 ){
        kx = ( MAX - p.x ) / speed[0] + 1LL;
    }else{
        kx = ( -MAX - p.x ) / speed[0] + 1LL;
    }

    if ( speed[1] > 0  ){
        ky = ( MAX - p.y ) / speed[1] + 1LL;
    }else{
        ky = ( -MAX - p.y ) / speed[1] + 1LL;
    }

    if ( kx > ky ) kx = ky;
    return Point(p.x+kx*speed[0],p.y+kx*speed[1]);
}

Point A[3],B[3];
llt SpeedA[2],SpeedB[2];

//a静止不动，b以speed速度运动，相撞返回true
bool f(Point const a[],Point const b[],llt const speed[]){
    for(int i=0;i<3;++i){
        Point inf = mkLimit(b[i],speed);
        if ( isInter(b[i],inf,a[0],a[1])
            || isInter(b[i],inf,a[1],a[2])
            || isInter(b[i],inf,a[2],a[0]) ) return true;
    }
}

inline bool f(Point const a[],Point const b[],llt const speeda[],llt const speedb[]){
    llt speed[] = {speeda[0]-speedb[0],speeda[1]-speedb[1]};
    if ( f(b,a,speed) ) return true;
    speed[0] = -speed[0], speed[1] = -speed[1];
    return f(a,b,speed);
}

int main(){
    //freopen("1.txt","r",stdin);
    int nofkase;
    scanf("%d",&nofkase);
    for(int kase=1;kase<=nofkase;++kase){
        //scanf("%lld%lld%lld%lld%lld%lld%lld%lld",&A[0].x,&A[0].y,&A[1].x,&A[1].y,&A[2].x,&A[2].y,SpeedA,SpeedA+1);
        //scanf("%lld%lld%lld%lld%lld%lld%lld%lld",&B[0].x,&B[0].y,&B[1].x,&B[1].y,&B[2].x,&B[2].y,SpeedB,SpeedB+1);
        cin>>A[0].x>>A[0].y>>A[1].x>>A[1].y>>A[2].x>>A[2].y>>SpeedA[0]>>SpeedA[1];
        cin>>B[0].x>>B[0].y>>B[1].x>>B[1].y>>B[2].x>>B[2].y>>SpeedB[0]>>SpeedB[1];
        printf("Case #%d: ",kase);
        printf(f(A,B,SpeedA,SpeedB)?"YES\n":"NO\n");
    }
    return 0;
}
