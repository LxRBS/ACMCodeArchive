#include <stdio.h>
#include <math.h>

int N,M;

#define INF 0x7FFFFFFF

int Ans = INF;

/*每一层的最小体积*/
int VMin[21];

/*每一层的最小面积*/
int AMin[21];

void dfs(int depth,int fr,int fh,int volum,int area){
	int r,h;
	if ( 0 == depth ){
		if ( 0 == volum && Ans > area ) Ans = area;
		return;
	}

	/*如果剩余层的最小体积超过了剩余体积，忽略*/
	if ( volum < VMin[depth] ) return;

	/*如果当前答案小于预期的最小面积，忽略*/
	if ( Ans <= area + AMin[depth] ) return;

    /*利用剩余体积估算的最小面积是*/
	if ( Ans <= area + 2 * volum / fr ) return;

	for(r=fr-1;r>=depth;r--){
		/*本层能使用的最大体积*/
        int maxh = ( volum - VMin[depth-1] ) / ( r * r );
		if ( maxh > fh - 1 ) maxh = fh - 1;
        for(h=maxh;h>=depth;h--) dfs(depth-1,r,h,volum-r*r*h,area+2*r*h);
	}

	return;
}

int main(){
	int r,h;
	int volum,area;

	/*所谓最小就是第r层半径与高度均取r，r从1到20，从上往下*/
	VMin[0] = AMin[0] = 0;
	for(r=1;r<=20;r++){
        VMin[r] = VMin[r-1] + r*r*r;
		AMin[r] = AMin[r-1] + 2*r*r;
	}

	scanf("%d%d",&N,&M);

	for(r=N+1;r>=M;r--){
		int maxh = ( N - VMin[M-1] ) / ( r * r );
		if ( maxh > N + 1 ) maxh = N + 1;
		for(h=maxh;h>=M;h--) dfs(M-1,r,h,N-r*r*h,2*r*h+r*r);
	}

	if ( INF == Ans ) printf("0\n");
	else 	printf("%d\n",Ans);

	return 0;
}