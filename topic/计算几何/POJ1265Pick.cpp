//Pick公式，太简单了
#include <iostream>
using namespace std;

struct point_t{
	int x;
	int y;
	point_t(int xx=0,int yy=0):x(xx),y(yy){}
}P[101];

int cross(point_t const&O,point_t const&A,point_t const&B){
	int xoa = A.x - O.x;
	int yoa = A.y - O.y;
	int xob = B.x - O.x;
	int yob = B.y - O.y;
	return xoa * yob - yoa * xob; 
}

int gcd(int x,int y){
	if ( x < 0 ) x = -x;
	if ( y < 0 ) y = -y;

	if ( 0 == x ) return y;
	if ( 0 == y ) return x;
	
	int r = x % y;
	while( r ){
		x = y;
		y = r;
		r = x % y;
	}

	return y;
}

int main(){
	int t;
	scanf("%d",&t);
	for(int kase=1;kase<=t;++kase){
		int n;
		scanf("%d",&n);

		int e = n;
		int dx,dy;
		for(int i=1;i<n;++i){
			scanf("%d%d",&dx,&dy);
			P[i].x = P[i-1].x + dx;
			P[i].y = P[i-1].y + dy;
			e += gcd(dx,dy) - 1;
		}
		scanf("%d%d",&dx,&dy);
		e += gcd(dx,dy) - 1;

		int area = 0;
		for(int i=1;i<n-1;++i) area += cross(P[0],P[i],P[i+1]);

		int inner = ( area + 2 - e ) / 2;

		printf("Scenario #%d:\n",kase);
		printf("%d %d %d",inner,e,area/2);
		if ( area % 2 ) printf(".5\n");
		else            printf(".0\n");
		printf("\n");
	}
	return 0;
}