#include <stdio.h>
#include <math.h>

int N,M;

#define INF 0x7FFFFFFF

int Ans = INF;

/*ÿһ�����С���*/
int VMin[21];

/*ÿһ�����С���*/
int AMin[21];

void dfs(int depth,int fr,int fh,int volum,int area){
	int r,h;
	if ( 0 == depth ){
		if ( 0 == volum && Ans > area ) Ans = area;
		return;
	}

	/*���ʣ������С���������ʣ�����������*/
	if ( volum < VMin[depth] ) return;

	/*�����ǰ��С��Ԥ�ڵ���С���������*/
	if ( Ans <= area + AMin[depth] ) return;

    /*����ʣ������������С�����*/
	if ( Ans <= area + 2 * volum / fr ) return;

	for(r=fr-1;r>=depth;r--){
		/*������ʹ�õ�������*/
        int maxh = ( volum - VMin[depth-1] ) / ( r * r );
		if ( maxh > fh - 1 ) maxh = fh - 1;
        for(h=maxh;h>=depth;h--) dfs(depth-1,r,h,volum-r*r*h,area+2*r*h);
	}

	return;
}

int main(){
	int r,h;
	int volum,area;

	/*��ν��С���ǵ�r��뾶��߶Ⱦ�ȡr��r��1��20����������*/
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