/*
n个珠子,3种颜色,旋转和翻转不变
问一共有多少种不同 
*/
#include <iostream>
using namespace std;

//最大公约数
int gcd(int a,int b){
	int r = a % b;
	while( r != 0 ){
		a = b;
		b = r;
		r = a % b;
	}
	return b;
}
//求x的y次方
long long pow(long long int x,int y){
    long long ans = 1;
	do {
		if ( y & 1 ) ans *= x;
		x *= x;
	} while ( y = y >> 1 );
	return ans;
}
//所有旋转变换的等价类个数，c为颜色个数
long long rotate(int c,int n){
	long long sum = 0;
	for(int i=1;i<=n;++i)
		sum += pow(c,gcd(i,n));
	return sum;
}
//所有翻转变换的等价类个数
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
