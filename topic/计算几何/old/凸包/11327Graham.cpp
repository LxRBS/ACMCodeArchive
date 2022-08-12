//���ϸ�͹��
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long llt;

#define MAX(x,y) ( (x) > (y) ? (x) : (y) )
#define MIN(x,y) ( (x) < (y) ? (x) : (y) )

#define SIZE 101

struct point_t{
	llt x,y;
}P[SIZE];

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
	if ( t ) return t > (llt)0;
	
	llt a1 = A.x > pO->x ? A.x - pO->x : pO->x - A.x;
	llt a2 = B.x > pO->x ? B.x - pO->x : pO->x - B.x;
    if ( a1 != a2 ) return a1 < a2;

	a1 = A.y > pO->y ? A.y - pO->y : pO->y - A.y;
	a2 = B.y > pO->y ? B.y - pO->y : pO->y - B.y;
	return a1 < a2;
}

//Graham��͹������������й��ߵ㣬����������������
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

	//������Grahamѭ��
	int top = 2;
	for(int i=2;i<n;++i){
		while( top > 1 && cross(P[top-2],P[top-1],P[i]) < (llt)0 )
			--top;
		P[top++] = P[i];
	}
	return top;
}
int main(){
	int n;
	while( scanf("%d",&n) && n ){
        for(int i=0;i<n;++i)scanf("%I64d%I64d",&P[i].x,&P[i].y);
		n = Graham(P,n);

		printf("%d\n",n);
		for(int i=0;i<n;++i)printf("%lld %lld\n",P[i].x,P[i].y);
	}
	return 0;
}
