/*
    给定一对直线，问位置关系
    同一平面上的两条直线的位置关系共三种：平行、重合、相交
*/
#include <iostream>

using namespace std;

double const EPS = 1E-6;
#define isZero(x) ( - EPS <= (x) && (x) <= EPS )

//射影几何结构，既是点也是直线
struct proj_t{
	double x;
	double y;
	double t;
	proj_t(double a=.0,double b=.0,double c=.0)
		:x(a),y(b),t(c){}
};
//叉积
proj_t operator * (proj_t const&l,proj_t const&r){
	proj_t ans;
	ans.x = l.y * r.t - r.y * l.t;
	ans.y = r.x * l.t - l.x * r.t;
	ans.t = l.x * r.y - r.x * l.y;
	return ans;
}
int main(){
	int n;
	scanf("%d",&n);
	printf("INTERSECTING LINES OUTPUT\n");
	while(n--){
        int x1,y1,x2,y2,x3,y3,x4,y4;
		scanf("%d%d%d%d%d%d%d%d",&x1,&y1,&x2,&y2,&x3,&y3,&x4,&y4);
        proj_t p1((double)x1,(double)y1,1.0);
		proj_t p2((double)x2,(double)y2,1.0);
		proj_t l12 = p1 * p2;
		proj_t p3((double)x3,(double)y3,1.0);
		proj_t p4((double)x4,(double)y4,1.0);
		proj_t l34 = p3 * p4;

		proj_t jiaodian = l12 * l34;
        
		if ( isZero(jiaodian.t) ){
			if( isZero(jiaodian.x) && isZero(jiaodian.y) )
				printf("LINE\n");
			else
				printf("NONE\n");
		}else{
			printf("POINT %.2lf %.2lf\n",jiaodian.x/jiaodian.t,jiaodian.y/jiaodian.t);

		}
	
	}
	printf("END OF OUTPUT\n");
	return 0;
}