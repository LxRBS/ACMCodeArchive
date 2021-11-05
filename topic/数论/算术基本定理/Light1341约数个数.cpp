/*
    ��֪S=a*b��a<b
    ��֪a����С���ܵ�ֵ
    ��һ���ж�����(a,b)����ab=S

    ���S���ܵ�Լ���ĸ�����һ�룬
    Ȼ���޳���aС��Լ������
*/

#include <stdio.h>
#include <algorithm>
using namespace std;

//����ɸ��
int const SIZE = 1E6+10;//һ��ֻɸ��30000+����
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

typedef long long llt;

int main(){
    //freopen("1.txt","r",stdin);
    sieve();
    int nofkase;
    scanf("%d",&nofkase);

    llt s,a;
    for(int kase=1;kase<=nofkase;++kase){
        scanf("%lld%lld",&s,&a);

        if ( s / a < a ){
            printf("Case %d: 0\n",kase);
            continue;
        }

        //���s��Լ������
        llt ans = 1, ss = s;
        for(int i=0;P[i]*P[i]<=ss&&i<PCnt;++i){
            if ( 0 == ss % P[i] ){
                int k = 0;
                while( 0 == ss % P[i] ) ss /= P[i], ++k;
                ans *= ( k + 1 );
            }
        }

        if ( ss != 1 ) ans <<= 1;
        ans >>= 1;//ֻȡһ�������

        //���С��b��Լ�����������������̫����
        for(int i=1;i<a;++i)if(0==s%i)--ans;

        printf("Case %d: %d\n",kase,ans);
    }
    return 0;
}
