#include<bits/stdc++.h>
using namespace std;
const long double eps = 1e-8;
struct Point{
	long double x,y;
	void read() {
		scanf("%Lf%Lf",&x,&y);
	}
	Point () {}
	Point (long double a1,long double a2) : x(a1),y(a2) {}
	Point (int a1,int a2) : x(a1),y(a2) {}
	friend Point operator + (Point p1,Point p2){return Point(p1.x+p2.x,p1.y+p2.y);} 
	friend Point operator - (Point p1,Point p2){return Point(p1.x-p2.x,p1.y-p2.y);} 
	friend Point operator * (Point p1,long double t){return Point(p1.x*t,p1.y*t);} 
	friend Point operator / (Point p1,long double k){return Point(p1.x/k,p1.y/k);}
	friend bool operator < (Point p1,Point p2){return (abs(p1.x-p2.x)<=eps)?p1.y<p2.y:p1.x<p2.x;}
	friend bool operator == (Point p1,Point p2){return (abs(p1.x-p2.x)<=eps && abs(p1.y-p2.y)<=eps);}
	Point trans(long double newlen)	{	
		long double len=mo(); 
		long double xx=x/len*newlen,yy=y/len*newlen; 
		return Point(xx,yy);
	}
    
	inline Point rotate(long double sinfi,long double cosfi){
        return Point(x*cosfi-y*sinfi,y*cosfi+x*sinfi);
    }
	inline Point rotate(long double fi){
        long double sinfi=sin(fi),cosfi=cos(fi); 
        return Point(x*cosfi-y*sinfi,y*cosfi+x*sinfi);
    }
    inline Point rotate90(){
        return Point(-y,x);
    }
	long double mo(){return sqrt(x*x+y*y);}
	long double getAngle() {return atan2(y,x);}
}; 
long double mulcross(Point v1,Point v2){return (v1.x*v2.y-v1.y*v2.x);}

struct Line{
	Point p,u;
	long double ang;
	Line () {}
	Line (Point a1,Point a2) : p(a1),u(a2) {}
	bool judgeHalfPlane(Point p0) {return mulcross(u,p0-p)>=-eps;}
	friend bool operator < (Line l1,Line l2) {return l1.p<l2.p;}
	void setAngle() {ang = u.getAngle();}
}dline,uline,lline,rline;
Point inters(Line l1,Line l2){return l1.p+l1.u*(mulcross(l2.p-l1.p,l2.u)/mulcross(l1.u,l2.u));}

struct threePoint{
	long double x,y,z;
	threePoint (long double a1=0,long double a2=0,long double a3=0) : x(a1),y(a2),z(a3) {}
	void read() {scanf("%Lf%Lf%Lf",&x,&y,&z);}
	Point project() {return Point(x,y);}
	Point getShadow(threePoint light) {
		if (z==0) return this->project();
		Point u = this->project() - light.project();
		if (abs(u.x)<eps && abs(u.y)<eps) return this->project();
		if (z<light.z) {
			u=u.trans(u.mo()+z*u.mo()/(light.z-z));
			return u+light.project();
		}else{
			throw "point not found";
		}
		throw "point not found";
	}
};
bool cmp(Line l1,Line l2){return ((abs(l1.ang-l2.ang)<eps)?(mulcross(l1.p-l2.p,l2.u)<0):l1.ang<l2.ang);}
int nxt(int i,int l,int r){return i==r?l:i+1;}

vector<Point> halfPlaneIntersection(vector<Line> lineList) {
	for (int i=1;i<(int)lineList.size();i++) lineList[i].setAngle();
	sort(lineList.begin()+1,lineList.end(),cmp);
	const int thisSize = 200005+5;
	static Line que[thisSize];
	static Point forw[thisSize],bacw[thisSize];
	int l=1,r=1;
	que[1]=lineList[1];

    vector<Point> convexGenerateByHalfPlane;
	for (int i=2;i<(int)lineList.size();i++) {
		if (lineList[i].ang-lineList[i-1].ang<=eps) continue;
		while (r-l+1>=2 && mulcross(forw[r]-lineList[i].p,lineList[i].u)>=0) r--;
		while (r-l+1>=2 && mulcross(bacw[l]-lineList[i].p,lineList[i].u)>=0) l++;
		que[++r]=lineList[i];
		if (abs(mulcross(que[r].u,que[r-1].u))<=eps) return convexGenerateByHalfPlane;
		forw[r]=bacw[r-1]=inters(que[r],que[r-1]);
	}
	while (r-l+1>=2 && mulcross(forw[r]-que[l].p,que[l].u)>=0) r--;
	if (abs(mulcross(que[l].u,que[r].u))<=eps) return convexGenerateByHalfPlane;
	forw[l]=inters(que[l],que[r]);
	
	for (int i=l;i<=r;i++) {
        convexGenerateByHalfPlane.push_back(forw[i]);
	}

    return convexGenerateByHalfPlane;
}

long double getarea(vector<Point> convex) {
	long double ans=0;
	Point O(0,0);
	int len = convex.size();
	for (int i=0;i<len;i++) {
		ans+=mulcross(convex[i]-O,convex[(i+1)%len]-O)/2.0;
	}
	return ans;
}
struct Wall{
    int n,height;
    long double width;
    vector<Point> pointList;
	void read() {
        scanf("%d%d%Lf",&n,&height,&width);
        for (int i=1;i<=n;i++) {
            Point tmpPoint;
            tmpPoint.read();
            pointList.push_back(tmpPoint);
        }
	}
    vector<Line> lineList;
	void init() {
		Line line;
		lineList.push_back(line);
	}
    void shrink() {
        int len = pointList.size();
        for (int i=0;i<len;i++) {
            Point u = pointList[(i+1)%len] - pointList[i];
            lineList.push_back(Line(pointList[i]+u.rotate90().trans(width),u));
        }
        vector<Point> convex = halfPlaneIntersection(lineList);
        if (convex.size()<3) throw (long double)0;
        pointList = convex;
    }
    void isin(threePoint light) {
        int len = pointList.size();
  		for (int i=0;i<len;i++) {
            Point u = pointList[(i+1)%len] - pointList[i];
  			if (mulcross(u,light.project()-pointList[i])<0) return;
		}
		throw getarea(pointList);
    }
    void getShadow(threePoint light) {
    	if (light.z<=height) throw (long double)0;
        int len = pointList.size();
        vector<Point> anotherConvex;
        for (int i=0;i<len;i++) {
            threePoint point(pointList[i].x,pointList[i].y,height);
            Point projection = point.getShadow(light);
            anotherConvex.push_back(projection);
        }
        len = anotherConvex.size();
        for (int i=0;i<len;i++) {
            Point u = anotherConvex[(i+1)%len] - anotherConvex[i];
            lineList.push_back(Line(anotherConvex[i],u));
        }
        vector<Point> convex = halfPlaneIntersection(lineList);
        if (convex.size()<3) throw (long double)0;
        throw getarea(convex);
    }
};

void solve() 
{
    try{
        Wall wall;
        wall.read();
        threePoint light;
        light.read();
        wall.init();
        wall.shrink();
        wall.isin(light);
        wall.getShadow(light);        
    }catch(long double ans) {
        printf("%.10Lf\n",ans);
    }
}

int main()
{
	int t;
	scanf("%d",&t);
	while (t--) solve();
}
