/*
    NλK��������û��2��������0��һ���ж��ٸ�
*/
#include <cstdio>
#include <algorithm>
using namespace std;

int N,K;
bool read(){
    if ( EOF == scanf("%d%d",&N,&K) ) return false;

    int a = 1, b = K - 1;
    int c;
    for(int i=2;i<=N;++i){
        c = ( K - 1 ) * ( a + b );
        a = b;
        b = c;
    }
    printf("%d\n",c);
    return true;
}
int main(){
    //freopen("1.txt","r",stdin);
    while( read() );
    return 0;
}

