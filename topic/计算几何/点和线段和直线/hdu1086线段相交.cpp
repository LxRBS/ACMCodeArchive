//简单题，求线段的交点的个数
#include <iostream>
using namespace std;

double const EPS = 1E-9;

#define is0(x) ( -EPS <= (x) && (x) <= EPS )
#define MAX(x,y) ( (x) >= (y) ? (x) : (y) )
#define MIN(x,y) ( (x) <= (y) ? (x) : (y) )

struct point64f_t{
	double x;
	double y;
};

struct lineseg_t{
	point64f_t s;
	point64f_t e;
};

double cross(point64f_t const&O,point64f_t const&A,point64f_t const&B){
	double xoa = A.x - O.x;
	double yoa = A.y - O.y;
	double xob = B.x - O.x;
	double yob = B.y - O.y;
	return xoa * yob - xob * yoa;
}

bool isInter(lineseg_t const&AB,lineseg_t const&CD){
	point64f_t const&A = AB.s;
	point64f_t const&B = AB.e;
	point64f_t const&C = CD.s;
	point64f_t const&D = CD.e;
    return MAX(A.x,B.x) >= MIN(C.x,D.x)
		&& MAX(A.y,B.y) >= MIN(C.y,D.y)
		&& MAX(C.x,D.x) >= MIN(A.x,B.x)
		&& MAX(C.y,D.y) >= MIN(A.y,B.y)
		&& cross(A,D,B) * cross(A,B,C) >= -EPS
		&& cross(C,A,D) * cross(C,D,B) >= -EPS;
}
lineseg_t ls[103];
int main(){
	int n;
	while( scanf("%d",&n) && n ){
        for(int i=0;i<n;++i)scanf("%lf%lf%lf%lf",&ls[i].s.x,&ls[i].s.y,&ls[i].e.x,&ls[i].e.y);
		int ans = 0;
		for(int i=0;i<n-1;++i)for(int j=i+1;j<n;++j)if(isInter(ls[i],ls[j]))
			++ans;
		printf("%d\n",ans);
	}
	return 0;
}