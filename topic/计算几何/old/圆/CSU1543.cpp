#include <cstdio>
#include <cmath>
#include <cstring>
#include <queue>
using namespace std;

#define SIZE 9
double const INF = 1E10;
double const EPS = 1E-6;
double const PI = acos(-1.0);

inline bool is0(double x){return -EPS <= x && x <= EPS;}
inline double max(double x,double y){return x > y ? x : y;}
inline double min(double x,double y){return x < y ? x : y;}

double const R = 100.0;
struct point_t{
	double x,y;
	point_t(double a=0.0,double b=0.0):x(a),y(b){}
};
struct circle_t{
	point_t center;
	double radius;
};
double cross(point_t const&O,point_t const&A,point_t const&B){
	double xoa = A.x - O.x;
	double yoa = A.y - O.y;
	double xob = B.x - O.x;
	double yob = B.y - O.y;
	return xoa * yob - xob * yoa;
}
double dot(point_t const&O,point_t const&A,point_t const&B){
	double xoa = A.x - O.x;
	double yoa = A.y - O.y;
	double xob = B.x - O.x;
	double yob = B.y - O.y;
	return xoa * xob + yoa * yob;
}
double dist2(point_t const&A,point_t const&B){
	double x = A.x - B.x;
	double y = A.y - B.y;
	return x * x + y * y;
}
double dist(point_t const&A,point_t const&B){
	return sqrt(dist2(A,B));
}
//点O是否在线段AB上
bool isIn(point_t const&O,point_t const&A,point_t const&B){
	return is0(cross(O,A,B))
		&& O.x <= max(A.x,B.x)
		&& O.x >= min(A.x,B.x)
		&& O.y <= max(A.y,B.y)
		&& O.y >= min(A.y,B.y) ;
}
//点O到线段AB的距离
double dist(point_t const&O,point_t const&A,point_t const&B){
	if ( isIn(O,A,B) ) return 0.0;

    //计算AO·AB
	double daob = dot(A,O,B);
    if ( daob <= 0.0 ) return dist(A,O);

	//计算BO·BA
	double dboa = dot(B,O,A);
	if ( dboa <= 0.0 ) return dist(B,O);

	//计算叉积
	double area = cross(O,A,B);
	if ( area < 0.0 ) area = -area;
	return area / dist(A,B);
}
//点p是否在圆内
bool isIn(point_t const&p,circle_t const&cir){
	return dist2(p,cir.center) < cir.radius * cir.radius;
}
//线段AB是否与圆相交
bool isInter(point_t const&A,point_t const&B,circle_t const&cir){
	return dist(cir.center,A,B) < cir.radius;
}
//求指定点到圆的切点，保证点在圆外
//令切点为(X,Y)，且令x=X-x0,y=Y-y0，相当于对着圆心做一个坐标变换
//则 y = [(x0-xp)X + R^2]/(yp-y0)
//当yp==y0时，x=R^2/(xp-x0),y=±sqrt(R^2-x^2)
//不相等时则有一元二次方程为
//a: (yp-y0)^2+(x0-xp)^2
//b:2(x0-xp)·R^2
//c:R^4-(yp-y0)^2·R^2
void tagent(point_t const&p,circle_t const&cir,point_t r[]){
    double t1 = cir.center.x - p.x;//x0-xp
    double t2 = p.y - cir.center.y;//yp-y0
    double t3 = cir.radius * cir.radius;
    if ( is0(t2) ){
    	double x = t3 / -t1;
    	double y = sqrt(t3-x*x);
    	r[0].x = x + cir.center.x;
    	r[0].y = y + cir.center.y;
    	r[1].x = x + cir.center.x;
    	r[1].y = -y + cir.center.y;
    	return;
    }
    double a = t2 * t2 + t1 * t1;
    double b = 2.0 * t1 * t3;
    double c = t3 * ( t3 - t2 * t2 );
    double delta = b * b - 4.0 * a * c;
    delta = sqrt(delta);
    double x1 = ( -b + delta ) / (2.0*a);
    double y1 = ( t1 * x1 + t3 ) / t2;
    double x2 = ( -b - delta ) / (2.0*a);
    double y2 = ( t1 * x2 + t3 ) / t2;
    r[0].x = x1 + cir.center.x;
    r[0].y = y1 + cir.center.y;
    r[1].x = x2 + cir.center.x;
    r[1].y = y2 + cir.center.y;
}
//求A、B圆的切点，两圆半径相等，可能各有2个切点，也可能各有4个
int tagent(circle_t const&A,circle_t const&B,point_t ra[],point_t rb[]){
    double t1 = B.center.y - A.center.y;//yb-ya
    double t2 = A.center.x - B.center.x;//xa-xb
    double t = sqrt( t1 * t1 + t2 * t2 );
    if ( is0(t1) ){
        ra[0].x =  ra[1].x = A.center.x;
        ra[0].y = A.center.y + A.radius;
        ra[1].y = A.center.y - A.radius;
        rb[0].x = rb[1].x = B.center.x;
        rb[0].y = B.center.y + B.radius;
        rb[1].y = B.center.y - B.radius;
    }else{
        double x1 = A.radius * t1 / t;
        double y1 = t2 * x1 / t1;
        double x2 = -A.radius * t1 / t;
        double y2 = t2 * x2 / t1;
        ra[0].x = A.center.x + x1;
        ra[0].y = A.center.y + y1;
        ra[1].x = A.center.x + x2;
        ra[1].y = A.center.y + y2;

        rb[0].x = ra[0].x - t2;
        rb[0].y = ra[0].y + t1;
        rb[1].x = ra[1].x - t2;
        rb[1].y = ra[1].y + t1;
    }

    if ( dist(A.center,B.center) < A.radius + B.radius ) return 2;

    point_t mid((A.center.x+B.center.x)/2.0,(A.center.y+B.center.y)/2.0);
    tagent(mid,A,ra+2);
    rb[2].x = 2.0 * mid.x - ra[2].x;
    rb[2].y = 2.0 * mid.y - ra[2].y;
    rb[3].x = 2.0 * mid.x - ra[3].x;
    rb[3].y = 2.0 * mid.y - ra[3].y;
    return 4;
}
int N;
point_t G,Origin;
circle_t C[8];
void read(){
	scanf("%d",&N);
	scanf("%lf%lf",&G.x,&G.y);
	for(int i=0;i<N;++i){
		scanf("%lf%lf",&C[i].center.x,&C[i].center.y);
		C[i].radius = R;
	}
}
//点p是否在所有圆之外
bool isValid(point_t const&p,int idx){
	for(int i=0;i<N;++i){
		if ( i == idx ) continue;
		if ( isIn(p,C[i]) ) return false;
	}
	return true;
}
//线段AB是否在所有圆之外
bool isValid(point_t const&A,point_t const&B,int aidx,int bidx){
	for(int i=0;i<N;++i){
		if ( i == aidx || i == bidx ) continue;
		if ( isInter(A,B,C[i]) ) return false;
	}
	return true;
}

point_t P[SIZE][4*SIZE];//圆上的点
int Idx[SIZE][4*SIZE];//圆上点对应图顶点的序号
int PCnt[SIZE];//圆上点的数量
double SAngle[SIZE][SIZE],EAngle[SIZE][SIZE];//圆圆相交产生的区间段
int ICnt[SIZE];//区间数量

//给定圆上2点，求角度范围
void interCircle(double x1,double y1,double x2,double y2,int idx){
    double Atheta1 = atan2(y1-C[idx].center.y,x1-C[idx].center.x);
    double Atheta2 = atan2(y2-C[idx].center.y,x2-C[idx].center.x);
    if ( Atheta1 > Atheta2 ) swap(Atheta1,Atheta2);
    if ( Atheta2 - Atheta1 < PI ){
        SAngle[idx][ICnt[idx]] = Atheta1;
        EAngle[idx][ICnt[idx]] = Atheta2;
        ++ICnt[idx];
    }else{
    	SAngle[idx][ICnt[idx]] = -PI;
    	EAngle[idx][ICnt[idx]] = Atheta1;
    	++ICnt[idx];
    	SAngle[idx][ICnt[idx]] = Atheta2;
    	EAngle[idx][ICnt[idx]] = PI;
    	++ICnt[idx];
    }
}
//两圆相交，求交点对应的圆心角
void interCircles(int idx,int jdx){
	if ( dist(C[idx].center,C[jdx].center) > R * 2.0 ) return;

	circle_t& A = C[idx];
	circle_t& B = C[jdx];
	double t1 = B.center.y - A.center.y;
	double t2 = A.center.x - B.center.x;
	double t3 = R * R;
	double x1,x2,y1,y2;
	if ( is0(t1) ){
        x1 = x2 = ( A.center.x + B.center.x ) / 2.0;
        double y = sqrt( t3 - dist2(A.center,B.center)/4.0 );
        y1 = A.center.y + y;
        y2 = A.center.y - y;
	}else{
		double t4 = t1*t1 + t2*t2;
    	double a = 4.0 * t4;
	    double b = 4.0 * t2 * t4;
	    double c = t4 * t4 - t3 * 4.0 * t1 * t1;
	    double delta = b * b - 4.0 * a * c;
	    delta = sqrt(delta);
	    x1 = ( -b + delta ) / ( 2.0 * a );
	    x2 = ( -b - delta ) / ( 2.0 * a );
        y1 = ( t4 + 2.0 * t2 * x1 ) / ( 2.0 * t1 );
        y2 = ( t4 + 2.0 * t2 * x2 ) / ( 2.0 * t1 );;
        x1 += A.center.x;
        y1 += A.center.y;
        x2 += A.center.x;
        y2 += A.center.y;
	}

    interCircle(x1,y1,x2,y2,idx);
    interCircle(x1,y1,x2,y2,jdx);
}
void interCircles(){
	memset(ICnt,0,sizeof(ICnt));
	for(int i=0;i<N-1;++i)for(int j=i+1;j<N;++j)
		interCircles(i,j);
}

struct edge_t{
	int u;
	double w;
	edge_t* next;
}Edge[20000];
int ECnt = 0;
edge_t* Ver[300];
int VCnt = 0;

void mkEdge(int a,int b,double w){
    Edge[ECnt].u = b;
    Edge[ECnt].w = w;
    Edge[ECnt].next = Ver[a];
    Ver[a] = Edge + ECnt++;

    Edge[ECnt].u = a;
    Edge[ECnt].w = w;
    Edge[ECnt].next = Ver[b];
    Ver[b] = Edge + ECnt++;
}
//判断圆idx上的两个角度是否合法
int calcValid(double theta1,double theta2,int idx){
	int ans = 0;
    for(int i=0;i<ICnt[idx];++i){
    	if ( ( SAngle[idx][i] <= theta1 && theta1 <= EAngle[idx][i] )
    		|| ( SAngle[idx][i] <= theta2 && theta2 <= EAngle[idx][i] ) )
    		return 3;//都不可用
    	if ( ( theta1 <= SAngle[idx][i] && SAngle[idx][i] <= theta2 )
    		|| ( theta1 <= EAngle[idx][i] && EAngle[idx][i] <= theta2 ) )
    		ans |= 1;
    	if ( SAngle[idx][i] >= theta2 || SAngle[idx][i] <= theta1
    		|| EAngle[idx][i] >= theta2 || EAngle[idx][i] <= theta1 )
    		ans |= 2;
    	if ( 3 == ans ) return ans;
    }
    return ans;//为1表示从小到大不可用，为2表示从大到小不可用,为0表示都可用
}
void mkEdge4Circle(int idx){
	int n = PCnt[idx];
	double theta[4*SIZE];
	double xo = C[idx].center.x;
	double yo = C[idx].center.y;
    for(int i=0;i<n;++i){
    	double x = P[idx][i].x;
    	double y = P[idx][i].y;
    	theta[i] = atan2(y-yo,x-xo);
    }
    for(int i=0;i<n-1;++i)for(int j=i+1;j<n;++j){
    	double t1 = theta[i],t2 = theta[j];
    	if ( t1 > t2 ) swap(t1,t2);
    	int ans = calcValid(t1,t2,idx);
    	if ( 3 == ans ) continue;
        double w = INF;
        if ( 1 != ans ){//从小到大可用
           w = R * ( t2 - t1 );
        }
        if ( 2 != ans ){//从大到小可用
        	double w1 = R * ( 2.0*PI-t2+t1 );
        	if ( w1 < w ) w = w1;
        }
        mkEdge(Idx[idx][i],Idx[idx][j],w);
    }
}
void mkGraph(){
	ECnt = 0;
	VCnt = 2;
	memset(Ver,0,sizeof(Ver));
	memset(PCnt,0,sizeof(PCnt));
	memset(Idx,0,sizeof(Idx));

    for(int i=0;i<N-1;++i){
    	point_t ra[4],rb[4];
        for(int j=i+1;j<N;++j){
            int kk = tagent(C[i],C[j],ra,rb);
            for(int k=0;k<kk;++k){
            	if ( isValid(ra[k],rb[k],i,j) ){
                    P[i][PCnt[i]] = ra[k];
                    P[j][PCnt[j]] = rb[k];
                    Idx[i][PCnt[i]] = VCnt++;
                    Idx[j][PCnt[j]] = VCnt++;
                    mkEdge(Idx[i][PCnt[i]],Idx[j][PCnt[j]],dist(ra[k],rb[k]));
                    ++PCnt[i];
                    ++PCnt[j];
            	}
            }
        }
    }

    //起点到每个圆
    for(int i=0;i<N;++i){
    	point_t r[2];
        tagent(Origin,C[i],r);
        for(int k=0;k<2;++k){
        	if ( isValid(Origin,r[k],-1,i) ){
                P[i][PCnt[i]] = r[k];
                Idx[i][PCnt[i]] = VCnt++;
                mkEdge(0,Idx[i][PCnt[i]],dist(Origin,r[k]));
                ++PCnt[i];
        	}
        }
    }
    //终点到每个圆
    for(int i=0;i<N;++i){
    	point_t r[2];
    	tagent(G,C[i],r);
    	for(int k=0;k<2;++k){
    		if ( isValid(G,r[k],-1,i) ){
                P[i][PCnt[i]] = r[k];
                Idx[i][PCnt[i]] = VCnt++;
                mkEdge(1,Idx[i][PCnt[i]],dist(G,r[k]));
                ++PCnt[i];
    		}
    	}
    }

    interCircles();
    //每个圆内部的切点连边
    for(int i=0;i<N;++i)mkEdge4Circle(i);
}

bool F[1200];
double D[1200];
int Path[1200];
void spfa(int s){
	memset(Path,-1,sizeof(Path));
    memset(F,0,sizeof(F));
    for(int i=0;i<VCnt;++i) D[i] = INF;

    D[s] = 0.0;
    F[s] = true;
    Path[s] = s;

    queue<int> q;
    q.push(s);

    while( !q.empty() ){
    	int u = q.front();
    	q.pop();
    	F[u] = false;

    	for(edge_t*p=Ver[u];p;p=p->next){
    		int v = p->u;
    		double t = D[u] + p->w;
    		if ( t < D[v] ){
    			D[v] = t;
    			Path[v]=u;
    			if ( !F[v] )q.push(v),F[v] = true;
    		}
    	}
    }
}

int main() {
	read();
	if ( !isValid(Origin,-1) || !isValid(G,-1) ){
		printf("0.0\n");
		return 0;
	}
    if ( isValid(Origin,G,-1,-1) ){
    	printf("%.5lf\n",dist(Origin,G));
    	return 0;
    }
	mkGraph();
    spfa(0);
    if ( is0(D[1]-INF) ) printf("0.0\n");
    else printf("%.5lf\n",D[1]);
	return 0;
}
