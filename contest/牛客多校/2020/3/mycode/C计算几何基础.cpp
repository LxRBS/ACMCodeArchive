#include <bits/stdc++.h>
using namespace std;
 
double const EPS = 0.5;
inline bool is0(double x){return -EPS < x && x < EPS;}
inline bool isEq(double x,double y){return is0(x-y);}
 
struct point64f_t{
    double x,y;
};
 
double dist2(const point64f_t&a,const point64f_t&b){
    double x = a.x - b.x;
    double y = a.y - b.y;
    return x*x+y*y;
}
 
double dist(const point64f_t&a,const point64f_t&b){
    double x = a.x - b.x;
    double y = a.y - b.y;
    return sqrt(x*x+y*y);
}
 
double dot(const point64f_t&O,const point64f_t&A,const point64f_t&B){
    double xoa = A.x - O.x;
    double yoa = A.y - O.y;
    double xob = B.x - O.x;
    double yob = B.y - O.y;
    return xoa * xob + yoa * yob;
}
 
double cross(const point64f_t&O,const point64f_t&A,const point64f_t&B){
    double xoa = A.x - O.x;
    double yoa = A.y - O.y;
    double xob = B.x - O.x;
    double yob = B.y - O.y;
    return xoa*yob - xob*yoa;
}
 
point64f_t P[21];
double D[21];
 
bool f(){//左手返回true，右手返回false
    int st1 = 0;
    //先找最大的
    int emaxi = max_element(D,D+20)-D;
    int e_next = emaxi + 1;
    if (e_next == 20) e_next = 0;
    int ej = e_next + 1;
    if(ej==20) ej = 0;
 
    //看看下一个是8还是5
    if(isEq(D[e_next],64.)){//9后面跟8，如果还是逆时针就是右手
        double tmp = cross(P[emaxi],P[e_next],P[ej]);
        return tmp < 0;
    }
    if(isEq(D[e_next],36.)){
        double tmp = cross(P[emaxi],P[e_next],P[ej]);
        return tmp > 0;
    }
 
    //不应该到这
    throw runtime_error("should not here");
    return true;
}
 
int main(){
    //freopen("1.txt","r",stdin);
    int nofkase;
    scanf("%d",&nofkase);
    while(nofkase--){
        for(int i=0;i<20;++i){
            scanf("%lf%lf",&P[i].x,&P[i].y);
        }
        P[20] = P[0];
 
        for(int i=0;i<20;++i) D[i] = dist2(P[i],P[i+1]);
 
        puts(f()?"left":"right");
    }
    return 0;