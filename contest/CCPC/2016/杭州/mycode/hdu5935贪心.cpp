/*
  汽车在一条直线上做不减速行驶
  已知若干通过的坐标位置，而且通过这些位置时必须是整数时间
  问最小通过时间是多少
  贪心
  最小通过，则最后一段必然只用1s，然后往前推
  double类型需要注意精度，或者使用分数
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

double const EPS = 1E-8;
inline bool is0(double x){
    return -EPS <= x && x <= EPS;
}

int N;
int A[100100];

int proc(){
    //最后一段1s过
    int ret = 1;
    double velocity = A[N] - A[N-1];
    for(int i=N-1;i>0;--i){
        double ss = A[i] - A[i-1];
        if(is0(ss-velocity)){//如果速度和长度恰好相等，则不用改变速度，还是1s过
            ++ret;
        }else if(velocity>ss){//如果速度大于长度，则还是1s过，速度减小
            ++ret;
            velocity = ss;
        }else{//如果长度较大，则需判断是否能整除
            //这一步实现了整除或者不能整除则加1的操作
            int t = (int)((ss-EPS)/velocity)+1;
            ret += t;
            velocity = ss / t;
        }
    }
    return ret;
}

int main(){
    //freopen("1.txt","r",stdin);
    int nofkase = getUnsigned();
    for(int kase=1;kase<=nofkase;++kase){
        N = getUnsigned();
        for(int i=1;i<=N;++i)A[i] = getUnsigned();

        printf("Case #%d: %d\n",kase,proc());
    }
    return 0;
}
