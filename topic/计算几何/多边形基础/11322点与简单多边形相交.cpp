//点与简单多边形相交
#include <cstdio>
#include <cmath>
typedef int llt;

#define MAX(x,y) ( (x) > (y) ? (x) : (y) )
#define MIN(x,y) ( (x) < (y) ? (x) : (y) )

#define SIZE 101

struct point_t{
	llt x,y;
	point_t(llt a=0,llt b=0):x(a),y(b){}
}P[101];

//叉积，OA×OB
llt cross(point_t const&O,point_t const&A,point_t const&B){
	llt xoa = A.x - O.x;
	llt yoa = A.y - O.y;
	llt xob = B.x - O.x;
	llt yob = B.y - O.y;
	return xoa * yob - xob * yoa;
}

//点O是否在线段AB上
bool isInter(point_t const&O,point_t const&A,point_t const&B){
	return 0 == cross(O,A,B)
		&& O.x <= MAX(A.x,B.x) 
		&& O.x >= MIN(A.x,B.x)
		&& O.y <= MAX(A.y,B.y)
		&& O.y >= MIN(A.y,B.y) ;
}

//判断线段AB是否与线段CD相交
bool isInter(point_t const&A,point_t const&B,point_t const&C,point_t const&D){
	return MIN(A.x,B.x) <= MAX(C.x,D.x)
		&& MIN(A.y,B.y) <= MAX(C.y,D.y)
		&& MIN(C.x,D.x) <= MAX(A.x,B.x)
		&& MIN(C.y,D.y) <= MAX(A.y,B.y)
		&& cross(A,C,B) * cross(A,B,D) >= 0
		&& cross(C,A,D) * cross(C,D,B) >= 0;
}
//点O是否与简单多边形P[n]相交，保证P[n]==P[0]
bool isInter(point_t const&O,point_t const P[],int n){
    point_t pinf(1001,O.y);//极右点

	int ret = 0;
	for(int i=0;i<n;++i){
        //首先判断点是否在边上
        if ( isInter(O,P[i],P[i+1]) ) return true;

		//如果是水平边或者线段不相交
		if ( P[i].y == P[i+1].y || !isInter(O,pinf,P[i],P[i+1]) ) continue;

        //是否相较于边的较高的那个端点
        if ( P[i].y > P[i+1].y && isInter(P[i],O,pinf)
		  || P[i+1].y > P[i].y && isInter(P[i+1],O,pinf) ) continue;
 
		//否则+1
		++ret;
	}

	//奇数个交点，则O在P[n]内
	return ret & 1;
}
point_t O;
int main(){
	int n;
	while( scanf("%d",&n) && n ){
		scanf("%d%d",&O.x,&O.y);
		for(int i=0;i<n;++i)scanf("%I64d%I64d",&P[i].x,&P[i].y);
        P[n] = P[0];
		printf(isInter(O,P,n)?"Y\n":"N\n");
	}
	return 0;
}
