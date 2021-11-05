/*
    凸包求周长
*/

#include <stdio.h>
#include <math.h>
#include <algorithm>
using namespace std;

//点的数据结构
struct point_t{
	int x,y;
	point_t(int a=0,int b=0):x(a),y(b){}
};

//叉积OA×OB
int cross(point_t const&O,point_t const&A,point_t const&B){
	int xoa = A.x - O.x;
	int yoa = A.y - O.y;
	int xob = B.x - O.x;
	int yob = B.y - O.y;
	return xoa * yob - xob * yoa;
}

//判断点l是否比点r更下更左
bool isBottomLeft(point_t const&l,point_t const&r){
	if ( l.y != r.y ) return l.y < r.y;
	return l.x < r.x;
}

//为Graham排序做准备
point_t* pOrigin;
bool is4Graham(point_t const&l,point_t const&r){
	int t = cross(*pOrigin,l,r);
	if ( t ) return t > 0;
	return (l.x-pOrigin->x)*(l.x-pOrigin->x)<(r.x-pOrigin->x)*(r.x-pOrigin->x);
}

//Graham求严格凸包
int Graham(point_t p[],int n){
	if ( 1 == n ) return 1;

	//求最下最左点
	point_t* t = min_element(p,p+n,isBottomLeft);

	//与0点交换位置
	point_t ptmp(*t);
	*t = p[0];
	p[0] = ptmp;

	//相对于0点排序
	pOrigin = p;
	sort(p+1,p+n,is4Graham);

	//建栈循环
	int top = 2;
	for(int i=2;i<n;++i){
		while( top>1 && cross(p[top-2],p[top-1],p[i])<=0 )
			--top;
		p[top++] = p[i];
	}

	if( top>=3 && 0==cross(p[0],p[top-1],p[top-2]) )
		--top;

	return top;
}

int N,L;
point_t P[1010];
bool read(){
    if ( EOF == scanf("%d%d",&N,&L) ) return false;
    for(int i=0;i<N;++i)scanf("%d%d",&P[i].x,&P[i].y);
    return true;
}

inline double dist(point_t const&lhs,point_t const&rhs){
    double x = lhs.x - rhs.x;
    double y = lhs.y - rhs.y;
    return sqrt(x*x+y*y);
}

double proc(){
    int n = Graham(P,N);
    double r = dist(P[n-1],P[0]);
    for(int i=0;i<n-1;++i) r += dist(P[i],P[i+1]);
    return r + 2.0 * acos(-1.0) * L;
}

int main(){
    while ( read() ) printf("%.0f\n",proc());
    return 0;
}
