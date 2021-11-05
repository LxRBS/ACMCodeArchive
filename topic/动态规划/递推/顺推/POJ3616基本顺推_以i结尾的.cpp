/*
    N��Сʱ��M�����ܵ�ʱ�μ���ʱ���ܹ���õ�milk
    ��ϢR��Сʱ������ٴι���
    ���ܻ�õ����milk
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

struct _t{
    int s,e,g;
}A[1010];
bool operator <(_t const&lhs,_t const&rhs){
    return lhs.e < rhs.e || (lhs.e==rhs.e && lhs.s<rhs.s) || (lhs.s==rhs.s&&lhs.e==rhs.e&&lhs.g>rhs.g);
}

int N,M,R;

void read(){
    N = getUnsigned();
    M = getUnsigned();
    R = getUnsigned();
    for(int i=0;i<M;++i){
        A[i].s = getUnsigned();
        A[i].e = getUnsigned() + R;
        A[i].g = getUnsigned();
    }
    sort(A,A+M);
}

int D[1010];//Di��ʾ��i��β���ܻ�õ����ֵ
void dp(){
    D[0] = A[0].g;
    for(int i=1;i<M;++i){
        int t = 0;
        for(int j=0;j<i;++j){
            if ( A[j].e <= A[i].s ) t = max(t,D[j]);
        }
        D[i] = A[i].g + t;
    }
}

int main(){
    //freopen("1.txt","r",stdin);
    read();
    dp();
    printf("%d\n",*max_element(D,D+M));
    return 0;
}
