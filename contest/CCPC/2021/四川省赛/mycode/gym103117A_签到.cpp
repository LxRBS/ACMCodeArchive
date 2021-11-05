/// Ç©µ½
#include <bits/stdc++.h>
using namespace std;

typedef long long llt;

int const A[101] = {
    0, 0, 1, 1,
    2, 2, 3, 3,
    3, 2, 2, 1,
    1, 0
};

int main(){
    //freopen("1.txt","r",stdin);
    int nofkase;
    scanf("%d",&nofkase);
    while(nofkase--){
        int k;
        scanf("%d", &k);
        printf("%d\n", A[k]);
    }
    return 0;
}
