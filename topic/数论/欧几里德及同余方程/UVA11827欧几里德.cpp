/*
     求两两gcd的最大值
*/
#include <stdio.h>
#include <cmath>
#include <sstream>
#include <algorithm>
using namespace std;

typedef int int_t;

int_t gcd(int_t a,int_t b){
    while( b ){
        int_t r = b;
        b = a % b;
        a = r;
    }
    return a;
}

char A[300000+1];
int B[110];
int main(){
    int nofkase;
    scanf("%d",&nofkase);
    fgets(A,300000,stdin);
    while(nofkase--){
        fgets(A,300000,stdin);
        stringstream ss(A);
        int a,cnt=0;
        while(ss>>a) B[cnt++] = a;

        int ans = -1;
        for(int i=0;i<cnt;++i)for(int j=i+1;j<cnt;++j)ans=max(ans,gcd(B[i],B[j]));
        printf("%d\n",ans);
    }
    return 0;
}