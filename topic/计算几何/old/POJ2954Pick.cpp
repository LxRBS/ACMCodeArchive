#include <stdio.h>

int gcd(int a,int b){
	int r;
	while( r = a % b ){
		a = b;
		b = r;
	}
	return b;
}

//求边界点数，不计算端点
int edge(int x1,int y1,int x2,int y2){
	int x = x2 - x1;
	int y = y2 - y1;

	//都转到第一象限，结果是一致的
	if ( x < 0 ) x = -x;
	if ( y < 0 ) y = -y;

	if ( 0 == x ) return y - 1;
	if ( 0 == y ) return x - 1;

    return gcd(x,y) - 1;
}

int main(){
	int x1,y1,x2,y2,x3,y3;
	int x13,x12,y13,y12;
	int area,ans;

	while( 1 ){
		scanf("%d%d%d%d%d%d",&x1,&y1,&x2,&y2,&x3,&y3);
		if ( 0 == x1 && 0 == x2 && 0 == x3 && 0 == y1 && 0 == y2 && 0 == y3 )
			return 0;
		
		x13 = x3 - x1;
		y13 = y3 - y1;
		x12 = x2 - x1;
		y12 = y2 - y1;
		area = x12 * y13 - y12 * x13;
		
		if ( 0 == area ) {
			printf("0\n");
			continue;
		}

		if ( area < 0 ) area = -area;

        ans = area / 2 + 1 - ( 3 + edge(x1,y1,x2,y2) + edge(x1,y1,x3,y3) + edge(x2,y2,x3,y3) ) / 2;

		printf("%d\n",ans);
	}
	return 0;
}