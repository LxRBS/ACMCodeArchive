//����򵥶�����ཻ
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

//�����OA��OB
llt cross(point_t const&O,point_t const&A,point_t const&B){
	llt xoa = A.x - O.x;
	llt yoa = A.y - O.y;
	llt xob = B.x - O.x;
	llt yob = B.y - O.y;
	return xoa * yob - xob * yoa;
}

//��O�Ƿ����߶�AB��
bool isInter(point_t const&O,point_t const&A,point_t const&B){
	return 0 == cross(O,A,B)
		&& O.x <= MAX(A.x,B.x) 
		&& O.x >= MIN(A.x,B.x)
		&& O.y <= MAX(A.y,B.y)
		&& O.y >= MIN(A.y,B.y) ;
}

//�ж��߶�AB�Ƿ����߶�CD�ཻ
bool isInter(point_t const&A,point_t const&B,point_t const&C,point_t const&D){
	return MIN(A.x,B.x) <= MAX(C.x,D.x)
		&& MIN(A.y,B.y) <= MAX(C.y,D.y)
		&& MIN(C.x,D.x) <= MAX(A.x,B.x)
		&& MIN(C.y,D.y) <= MAX(A.y,B.y)
		&& cross(A,C,B) * cross(A,B,D) >= 0
		&& cross(C,A,D) * cross(C,D,B) >= 0;
}
//��O�Ƿ���򵥶����P[n]�ཻ����֤P[n]==P[0]
bool isInter(point_t const&O,point_t const P[],int n){
    point_t pinf(1001,O.y);//���ҵ�

	int ret = 0;
	for(int i=0;i<n;++i){
        //�����жϵ��Ƿ��ڱ���
        if ( isInter(O,P[i],P[i+1]) ) return true;

		//�����ˮƽ�߻����߶β��ཻ
		if ( P[i].y == P[i+1].y || !isInter(O,pinf,P[i],P[i+1]) ) continue;

        //�Ƿ�����ڱߵĽϸߵ��Ǹ��˵�
        if ( P[i].y > P[i+1].y && isInter(P[i],O,pinf)
		  || P[i+1].y > P[i].y && isInter(P[i+1],O,pinf) ) continue;
 
		//����+1
		++ret;
	}

	//���������㣬��O��P[n]��
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
