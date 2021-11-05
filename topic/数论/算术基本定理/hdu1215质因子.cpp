#include <iostream>
using namespace std;
#define SIZE 500001
int Arr[SIZE];
int main(){
	for(int i=1;i<SIZE;++i)Arr[i] = 1;
	for(int i=2;i<=(SIZE>>1);++i){
		for(int j=i+i;j<SIZE;j+=i){
			Arr[j] += i;
		}
	}

	int t;
	scanf("%d",&t);
	while(t--){
		int n;
		scanf("%d",&n);
		printf("%d\n",Arr[n]);
	}
	return 0;
}