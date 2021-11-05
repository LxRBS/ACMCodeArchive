//��������[a,b]����Լ������������
//������������Ȼ����Լ���ĸ���
#include <iostream>
#include <math.h>
using namespace std;


//����ɸ��
int const SIZE = sqrt(1E9) + 2;//һ��ֻɸ��30000+����
bool isComp[SIZE] = {false};//isComp[i]Ϊ��˵��i�Ǻ���
int P[SIZE];//P[i]Ϊ��i��������i��0��ʼ
int PCnt = 0;//PCnt��¼1~SIZE֮��������ĸ���
void sieve(){
    for(int i=2;i<SIZE;++i){
        if ( !isComp[i] ) P[PCnt++] = i;

        for(int j=0;j<PCnt&&i*P[j]<SIZE;++j){
            isComp[i*P[j]] = true;
            if ( 0 == i % P[j] ) break;
        }
    }
}

int proc(int n){
    int r = 1;
    for(int i=0;i<PCnt&&P[i]*P[i]<=n;++i){
        if ( n % P[i] ) continue;

        int k = 0;
        while( 0 == n % P[i] ) n /= P[i], ++k;
        r *= 1 + k;
    }
    if ( 1 != n ) r *= 2;
    return r;
}

void proc(int a,int b,int&n,int&k){
    k = 0;
    int t;
    for(int i=a;i<=b;++i){
        t = proc(i);
        if ( k < t ) n = i, k = t;
    }
}

int main(){
    sieve();

    int kase,a,b,n,k;
    cin>>kase;
    while(kase--){
        cin>>a>>b;
        proc(a,b,n,k);
        cout<<"Between "<<a<<" and "<<b<<", "<<n<<" has a maximum of "<<k<<" divisors."<<endl;
    }
}
