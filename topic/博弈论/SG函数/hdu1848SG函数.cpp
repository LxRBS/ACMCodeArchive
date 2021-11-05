#include <cstdio>
#include <algorithm>
using namespace std;

int Fib[15] = {1,2};
int Sg[1001] = {0};
void init(){
	for(int i=2;i<15;++i)Fib[i] = Fib[i-1] + Fib[i-2];
	for(int i=1;i<1001;++i){
		bool a[16] = {false};
		for(int j=0;Fib[j]<=i;++j)a[Sg[i-Fib[j]]] = true;
		Sg[i] = find(a,a+16,false) - a;
	}
}

int main(){
	init();
	int n,m,p;
	while( scanf("%d%d%d",&n,&m,&p) ){
		if ( 0 == n && 0 == m && 0 == p ) return 0;
		printf(Sg[n]^Sg[m]^Sg[p]?"Fibo\n":"Nacci\n");
	}
	return 0;
}