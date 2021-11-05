#include <iostream>
using namespace std;
typedef unsigned long long int llt;
llt C[201][101] = {0};

//求a的b次方对x取余数
int powmod(int a,int b,int x){
    int ans = 1;
	while( b ){
		if ( b & 1 ) ans = ans * a % x;
		a = a * a % x;
		b = b >> 1;
	}
	return ans;
}

int main(){
    int x;
	while( scanf("%d",&x) ){
		if ( 0 == x ) return 0;
		int a = ( powmod(2,x+x+1,29) + 28 ) % 29;
		int b = ( powmod(3,x+1,29) + 28 ) % 29;
		int c = ( powmod(22,x+1,29) + 28 ) % 29;
		printf("%d\n",(a*(b*15)%29*(c*18)%29)%29);
	}
	return 0;
}
