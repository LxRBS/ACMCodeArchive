#include <cstdio>
#include <algorithm>
using namespace std;

#define SIZE 51

struct point_t{
	int x;
	int y;
}P[SIZE];
//叉积，OA×OB
inline int cross(point_t const&O,point_t const& A,point_t const&B){
	int xoa = A.x - O.x;
	int yoa = A.y - O.y;
	int xob = B.x - O.x;
	int yob = B.y - O.y;
	return xoa * yob - xob * yoa;
}

inline bool isLowLeft(point_t const&A,point_t const&B){
	if ( A.y != B.y ) return A.y < B.y;
	return A.x < B.x;
}

bool comp(point_t const&A,point_t const&B){
	int t = cross(*P,A,B);
	if ( t ) return t > 0;
	return ( A.x - P->x ) * ( A.x - P->x ) < ( A.y - P->y ) * ( A.y - P->y );
}

inline bool isUpLeft(point_t const&A,point_t const&B){
	if ( A.y != B.y ) return A.y > B.y;
	return A.x < B.x;
}
//Graham凸包，n为点的数量，返回值为凸包的点的数量
int Graham(int n){
	//求最左最下点，然后与零点交换
	point_t* tp = min_element(P,P+n,isLowLeft);
	swap(*P,*tp);

	//排序
	sort(P+1,P+n,comp);

	int top = 3;
	for(int i=3;i<n;++i){
		while( top > 1 && cross(P[top-2],P[top-1],P[i]) <= 0 )
			--top;
		P[top++] = P[i];
	}

	//去除最后一条边的共线点 
	while( top > 2 && 0 == cross(P[0],P[top-1],P[top-2]) ) --top;
	return top;
}
void solve3(){
    //找出最高点
	point_t* tp = min_element(P,P+3,isUpLeft);
	swap(*P,*tp);
    sort(P+1,P+3,comp);
	if ( 0 == cross(P[0],P[1],P[2]) ){
		printf("2\n");
		printf("%d %d\n",P->x,P->y);
		printf("%d %d\n",P[2].x,P[2].y);
		return;
	}
	printf("3\n");
	printf("%d %d\n",P->x,P->y);
	printf("%d %d\n",P[2].x,P[2].y);
	printf("%d %d\n",P[1].x,P[1].y);
}
int main(){
	int nofkase;
	scanf("%d",&nofkase);
	for(int kase=1;kase<=nofkase;++kase){
		int n;
		scanf("%*d%d",&n);
		for(int i=0;i<n;++i)scanf("%d%d",&P[i].x,&P[i].y);

		if ( 3 == n ){
			printf("%d ",kase);
			solve3();
			continue;
		}

		n = Graham(n);
		//找出最上最左点
		point_t* tp = min_element(P,P+n,isUpLeft);
		int k = tp - P;

		//输出
		printf("%d %d\n",kase,n);
		for(int i=k;i>=0;--i)printf("%d %d\n",P[i].x,P[i].y);
		for(int i=n-1;i>k;--i)printf("%d %d\n",P[i].x,P[i].y);
	}
	return 0;
}
