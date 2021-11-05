#include <iostream>
#include <algorithm>

struct point_t{
	int x;
	int y;
};

#define  SIZE  50000

point_t P[SIZE+1];

//�����OA��OB
int cross(point_t const& O,point_t const& A,point_t const& B){
	return (A.x - O.x) * (B.y - O.y) - (B.x - O.x) * (A.y - O.y);
}

//Ϊgraham������д�ıȽϺ���
bool cmp(point_t const& left,point_t const& right){
	int xl = left.x - P->x;
	int yl = left.y - P->y;
	int xr = right.x - P->x;
	int yr = right.y - P->y;

	int xmul = xl * yr - yl * xr;

	//��A��BΪ˳ʱ�룬��B�ļ��ǿ϶�С��A��ע�����P[0]�����������
	if ( xmul > 0 || (0==xmul && xl * xl + yl * yl < xr * xr + yr * yr) )
		return true;

	return false;
}

//����͹���ĵ���
//ͬʱѰ����������㣬Ϊ��ת������׼��
int graham(int n){
	int blk = 0;
	//�����������
	for(int i=1;i<n;i++){
		if ( (P+i)->y < (P+blk)->y || ( (P+i)->y==(P+blk)->y && (P+i)->x<(P+blk)->x ) )
			blk = i;
	}
	//����
	point_t t(*P);
	*P = *(P+blk);
	*(P+blk) = t;

	std::sort(P+1,P+n,cmp);

	int k = 2;

	//ȷ��ǰ�����㲻��ͬһֱ����
	while( k < n && 0 == cross(*P,*(P+1),*(P+k)) ){
        *(P+1) = *(P+k);
		k++;
	}

	int top = 2;

	for(int i=k;i<n;i++){
		//�ϸ�͹����͹����û�й��ߵ�����
		while( cross(*(P+top-2),*(P+top-1),*(P+i)) <= 0 )
			top--;
		*(P+top++) = *(P+i);
	}

	return top;
}


int main(){
	int n;
	scanf("%d",&n);
	
	for(int i=0;i<n;i++) scanf("%d%d",&(P+i)->x,&(P+i)->y);

	if ( 2 == n ){
		int x = P->x - (P+1)->x;
		int y = P->y - (P+1)->y;
		printf("%d\n",x*x+y*y);
		return 0;
	}

	n = graham(n);
    
	//����һ���ڱ�
	*(P+n) = *P;

	if ( 2 == n ){
		int x = P->x - (P+1)->x;
		int y = P->y - (P+1)->y;
		printf("%d\n",x*x+y*y);
		return 0;
	}

    int k = 1;
	int ans = 0;

	int x,y,tmp;

	for(int i=0;i<n;i++){
              //ѡ������i����Զ�Ķ˵�
		while( cross(*(P+i),*(P+i+1),*(P+k+1)) > cross(*(P+i),*(P+i+1),*(P+k)) )
			k = ( k + 1 ) % n;
		
		x = (P+i)->x - (P+k)->x;
		y = (P+i)->y - (P+k)->y;
		tmp = x * x + y * y;
              
              //���ֵ
		if ( tmp > ans ) ans = tmp;
	}

	printf("%d\n",ans);

	return 0;
}