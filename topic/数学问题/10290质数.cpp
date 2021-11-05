#include <cstdio>
#include <iostream>
using namespace std;

typedef long long llt;
llt const SIZE = 1000000LL;

bool isComp[SIZE] = {false};
llt P[SIZE] = {0};
llt PCnt = 0;
void sieve(){
	for(llt i=2;i<SIZE;++i){
		if ( !isComp[i] ) P[PCnt++] = i;

		for(llt j=0;j<PCnt&&i*P[j]<SIZE;++j){
			isComp[i*P[j]] = true;
			if ( 0 == i % P[j] ) break;
		}
	}
}

llt f(llt p,llt a,llt b){
    llt t = p * p;
    while( t < a ) t *= p;

    llt r = 0LL;
    while( t <= b ) t*=p, ++r;
    return r;
}
llt f(llt a,llt b){
    llt ret = 0LL;
    for(llt i=0;i<PCnt&&P[i]*P[i]<=b;++i){
        ret += f(P[i],a,b);
    }
    return ret;
}

int main()
{
    sieve();
    int nofkase;
    scanf("%d",&nofkase);
    while(nofkase--){
        llt a,b;
        scanf("%I64d%I64d",&a,&b);
        printf("%I64d\n",f(a,b));
    }
    return 0;
}
