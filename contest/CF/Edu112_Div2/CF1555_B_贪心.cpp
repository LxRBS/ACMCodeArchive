/**
 * 给定一个大矩形区域，里面再放一个小矩形的台子。
 * 然后还有一个小矩形的桌子。所有矩形都是横平竖直的
 * 问为了把桌子放进去，台子需要移动的最小距离
 * 显然桌子顶着区域的顶点放置，台子移动的距离是最小的
 * 因此把4个点都试一边即可。
*/
#include <bits/stdc++.h>
using namespace std;

typedef double Real;

Real const EPS = 1E-8;
Real const INF = 1E100;

inline int sgn(Real x){return x < -EPS ? -1 : (x > EPS ? 1 : 0);}
inline bool isGT(Real x, Real y){return 1 == sgn(x-y);}
inline bool isEQ(Real x, Real y){return 0 == sgn(x-y);}

Real W, H;
Real X[2], Y[2];
Real w, h;
Real XD, YD;

Real f1(){
    if(sgn(X[0]-w) >= 0) return 0;
    if(sgn(Y[0]-h) >= 0) return 0;

    Real ans = INF;
    if(sgn(w + XD - W) <= 0) ans = min(ans, w - X[0]);
    if(sgn(h + YD - H) <= 0) ans = min(ans, h - Y[0]);
    return ans;
}

Real f2(){
    Real ty = H - h;
    if(sgn(X[0] - w) >= 0) return 0;
    if(sgn(ty - Y[1]) >= 0) return 0;

    Real ans = INF;
    if(sgn(w + XD - W) <= 0) ans = min(ans, w - X[0]);
    if(sgn(h + YD - H) <= 0) ans = min(ans, Y[1] - ty);
    return ans;
}

Real f3(){
    Real tx = W - w;
    if(sgn(tx - X[1]) >= 0) return 0;
    if(sgn(Y[0] - h) >= 0) return 0;

    Real ans = INF;
    if(sgn(w + XD - W) <= 0) ans = min(ans, X[1] - tx);
    if(sgn(h + YD - H) <= 0) ans = min(ans, h - Y[0]);
    return ans;
}

Real f4(){
    Real tx = W - w, ty = H - h;
    if(sgn(tx - X[1]) >= 0) return 0;
    if(sgn(ty - Y[1]) >= 0) return 0;

    Real ans = INF;
    if(sgn(w + XD - W) <= 0) ans = min(ans, X[1] - tx);
    if(sgn(h + YD - H) <= 0) ans = min(ans, Y[1] - ty);
    return ans;
}

Real proc(){
    XD = X[1] - X[0];
    YD = Y[1] - Y[0];    

    Real ans = f1();
    ans = min(ans, f2());
    ans = min(ans, f3());
    ans = min(ans, f4());
    return ans != INF ? ans : -1;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int nofkase;
    scanf("%d", &nofkase);
    while(nofkase--){
        scanf("%lf%lf%lf%lf%lf%lf%lf%lf", &W, &H, X, Y, X+1, Y+1, &w, &h);
        Real ret = proc();
        if(ret < 0) puts("-1");
        else printf("%.10lf\n", ret);
    }
    return 0;
}