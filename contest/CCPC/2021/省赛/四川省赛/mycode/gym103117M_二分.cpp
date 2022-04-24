/**
    N���˸Ϸɻ���������������Ϊx��ÿ�����и��Ե��ٶ�
    ��ʼ���ʱ��Ϊp0���˺���tiʱ�̣����������ʱ���Ƴ�Ϊpi��һ���Ƴ�k��
    ���ĳ�˾��øϲ��Ϸɻ��ͻ�ͣ��ԭ�ز�����
    ���Ƴ�ʱ���ϵ����ˣ��ֻ����ǰ��
    ������м������ܸϵ���
    �������ٶȴ��ܱ��ٶ�С�����ƣ����Զ����ٶ�
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

/// speed�ٶ��Ƿ��ܹ��������
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
