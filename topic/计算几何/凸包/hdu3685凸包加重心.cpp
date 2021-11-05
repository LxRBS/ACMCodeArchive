//�ϸ�͹��
#include <cstdio>
#include <cmath>
#include <numeric>
#include <algorithm>
using namespace std;
typedef double llt;

#define MAX(x,y) ( (x) > (y) ? (x) : (y) )
#define MIN(x,y) ( (x) < (y) ? (x) : (y) )

#define SIZE 50001

struct point_t{
	llt x,y;
	point_t(llt a=0.0,llt b=0.0):x(a),y(b){}
}P[SIZE];

point_t const operator + (point_t const&lhs,point_t const&rhs){
	return point_t(lhs.x+rhs.x,lhs.y+rhs.y);
}

//���
llt dot(point_t const&O,point_t const&A,point_t const&B){
	llt xoa = A.x - O.x;
	llt yoa = A.y - O.y;
	llt xob = B.x - O.x;
	llt yob = B.y - O.y;
	return xoa * xob + yob * yoa;
}
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

//���ն���pO�ļ������򣬼�����ȵľ���Զ������ǰ�棬��Ϊ����Ҫ��һ��unique
point_t* pO;
bool comp4Graham(point_t const&A,point_t const&B){
	llt t = cross(*pO,A,B);
	if ( t ) return t > (llt)0;

	llt a1 = A.x > pO->x ? A.x - pO->x : pO->x - A.x;
	llt a2 = B.x > pO->x ? B.x - pO->x : pO->x - B.x;
	if ( a1 != a2 ) return a1 > a2;

	a1 = A.y > pO->y ? A.y - pO->y : pO->y - A.y;
	a2 = B.y > pO->y ? B.y - pO->y : pO->y - B.y;
	return a1 > a2;
}

//�����pO�Ƿ񼫽����
bool isEqPolar(point_t const&A,point_t const&B){
	return 0LL == cross(*pO,A,B);
}

//Graham��͹�����������û�й��ߵ㣬����������������
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

	//�������pO�Ĺ��ߵ���޳���ֻ�������һ��
	p = unique(P+1,P+n,isEqPolar);
	n = p - P;

	//������Grahamѭ��
	int top = 2;
	for(int i=2;i<n;++i){
		while( top > 1 && cross(P[top-2],P[top-1],P[i]) <= (llt)0 )
			--top;
		P[top++] = P[i];
	}
	return top;
}

//������
void getGravity(point_t const p[],int n,point_t& c){
	//�������ε����������
	c.x = c.y = 0.0;
	double total = 0.0;
	for(int i=2;i<n;++i){
		point_t tp = p[0] + p[i-1] + p[i];
		double area = cross(p[0],p[i-1],p[i]);
		c.x += tp.x * area;
		c.y += tp.y * area;
		total += area;
	}
	c.x /= total * 3.0;
	c.y /= total * 3.0;
	
	return;
}

int main(){
	int nofkase;
	scanf("%d",&nofkase);
	while(nofkase--){
		int n;
		scanf("%d",&n);
		for(int i=0;i<n;++i)scanf("%lf%lf",&P[i].x,&P[i].y);

		//������
		point_t cp;
		getGravity(P,n,cp);

		//��͹��
		n = Graham(P,n);
		P[n] = P[0];

		int ret = 0;
		for(int i=0;i<n;++i){
			double t1 = dot(P[i],P[i+1],cp);
			double t2 = dot(P[i+1],P[i],cp);
			if ( t1 > 0.0 && t2 > 0.0 ) ++ret;
		}
		printf("%d\n",ret);
	}
	return 0;
}