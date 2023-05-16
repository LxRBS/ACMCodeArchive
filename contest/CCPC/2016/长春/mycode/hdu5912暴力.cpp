/**
  1到N的N个数，问最少拿掉多少个使得剩下的数不能构成三角形
  N在20以内，随便怎么做都可以
  找规律发现留下的都是Fib数
*/

#include <stdio.h>
using namespace std;

int B[21] = {
    0,0,0,0,1,1,2,3,3,
    4,5,6,7,7,8,9,10,11,12,13,14
};
int main(){
    //freopen("2.txt","r",stdin);
    int nofkase;
    scanf("%d",&nofkase);
    for(int kase=1;kase<=nofkase;++kase){
        int n;
        scanf("%d",&n);
        printf("Case #%d: %d\n",kase,B[n]);
    }
    return 0;
}
