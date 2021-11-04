/*
  初始有N堆不同数量的东西，要把它们分成K等份
  两种操作：
  1. 合并相邻堆
  2. 一堆拆成两堆
  问最少要多少操作
  贪心
*/
#include <stdio.h>
using namespace std;

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}
typedef long long int llt;

int A[100010];
int N,K;
llt Sum;
void read(){
    N = getUnsigned();
    K = getUnsigned();
    Sum = 0LL;
    for(int i=0;i<N;++i){
        Sum += (A[i]=getUnsigned());
    }
}
int proc(){
    if(Sum%K) return -1;

    int ans = 0;
    llt const unit = Sum / K;

    int i=0;
    while(1){
        llt tmp = A[i];
        while(i<N&&tmp<unit) tmp += A[++i], ++ans;

        if(tmp%unit){
            ans += tmp / unit + 1;
            A[i+1] += tmp%unit;
        }else{
            ans += tmp / unit - 1;
        }
        ++i;
        if(i==N)break;
    }
    return ans;
}
int main(){
    //freopen("1.txt","r",stdin);
    int nofkase = getUnsigned();
    for(int kase=1;kase<=nofkase;++kase){
        read();
        printf("Case #%d: %d\n",kase,proc());
    }
    return 0;
}
