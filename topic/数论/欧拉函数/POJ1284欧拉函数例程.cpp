//���������p��ԭ�����𰸾���euler(p-1)
//420k,16ms,434B
//ŷ������������
#include <iostream>
using namespace std;
#define SIZE 65536
//ɸ����ŷ������
int Euler[SIZE] = {0};
void sieve(){
    Euler[1] = 1;
	for(int i=2;i<SIZE;++i){
	    if ( Euler[i] ) continue;
	    
		for(int j=i;j<SIZE;j+=i){
		    if ( !Euler[j] ) Euler[j] = j;

			Euler[j] = Euler[j] / i * ( i - 1 );
		}
	}
}

int main(){
	sieve();
	int p;
	while( EOF != scanf("%d",&p) )
		printf("%d\n",Euler[p-1]);
    return 0;
}