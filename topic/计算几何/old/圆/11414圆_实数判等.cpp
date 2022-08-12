#include <cstdio>
#include <cmath>
double const EPS = 1E-6;
double const PI = acos(-1.0);

inline bool is0(double x){return -EPS <= x && x <= EPS;}
inline bool isEQ(double x,double y){return is0(x-y);}
inline bool isGT(double x,double y){return x - y > EPS;}
inline bool isGE(double x,double y){return isGT(x,y)||isEQ(x,y);}
inline bool isLT(double x,double y){return !isGE(x,y);}
inline bool isLE(double x,double y){return !isGT(x,y);}

struct Point{
	double x;
	double y;
	Point(double xx=0.0,double yy=0.0):x(xx),y(yy){}
}P[30];

struct Circle{
	Point center;
	double radius;
}C[2];

inline double dist2(Point const&p1,Point const&p2){
	double x = p1.x - p2.x;
	double y = p1.y - p2.y;
	return x * x + y * y;
}

inline double dist(Point const&p1,Point const&p2){
	double x = p1.x - p2.x;
	double y = p1.y - p2.y;
	return sqrt( x * x + y * y );
}

inline double isIn(Point const&p,Circle const&c){
	return isLE(dist(p,c.center),c.radius);
}

inline double calAngle(Point const&p1,Point const&p2){
    double x = p1.x - p2.x;
    double y = p1.y - p2.y;
    return atan2(y,x) + PI / 2.0;
}

int N;
double R;
int main() {
	int nofkase;
	scanf("%d",&nofkase);
	while(nofkase--){
        scanf("%lf%d",&R,&N);
        for(int i=0;i<N;++i)scanf("%lf%lf",&P[i].x,&P[i].y);

        if ( N <= 1 ){
        	printf("%d\n",N);
        	continue;
        }

        if ( 2 == N ){
        	printf(isLE(dist(P[0],P[1]),R*2.0)?"2\n":"1\n");
        	continue;
        }


        C[0].radius = C[1].radius = R;

        int ans = 0;
        for(int i=0;i<N;++i){
        	C->center = P[i];
        	int t = 0;
        	for(int j=0;j<N;++j){
        		if ( isIn(P[j],*C) ) ++t;
        	}
        	if ( t > ans ) ans = t;
        }

        for(int i=0;i<N-1;++i)for(int j=i+1;j<N;++j){
        	if ( isGT(dist(P[i],P[j]),R*2.0) ) continue;
        	if ( isEQ(P[i].x,P[j].x) && isEQ(P[i].y,P[j].y) ) continue;

            Point mid((P[i].x+P[j].x)/2.0,(P[i].y+P[j].y)/2.0);
            double theta = calAngle(P[i],P[j]);
            double dt = R*R-dist2(P[i],P[j])/4.0;
            double r = (dt>0)?sqrt(dt):0.0;
            C[0].center.x = mid.x + r * cos(theta);
            C[0].center.y = mid.y + r * sin(theta);
            C[1].center.x = mid.x - r * cos(theta);
            C[1].center.y = mid.y - r * sin(theta);

            int t1 = 0, t2 = 0;
            for(int k=0;k<N;++k){
            	if ( isIn(P[k],C[0]) ) ++ t1;
            	if ( isIn(P[k],C[1]) ) ++ t2;
            }
            int t = t1 > t2 ? t1 : t2;
            if ( t > ans ) ans = t;
        }
        printf("%d\n",ans);
	}
	return 0;
}
