#include <cstdio>
#define SIZE 10011

bool isComp[SIZE] = {false};
int P[SIZE] = {2};
int PCnt = 1;
void sieve(){
	for(int i=4;i<SIZE;i+=2)isComp[i] = true;
	for(int i=3;i<SIZE;++i){
		if ( isComp[i] ) continue;

		P[PCnt++] = i;
		for(int j=i*i;j<SIZE;j+=i<<1)
			isComp[j] = true;
	}
}

//求各位数字和
int sumDigits(int n){
	int ret = 0;
	while( n ){
        ret += n % 10;
		n /= 10;
	}
	return ret;
}
int main(){
	sieve();
	int n;
	while( scanf("%d",&n) && n ){
		while(++n){
			//答案要求非素数
			if ( n < SIZE && !isComp[n] ) continue;

			int y = n;
            int t1 = sumDigits(y);
			int t2 = 0;
			bool flag = false;
			for(int i=0;P[i]*P[i]<=y&&i<PCnt;++i){
				if ( y % P[i] ) continue;

				flag = true;
				int x = sumDigits(P[i]);
				t2 += x;
				y /= P[i];
				while( 0 == y % P[i] ) y/=P[i],t2+=x;
			}
			if ( y > 1 ) t2 += sumDigits(y);

			if ( t1 == t2 && flag ) break;
		}
		printf("%d\n",n);
	}
}