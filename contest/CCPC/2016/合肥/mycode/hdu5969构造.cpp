/**
  ��[L,R]����2����x��y
  ����x|y���
  ���ݷ�Χ1E18
  x��y�غϵ����λ���ܱ䣬�����ȡ1����
*/

#include <stdio.h>
using namespace std;

typedef unsigned long long int ull;

int main(){
    //freopen("2.txt","r",stdin);
    int nofkase;
    scanf("%d",&nofkase);
    while(nofkase--){
        ull x,y;
        scanf("%I64u%I64u",&x,&y);

        ull ans = 0ULL;
        ull k = 1ULL<<63;
        int i = 64;
        while(i&&!((x&k)^(y&k))){
            k >>= 1;
            --i;
            ans |= (x&k);
        }
        ans = ans | ((1ULL<<i)-1ULL);
        printf("%I64u\n",ans);
    }
    return 0;
}
