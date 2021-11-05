#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

bool isOK(int n){
    bool t = false;
    while(n){
        int a = n % 10;
        if ( 4 == a || ( t && 6 == a ) ) return false;
        t = 2 == a;
        n /= 10;
    }
    return true;
}

int A[1000000] = {0};
void init(){
    for(int i=1;i<1000000;++i){
        A[i] = A[i-1] + ( isOK(i) ? 1 : 0 );
    }
}

int N,M;
int main(){
    init();
    while( scanf("%d%d",&N,&M),N,M ){
        printf("%d\n",A[M]-A[N-1]);
    }
    return 0;
}
