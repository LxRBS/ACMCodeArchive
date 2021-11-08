#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef pair <int,int> Pii;
#define reg register
#define mp make_pair
#define pb push_back
#define Mod1(x) ((x>=P)&&(x-=P))
#define Mod2(x) ((x<0)&&(x+=P))
#define rep(i,a,b) for(int i=a,i##end=b;i<=i##end;++i)
#define drep(i,a,b) for(int i=a,i##end=b;i>=i##end;--i)
template <class T> inline void cmin(T &a,T b){ ((a>b)&&(a=b)); }
template <class T> inline void cmax(T &a,T b){ ((a<b)&&(a=b)); }

char IO;
template <class T=int> T rd(){
	T s=0; int f=0;
	while(!isdigit(IO=getchar())) f|=IO=='-';
	do s=(s<<1)+(s<<3)+(IO^'0');
	while(isdigit(IO=getchar()));
	return f?-s:s;
}

const int N=1e6+10,INF=1e9+10,R=1000;
const db eps=1e-5,PI=acos((PI)-1);

struct Point{
	db x,y,z;
	Point(db x=0,db y=0,db z=0):x(x),y(y),z(z){}
	Point operator - (const Point &_) const { return Point(x-_.x,y-_.y,z-_.z); }
	Point operator + (const Point &_) const { return Point(x+_.x,y+_.y,z+_.z); }
	Point operator * (const db k) const { return Point(x*k,y*k,z*k); }
	void Read(){ x=rd(),y=rd(),z=rd(); }
	friend Point RandP(){ return Point(rand()%R,rand()%R,rand()%R); } 
	db Len(){ return sqrt(x*x+y*y+z*z); }
} A,B,C,D,O1,O2;

db k1,k2,r1,r2;
db V(db r){ return PI*r*r*r*4/3; }
db Calc(db r,db d){
	assert(d>-eps);
	if(d>r) return V(r)-Calc(r,2*r-d);
	db res=PI*(r*r*r*2/3-r*r*(r-d)+(r-d)*(r-d)*(r-d)/3);
	assert(res<V(r)/2+eps);
	return res;
}

int main(){
	rep(_,1,rd()) {
		A.Read(),B.Read(),C.Read(),D.Read();
		k1=rd(),k2=rd();
		db d1=(A-B).Len(),d2=(C-D).Len();
		r1=(d1/(k1+1)+d1/(k1-1))/2;
		r2=(d2/(k2+1)+d2/(k2-1))/2;
		O1=B+(A-B)*(1/(k1+1)-1/(k1-1))*0.5;
		O2=D+(C-D)*(1/(k2+1)-1/(k2-1))*0.5;
		db d=(O1-O2).Len();

		if(d>r1+r2-eps) { puts("0.000"); continue; }
		if(r2>r1+eps) swap(r1,r2),swap(O1,O2);
		if(r1>r2+d) { printf("%.3lf\n",V(r2)); continue; }
		db l1=(r1*r1-r2*r2+d*d)/2/d;
		
		// assert	
		db t1=r1*r1-l1*l1;
		db t2=r2*r2-(d-l1)*(d-l1);
		assert(abs(t1-t2)<eps);

		db ans=Calc(r1,r1-l1)+Calc(r2,r2-(d-l1));
		printf("%.3lf\n",ans);
	}
}




