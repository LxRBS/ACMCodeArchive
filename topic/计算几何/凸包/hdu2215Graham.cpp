#include <cstdio>
#include <cmath>
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

int dist2(point_t const&A,point_t const&B){
	int x = A.x - B.x;
	int y = A.y - B.y;
	return x * x + y * y;
}

#define SIZE 103
point_t P[SIZE];

int main(){
	int n;
	while(scanf("%d",&n)&&n){
        for(int i=0;i<n;++i)scanf("%d%d",&P[i].x,&P[i].y);

		if ( 1 == n ){
			printf("0.50\n");
			continue;
		}

		n = Graham(P,n);

		if ( 2 == n ){
			double t = sqrt((double)dist2(P[0],P[1]));
			printf("%.2lf\n",t/2.0+0.5);
			continue;
		}

		double ans = -1.0;
		for(int i=0;i<n-2;++i)for(int j=i+1;j<n-1;++j)for(int k=j+1;k<n;++k){
			int e2[3] = {
				dist2(P[i],P[j]),dist2(P[j],P[k]),dist2(P[k],P[i])
			};
			sort(e2,e2+3);

			double t;
			if ( e2[0] + e2[1] <= e2[2] ) t = sqrt((double)e2[2]) / 2.0;
			else{
				double s = (double)cross(P[i],P[j],P[k]) / 2.0;
                t = sqrt((double)e2[0])*sqrt((double)e2[1])*sqrt((double)e2[2]) / 4.0 / s;
			}
			if ( t > ans ) ans = t;
		}
		printf("%.2lf\n",ans+0.5);
	}
	return 0;
}