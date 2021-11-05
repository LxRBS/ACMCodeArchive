/*
n������,3����ɫ,��ת�ͷ�ת����
��һ���ж����ֲ�ͬ 
*/
#include <iostream>
using namespace std;

//���Լ��
int gcd(int a,int b){
	int r = a % b;
	while( r != 0 ){
		a = b;
		b = r;
		r = a % b;
	}
	return b;
}
//��x��y�η�
long long pow(long long int x,int y){
    long long ans = 1;
	do {
		if ( y & 1 ) ans *= x;
		x *= x;
	} while ( y = y >> 1 );
	return ans;
}
//������ת�任�ĵȼ��������cΪ��ɫ����
long long rotate(int c,int n){
	long long sum = 0;
	for(int i=1;i<=n;++i)
		sum += pow(c,gcd(i,n));
	return sum;
}
//���з�ת�任�ĵȼ������
long long reflect(int c,int n){
	if ( n & 1 ) return n * pow(c,1+(n>>1));
	return pow(c,1+(n>>1))*(n>>1) + pow(c,n>>1)*(n>>1);
}
int main(){
	int n;
	while(EOF != scanf("%d",&n)){
		if ( -1 == n ) return 0;
		if ( 0 == n ) {
			printf("0\n");
			continue;
		}
		long long ans = 0;
        ans += rotate(3,n);
		ans += reflect(3,n);
		ans /= n << 1;
		printf("%I64d\n",ans);
	}
	return 0;
}
