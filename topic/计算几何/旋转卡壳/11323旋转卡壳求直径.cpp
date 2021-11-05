#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
typedef int llt;

#define MAX(x,y) ( (x) > (y) ? (x) : (y) )
#define MIN(x,y) ( (x) < (y) ? (x) : (y) )

#define SIZE 1001

struct point_t{
	llt x,y;
	int sn;
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

//���ն���pO�ļ������򣬼�����ȵľ���Զ������ǰ�棬��Ϊ����Ҫ��һ��unique
point_t* pO;
bool comp4Graham(point_t const&A,point_t const&B){
	llt t = cross(*pO,A,B);
	if ( t ) return t > 0LL;

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
		while( top > 1 && cross(P[top-2],P[top-1],P[i]) <= 0LL )
			--top;
		P[top++] = P[i];
	}
	return top;
}
//����������ƽ��
llt dist2(point_t const&A,point_t const&B){
	llt x = A.x - B.x, y = A.y - B.y;
	return x * x + y * y;
}
//��ת���Ƿ���ֱ�������Ϊֱ���˵�����
void rc(point_t p[],int n,int ret[]){
	p[n] = p[0];
    int d = 0;
	int k1 = 0, k2 = 1;
	for(k1=0;k1<n;++k1){
		while( cross(p[k1+1],p[k2+1],p[k1]) > cross(p[k1+1],p[k2],p[k1]) )
			k2 = ( k2 + 1 ) % n;
		int t = dist2(p[k1],p[k2]);
		if ( t > d ){
			d = t;
			ret[0] = p[k1].sn;
			ret[1] = p[k2].sn;
			if ( ret[0] > ret[1] ) swap(ret[0],ret[1]);
		}else if ( t == d ){
			int s0 = p[k1].sn, s1 = p[k2].sn;
			if ( s0 > s1 ) swap(s0,s1);
			if ( s0 < ret[0] || (s0==ret[0]&&s1<ret[1]) )
				ret[0] = s0, ret[1] = s1;
		}
	}
}
int main(){
//	freopen("1.std.in","r",stdin);
	int n;
	int kase = 0;
	while( scanf("%d",&n) && n ){
		for(int i=0;i<n;++i){
			scanf("%d%d",&P[i].x,&P[i].y);
			P[i].sn = i;
		}
		n = Graham(P,n);
		int r[2];
		rc(P,n,r);
		printf("Case %d: %d %d\n",++kase,r[0],r[1]);
	}
	return 0;
}
