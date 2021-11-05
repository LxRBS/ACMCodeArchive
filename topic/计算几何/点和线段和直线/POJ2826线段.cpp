/*
����2���߶Σ�����2���߶ι��ɵ������ܽ�ס������ˮ����������������£���ˮ��������㣩
*/
#include <stdio.h>

#define  MIN(x,y) ( (x) < (y) ? (x) : (y) )
#define  MAX(x,y) ( (x) > (y) ? (x) : (y) )

struct point_t{
	double x;
	double y;
};

//OA��OB
double cross(struct point_t O,struct point_t A, struct point_t B){
	double xoa = A.x - O.x;
	double yoa = A.y - O.y;
	double xob = B.x - O.x;
	double yob = B.y - O.y;
	return xoa * yob - yoa * xob;
}
//�ж�AB��CD�Ƿ��ཻ
int isInter(struct point_t A, struct point_t B,struct point_t C,struct point_t D){
    return MIN(A.x,B.x) <= MAX(C.x,D.x)
		&& MIN(A.y,B.y) <= MAX(C.y,D.y)
		&& MIN(C.x,D.x) <= MAX(A.x,B.x)
		&& MIN(C.y,D.y) <= MAX(A.y,B.y)
		&& cross(A,C,B) * cross(A,B,D) >= 0
		&& cross(C,A,D) * cross(C,D,B) >= 0;
}

//��AB��CD�Ľ���
int getInter(struct point_t A, struct point_t B,struct point_t C,struct point_t D,struct point_t* P){
	double yAB = B.y - A.y;
	double xAB = B.x - A.x;

	double yCD = D.y - C.y;
	double xCD = D.x - C.x;

	double cst1,cst2;

	//�����߶ι��ߣ��϶��Ӳ�ס��ˮ
	if ( 0 == xAB * yCD - yAB * xCD ) return 0;

	cst1 = A.x * yAB - A.y * xAB;
	cst2 = C.x * yCD - C.y * xCD;

	P->x = ( cst1 * xCD - cst2 * xAB ) / ( yAB * xCD - yCD * xAB );
	P->y = ( P->x * yAB - cst1 ) / xAB;

	return 1;
}
//������2���˵�Ƚ����
int isHigher(struct point_t A, struct point_t B,struct point_t C,struct point_t D,struct point_t P){
    if ( A.y <= P.y && B.y <= P.y ) return 0;
	if ( C.y <= P.y && D.y <= P.y ) return 0;
    
	return 1;
}

//�����ˮ�����
double area(struct point_t A, struct point_t B,struct point_t C,struct point_t D,struct point_t P){
    //��������ߵĶ˵�
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

	//�����������˵��зֳ��߰�
	if ( low.y > high.y ){
        double t;
		t = high.y;
		high.y = low.y;
		low.y = t;
		t = high.x;
		high.x = low.x;
		low.x = t;
	}

	//����P��x��������2���˵���м䣬���ܽӵ���ˮ������о��Ǵ����
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

		//���ཻ�϶���0
		if ( !isInter(A,B,C,D) ){
			printf("0.00\n");
			continue;
		}

		//�󽻵�
		if ( !getInter(A,B,C,D,&P) ){
			printf("0.00\n");
			continue;
		}

		//�жϵ�һ������
		if ( !isHigher(A,B,C,D,P) ){
			printf("0.00\n");
			continue;
		}

		printf("%.2lf\n",area(A,B,C,D,P));
		
	}

	return 0;
}