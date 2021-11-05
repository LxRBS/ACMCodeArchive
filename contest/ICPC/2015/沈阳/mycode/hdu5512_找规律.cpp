/**
  1~N��Χ�ڣ���ʼ����{a, b}������������ѡ��
  ��ѡ�������Ǽ������������ĺͻ��߲����ѡ����
  ����ѡ��������t��t=a-b
  ��������������b-t...
  ������𷨣����Ĳ���gcd(a,b)
  ����ܹ�ѡ��������������N/gcd
*/

#include <stdio.h>
#include <string.h>
using namespace std;

int gcd(int a,int b){
    while( b ){
        int r = b;
        b = a % b;
        a = r;
    }
    return a;
}

char A[2][20] = {
    "Iaka","Yuwgna"
};

int main(){
    //freopen("2.txt","r",stdin);
    int nofkase;
    scanf("%d",&nofkase);
    for(int kase=1;kase<=nofkase;++kase){
        int n,a,b;
        scanf("%d%d%d",&n,&a,&b);
        int g = gcd(a,b);
        n /= g;
        printf("Case #%d: %s\n",kase,A[n&1]);
    }
    return 0;
}
