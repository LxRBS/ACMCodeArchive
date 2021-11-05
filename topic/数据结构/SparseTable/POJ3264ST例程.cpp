//ͬʱ�������������С
#include <stdio.h>
#include <math.h>

int A[50000];
int Max[50000][15];
int Min[50000][15];

void init(int n){
	int i,j;

	//��ʼ��������Ϊ1������
	for(i=0;i<n;i++) Max[i][0] = Min[i][0] = *(A+i);
	
	//���Ʊ�����
	for(j=1;(1<<j)<=n;j++){
		for(i=0;i+(1<<j)<=n;i++){
			//��һ�εļ�ֵ
		    int x = Max[i][j-1];
			//�ڶ��εļ�ֵ
			int y = Max[i+(1<<(j-1))][j-1];

			if ( x >= y ) Max[i][j] = x;
			else          Max[i][j] = y;

			x = Min[i][j-1];
			y = Min[i+(1<<(j-1))][j-1];

			if ( x <= y ) Min[i][j] = x;
			else          Min[i][j] = y;
		}
	}

	return ;
}

int query(int a,int b){
	int k;
	int x,y;
	int maxak,minak,maxkb,minkb;

	if ( a == b ) return 0;
	
	//�����䳤�ȵĶ���
	k = (int)( log((double)(b-a+1)) / log(2.0) );

	//����aΪ�׵�k���ȵļ�ֵ
    maxak = Max[a][k];
	minak = Min[a][k];

	//����b��β��k���ȼ�ֵ
    maxkb = Max[b+1-(1<<k)][k];
	minkb = Min[b+1-(1<<k)][k];

	if ( maxak < maxkb ) maxak = maxkb;
	if ( minak > minkb ) minak = minkb;

	return maxak - minak;
}

int main(){
	int n,q;
	int i;
	int a,b;

	scanf("%d%d",&n,&q);

	for(i=0;i<n;i++) scanf("%d",A+i);

	init(n);

	for(i=0;i<q;i++){
		scanf("%d%d",&a,&b);
		printf("%d\n",query(a-1,b-1));
	}
	return 0;
}