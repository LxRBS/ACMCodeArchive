//求莫比乌斯函数，模板题
#include <stdio.h>

int const SIZE = 5000000;
bool isComp[SIZE] = {false};
int P[SIZE] = {0};
int PCnt = 0;
int Mobius[SIZE] = {0,1};
void sieveAndMobius(){
	for(int i=2;i<SIZE;++i){
		if ( !isComp[i] ) P[PCnt++] = i, Mobius[i] = -1;

		for(int j=0;j<PCnt&&i*P[j]<SIZE;++j){
			isComp[i*P[j]] = true;

			if ( 0 == i % P[j] ){
				Mobius[i*P[j]] = 0;
				break;
			}else{
				Mobius[i*P[j]] = -Mobius[i];
			}
		}
	}
}

int mobius(int n){
    if ( n < SIZE ) return Mobius[n];

    int ret = 1;
    for(int i=0;i<PCnt&&P[i]*P[i]<=n;++i){
        if ( 0 == n % P[i] ){
            n /= P[i];
            if ( 0 == n % P[i] ) return 0;
            if ( 1 == n ) return ret;
            ret = -ret;
        }
    }
    return -ret;
}
int main(){
    sieveAndMobius();
    int n;
    scanf("%d",&n);
    printf("%d\n",mobius(n));
    return 0;
}
