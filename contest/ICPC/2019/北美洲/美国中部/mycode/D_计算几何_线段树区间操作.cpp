/**
   二维平面有一些固定的圆。
   还有一个圆盘（半径为b）从原点出发，等概率的选择一个方向前进d
   问不与固定圆发生碰撞的概率是多少

   首先将固定圆的半径增加b，然后计算出每个圆不允许的范围
   当然明显没用的固定圆要去掉

   然后再用线段树做一个区间操作。
   查询没有被刷过的区间即可
*/
#include <bits/stdc++.h>
using namespace std;

double const EPS = 1E-10;
double const PI = acos(-1.0);

inline int sgn(double x){return x>EPS?1:(x<-EPS?-1:0);}
inline bool is0(double x){return sgn(x)==0;}
inline bool isEq(double x,double y){return is0(x-y);}

inline double myasin(double x){
    if(x>1) x = 1.0;
    if(x<-1) x = -1.0;
    return asin(x);
}

inline double myacos(double x){
    if(x>1) x = 1.0;
    if(x<-1) x = -1.0;
    return acos(x);
}

int getInt(){
	int sgn = 1;
	char ch = getchar();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = getchar();
	if ( '-' == ch ) {sgn = 0;ch=getchar();}

	int ret = (int)(ch-'0');
	while( '0' <= (ch=getchar()) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return sgn ? ret : -ret;
}

inline int lson(int t){return t<<1;}
inline int rson(int t){return lson(t)|1;}

int St[570000];
int Lazy[570000];

inline void _pushUp(int t){
    St[t] = St[lson(t)] + St[rson(t)];
}

inline void _pushDown(int t,int s,int e){
    if(0==Lazy[t]) return;

    int mid = (s+e)>>1;
    St[lson(t)] = mid - s + 1;
    St[rson(t)] = e - mid;
    Lazy[lson(t)] = 1;
    Lazy[rson(t)] = 1;
    Lazy[t] = 0;
}

//查询[a,b]区间的和
int query(int t,int s,int e,int a,int b){
    if(a<=s&&e<=b){
        return St[t];
    }

    _pushDown(t,s,e);
    int mid = (s+e) >> 1;
    int ans = 0;
    if(a<=mid) ans += query(lson(t),s,mid,a,b);
    if(mid<b) ans += query(rson(t),mid+1,e,a,b);
    return ans;
}

//把[a,b]全改成1
void modify(int t,int s,int e,int a,int b){
    if(a<=s&&e<=b){
        St[t] = e - s + 1;
        Lazy[t] = 1;
        return;
    }

    _pushDown(t,s,e);
    int mid = (s+e) >> 1;
    if(a<=mid) modify(lson(t),s,mid,a,b);
    if(mid<b) modify(rson(t),mid+1,e,a,b);
    _pushUp(t);
}

int N;
double X[10010],Y[10010],R[10010];
double D,B;
vector<int> Vec;
double Yuanxinjiao[10010], Juli2[10010];
double Angles[10010][4];
int AngleCnt[10010] = {0};
double Thetas[140040];
int ThetaCnt = 0;

//对每个圆计算不允许的角度
void f(int idx){
    Yuanxinjiao[idx] = atan2(Y[idx],X[idx]);
    Juli2[idx] = X[idx]*X[idx]+Y[idx]*Y[idx];

    double theta;
    if(sgn(D-sqrt(Juli2[idx]-R[idx]*R[idx]))>=0){//计算切线角度
        theta = myasin(R[idx]/sqrt(Juli2[idx]));
    }else{
        theta = myacos((D*D+Juli2[idx]-R[idx]*R[idx])/(2.0*D*sqrt(Juli2[idx])));
    }

    double a1 = Yuanxinjiao[idx] - theta;
    double a2 = Yuanxinjiao[idx] + theta;

    if(sgn(-PI-a1)<=0&&sgn(a2-PI)<=0){
        AngleCnt[idx] = 2;
        Thetas[ThetaCnt++] = Angles[idx][0] = a1;
        Thetas[ThetaCnt++] = Angles[idx][1] = a2;
        Thetas[ThetaCnt++] = a1 - EPS*2.0;
        Thetas[ThetaCnt++] = a1 + EPS*2.0;
        Thetas[ThetaCnt++] = a2 - EPS*2.0;
        Thetas[ThetaCnt++] = a2 + EPS*2.0;
    }else if(sgn(-PI-a1)>0){
        AngleCnt[idx] = 4;
        Thetas[ThetaCnt++] = Angles[idx][0] = -PI;
        Thetas[ThetaCnt++] = Angles[idx][1] = a2;
        Thetas[ThetaCnt++] = Angles[idx][2] = a1 + PI + PI;
        Thetas[ThetaCnt++] = Angles[idx][3] = PI;
        Thetas[ThetaCnt++] = a2 - EPS*2.0;
        Thetas[ThetaCnt++] = a2 + EPS*2.0;
        Thetas[ThetaCnt++] = a1 + PI + PI - EPS*2.0;
        Thetas[ThetaCnt++] = a1 + PI + PI + EPS*2.0;
    }else if(sgn(a2-PI)>0){
        AngleCnt[idx] = 4;
        Thetas[ThetaCnt++] = Angles[idx][0] = a1;
        Thetas[ThetaCnt++] = Angles[idx][1] = PI;
        Thetas[ThetaCnt++] = Angles[idx][2] = -PI;
        Thetas[ThetaCnt++] = Angles[idx][3] = a2 - PI - PI;
        Thetas[ThetaCnt++] = a1 - EPS*2.0;
        Thetas[ThetaCnt++] = a1 + EPS*2.0;
        Thetas[ThetaCnt++] = a2 - PI - PI - EPS*2.0;
        Thetas[ThetaCnt++] = a2 - PI - PI + EPS*2.0;
    }else{
        throw runtime_error("XXXXXXXX");
    }
}

int main(){
    //freopen("1.txt","r",stdin);
    ///输入
    N = getInt();
    for(int i=1;i<=N;++i){
        X[i] = getInt();
        Y[i] = getInt();
        R[i] = getInt();
    }
    B = getInt(); D = getInt();
    for(int i=1;i<=N;++i){
        R[i] += B;
    }
    ///去掉明显够不着的圆
    Vec.reserve(N);
    for(int i=1;i<=N;++i){
        double d = sqrt(X[i]*X[i]+Y[i]*Y[i]);
        d -= R[i] + D;
        if(sgn(d)<0) Vec.push_back(i);
    }
    ///对每个圆计算不允许的角度，角度从-180到180
    for(auto i: Vec)f(i);

    ///离散化
    Thetas[ThetaCnt++] = -PI;
    Thetas[ThetaCnt++] = PI;
    sort(Thetas,Thetas+ThetaCnt);
    int n = unique(Thetas,Thetas+ThetaCnt,isEq) - Thetas;

    ///区间操作，线段树
    for(auto i: Vec){
        int a = lower_bound(Thetas,Thetas+n,Angles[i][0]) - Thetas + 1;
        int b = lower_bound(Thetas,Thetas+n,Angles[i][1]) - Thetas + 1;
        modify(1,1,n,a,b);
        if(AngleCnt[i]==4){
            a = lower_bound(Thetas,Thetas+n,Angles[i][2]) - Thetas + 1;
            b = lower_bound(Thetas,Thetas+n,Angles[i][3]) - Thetas + 1;
            modify(1,1,n,a,b);
        }
    }

    ///检查线段树中为0的区间范围
    double ans = 0.0;
    int i = 1;
    int ret;
    while(i<=n){
        int k = 0;
        while(i+k<=n&&query(1,1,n,i,i+k)==k+1)++k;
        if(i+k>n) break;

        i += k;
        k = 0;
        while(i+k<=n&&query(1,1,n,i,i+k)==0)++k;

        if(i+k>n){
            --k;
            ans += Thetas[i+k-1] - Thetas[i-1];
            break;
        }else{
            ans += Thetas[i+k-1] - Thetas[i-1];
            i += k;
        }

    }

    printf("%.12f\n",ans/(PI+PI));
    return 0;
}
