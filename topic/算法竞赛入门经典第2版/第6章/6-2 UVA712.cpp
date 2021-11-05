//二叉树，从根往下走

#include <cstdio>
#include <algorithm>
using namespace std;

int N;
int A[1000];
bool read(){
    scanf("%d",&N);
    if ( 0 == N ) return false;

    char a[20];
    for(int i=0;i<N;++i)scanf("%s",a);

    fill(A,A+(1<<N),0);
    for(int i=0,n=(1<<N);i<n;++i)scanf("%1d",A+i);
    return true;
}
int M;
void proc(){
    scanf("%d",&M);
    while(M--){
        int r = 0;
        for(int i=0;i<N;++i){
            int a;
            scanf("%1d",&a);
            r = ( r << 1 ) | a;
        }
        printf("%d",A[r]);
    }
    printf("\n\n");
}
int main(){
    //freopen("1.txt","r",stdin);
    for(int kase=1;read();++kase){
        printf("S-Tree #%d:\n",kase);
        proc();
    }
    return 0;
}