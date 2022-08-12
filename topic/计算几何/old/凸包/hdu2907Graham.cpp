//���ϸ�͹��
#include <cstdio>
#include <cmath>
#include <stack>
#include <algorithm>
using namespace std;
typedef int llt;

#define MAX(x,y) ( (x) > (y) ? (x) : (y) )
#define MIN(x,y) ( (x) < (y) ? (x) : (y) )

#define SIZE 31

struct point_t{
	llt x,y;
	int sn;
}P[SIZE],St[SIZE];

//�����OA��OB
llt cross(point_t const&O,point_t const&A,point_t const&B){
	llt xoa = A.x - O.x;
	llt yoa = A.y - O.y;
	llt xob = B.x - O.x;
	llt yob = B.y - O.y;
	return xoa * yob - xob * yoa;
}

//A�����B�����¸����󷵻���
bool isLowLeft(point_t const&A,point_t const&B){
	return A.y < B.y || ( A.y == B.y && A.x < B.x );
}

//������pO�ļ������򣬼�����ȵľ����������ǰ��
point_t* pO;
bool comp4Graham(point_t const&A,point_t const&B){
	llt t = cross(*pO,A,B);
	if ( t ) return t > 0LL;

	llt a1 = A.x > pO->x ? A.x - pO->x : pO->x - A.x;
	llt a2 = B.x > pO->x ? B.x - pO->x : pO->x - B.x;
	if ( a1 != a2 ) return a1 < a2;

	a1 = A.y > pO->y ? A.y - pO->y : pO->y - A.y;
	a2 = B.y > pO->y ? B.y - pO->y : pO->y - B.y;
	return a1 < a2;
}

//��¼ԭ�㼯����Щ����͹����
bool Flag[SIZE];

//Graham��͹��������������������
int Graham(point_t P[],int n){
	if ( 1 == n ) return 1;

	//Ѱ�����������
	point_t *p = min_element(P,P+n,isLowLeft);

	//����
	swap(*p,P[0]);

	if ( 2 == n ) return 2;

	//���������򣬼�����ȣ������������ǰ��
	pO = P;
	sort(P+1,P+n,comp4Graham);

	//�����һ���ߵĹ��ߵ㵹��������
	int k = n - 1;
	while( k && 0LL == cross(P[0],P[n-1],P[--k]) );//kΪ0˵�����е㹲��
	if ( k ) for(int i=k+1;i<(n+k+1)>>1;++i) swap(P[i],P[n+k-i]);


	
	St[0] = P[0];
	St[1] = P[1];
    //������Grahamѭ��
	int top = 2;
	for(int i=2;i<n;++i){
		while( top > 1 && cross(St[top-2],St[top-1],P[i]) < 0 ){
			//��ջ
			--top;
		}
		//��ջ
		St[top++] = P[i];
	}
	return top;
}
int main(){
	int nofkase;
	scanf("%d",&nofkase);
	while(nofkase--){
		int p,q,n;
		scanf("%d%d%d",&p,&q,&n);
		for(int i=0;i<n;++i){
			scanf("%d%d",&P[i].x,&P[i].y);
			P[i].sn = i;
		}

		fill(Flag,Flag+n,false);
		int cnt = Graham(P,n);
		for(int i=0;i<cnt;++i)Flag[St[i].sn]=true;

		int d = 0;
		Flag[n] = Flag[0];
		for(int i=0;i<n;++i)
			if( Flag[i] && !Flag[i+1] )
				++d;

		int ret = - d * p + ( cnt - d ) * q;
		printf("%d\n",ret<0?0:ret);
	}
	return 0;
}
