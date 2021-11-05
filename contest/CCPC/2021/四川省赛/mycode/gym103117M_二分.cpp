/**
    N个人赶飞机，距离机场距离均为x，每个人有各自的速度
    初始起飞时间为p0，此后在ti时刻，会宣布起飞时间推迟为pi，一共推迟k次
    如果某人觉得赶不上飞机就会停在原地不动，
    当推迟时间后赶得上了，又会继续前进
    问最后有几个人能赶得上
    很明显速度大总比速度小有优势，可以二分速度
*/
#include <bits/stdc++.h>
using namespace std;

char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)

int getUnsigned(){
	char ch = __hv007();
	while( ch < '0' || ch > '9' ) ch = __hv007();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = __hv007() ) && ch <= '9' ) ret = (ret<<1) + (ret<<3) + (int)(ch-'0');
	return ret;
}

#define pb push_back

typedef long long llt;
int const SIZE = 100100;

int N, K, X;
int Speed[SIZE];
int T[SIZE];
int P[SIZE];

/// speed速度是否能够到达机场
bool check(int speed){
    int left = X;
    int now = 0;

    for(int i=0;i<=K;++i){
        if((P[i]-now)*speed>=left){
            return true;
        }
        now = T[i+1];
    }
    return false;
}

int main(){
    //freopen("1.txt","r",stdin);
    N = getUnsigned();
    K = getUnsigned();
    X = getUnsigned();
    P[0] = getUnsigned();
    for(int i=1;i<=N;++i)Speed[i]=getUnsigned();
    for(int i=1;i<=K;++i)T[i] = getUnsigned();
    for(int i=1;i<=K;++i)P[i] = getUnsigned();

    sort(Speed+1,Speed+N+1);
    int left = 1, right = N, mid;
    do{
        mid = (left+right)>>1;
        if(check(Speed[mid])) right = mid - 1;
        else left = mid + 1;
    }while(left<=right);
    printf("%d\n",N-right);
    return 0;
}
