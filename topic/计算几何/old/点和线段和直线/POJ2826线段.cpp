/*
给定2条线段，问这2条线段构成的造型能接住多少雨水（假设雨从上面落下，雨水以面积计算）
*/
#include <stdio.h>

#define  MIN(x,y) ( (x) < (y) ? (x) : (y) )
#define  MAX(x,y) ( (x) > (y) ? (x) : (y) )

struct point_t{
	double x;
	double y;
};

//OA×OB
double cross(struct point_t O,struct point_t A, struct point_t B){
	double xoa = A.x - O.x;
	double yoa = A.y - O.y;
	double xob = B.x - O.x;
	double yob = B.y - O.y;
	return xoa * yob - yoa * xob;
}
//判断AB、CD是否相交
int isInter(struct point_t A, struct point_t B,struct point_t C,struct point_t D){
    return MIN(A.x,B.x) <= MAX(C.x,D.x)
		&& MIN(A.y,B.y) <= MAX(C.y,D.y)
		&& MIN(C.x,D.x) <= MAX(A.x,B.x)
		&& MIN(C.y,D.y) <= MAX(A.y,B.y)
		&& cross(A,C,B) * cross(A,B,D) >= 0
		&& cross(C,A,D) * cross(C,D,B) >= 0;
}

//求AB、CD的交点
int getInter(struct point_t A, struct point_t B,struct point_t C,struct point_t D,struct point_t* P){
	double yAB = B.y - A.y;
	double xAB = B.x - A.x;

	double yCD = D.y - C.y;
	double xCD = D.x - C.x;

	double cst1,cst2;

	//两个线段共线，肯定接不住雨水
	if ( 0 == xAB * yCD - yAB * xCD ) return 0;

	cst1 = A.x * yAB - A.y * xAB;
	cst2 = C.x * yCD - C.y * xCD;

	P->x = ( cst1 * xCD - cst2 * xAB ) / ( yAB * xCD - yCD * xAB );
	P->y = ( P->x * yAB - cst1 ) / xAB;

	return 1;
}
//至少有2个端点比交点高
int isHigher(struct point_t A, struct point_t B,struct point_t C,struct point_t D,struct point_t P){
    if ( A.y <= P.y && B.y <= P.y ) return 0;
	if ( C.y <= P.y && D.y <= P.y ) return 0;
    
	return 1;
}

//求接雨水的面积
double area(struct point_t A, struct point_t B,struct point_t C,struct point_t D,struct point_t P){
    //求出两个高的端点
	struct point_t low,high;
	struct point_t T;

	double xPH,yPH;

	double ans;

	if ( A.y > P.y ){
        low.y = A.y;
		low.x = A.x;
	}else{
		low.y = B.y;
		low.x = B.x;
	}

	if ( C.y > P.y ){
		high.y = C.y;
		high.x = C.x;
	}else{
		high.y = D.y;
		high.x = D.x;
	}

	//再在这两个端点中分出高矮
	if ( low.y > high.y ){
        double t;
		t = high.y;
		high.y = low.y;
		low.y = t;
		t = high.x;
		high.x = low.x;
		low.x = t;
	}

	//交点P在x方向需在2个端点的中间，才能接到雨水，这个判据是错误的
// 	if ( ( P.x - low.x ) * ( P.x - high.x ) > EPS )
// 		return 0.0;

	T.x = low.x;

	yPH = high.y - P.y;
	xPH = high.x - P.x;

	if ( 0 != xPH ){
	    T.y = P.y +  ( T.x - P.x ) * yPH / xPH;
		if ( T.y > low.y && T.y <= high.y ) return 0.0;
	}

    T.y = low.y;

    T.x = P.x + ( T.y - P.y ) * xPH / yPH;

	ans = 0.5f * cross(P,T,low);
	
	if ( ans < 0 ) return -ans;

	return ans;
}

struct point_t A,B,C,D;
struct point_t P;

int main(){
	int n;
	scanf("%d",&n);

	while(n--){
		scanf("%lf%lf%lf%lf",&A.x,&A.y,&B.x,&B.y);
		scanf("%lf%lf%lf%lf",&C.x,&C.y,&D.x,&D.y);

		//不相交肯定是0
		if ( !isInter(A,B,C,D) ){
			printf("0.00\n");
			continue;
		}

		//求交点
		if ( !getInter(A,B,C,D,&P) ){
			printf("0.00\n");
			continue;
		}

		//判断第一个条件
		if ( !isHigher(A,B,C,D,P) ){
			printf("0.00\n");
			continue;
		}

		printf("%.2lf\n",area(A,B,C,D,P));
		
	}

	return 0;
}