#include <stdio.h>

int Father[13];

void init(int n){
	int i;
	for(i=1;i<=n;i++)
		Father[i] = i;
}

int find(int x){
	int k = Father[x];
	return k == x
		? k 
		: ( Father[x] = find(k) );
}

void unite(int x,int y){
	x = find(x);
	y = find(y);
	Father[y] = x;
}

//叉积
int cross(int x0,int y0,int x1,int y1,int x2,int y2){
	int x01 = x1 - x0;
	int y01 = y1 - y0;
	int x02 = x2 - x0;
	int y02 = y2 - y0;
	return x01 * y02 - y01 * x02;
}

#define MAX(x,y) ( (x) >= (y) ? (x) : (y) )
#define MIN(x,y) ( (x) <= (y) ? (x) : (y) )

//判断两线段是否相交
int isInter(int x1,int y1,int x2,int y2,
			int a1,int b1,int a2,int b2){
    return MAX(x1,x2) >= MIN(a1,a2)
		&& MAX(y1,y2) >= MIN(b1,b2)
		&& MAX(a1,a2) >= MIN(x1,x2)
		&& MAX(b1,b2) >= MIN(y1,y2)
		&& cross(x1,y1,a2,b2,x2,y2) * cross(x1,y1,x2,y2,a1,b1) >= 0
		&& cross(a1,b1,x1,y1,a2,b2) * cross(a1,b1,a2,b2,x2,y2) >= 0;
}

int main(){
	int i,j,n;
	int x1[13],y1[13],x2[13],y2[13];
	int a,b;

	while( scanf("%d",&n) && n ){
		init(n);

		scanf("%d%d%d%d",x1+1,y1+1,x2+1,y2+1);

		for(i=2;i<=n;i++){
			scanf("%d%d%d%d",x1+i,y1+i,x2+i,y2+i);

			for(j=1;j<i;j++)if(isInter( 
				x1[j],y1[j],x2[j],y2[j],
				x1[i],y1[i],x2[i],y2[i] ) )
				unite(i,j);
		}

		while( scanf("%d%d",&a,&b) ){
			if ( 0 == a && 0 ==b ) break;

			if ( find(a) == find(b) )
				printf("CONNECTED\n");
			else
				printf("NOT CONNECTED\n");
		}
	}
	return 0;
}