/*
    ����n�����������ֿ����ظ�����
    ������Щ����ѡȡ�������
    ʹ�����ǵ��������

    ���������Щ�������Ի���
    �����������������޹�
    Ȼ��������Щ�������ֵ
*/
#include <stdio.h>
#include <algorithm>
using namespace std;

typedef long long int llt;

//�ж�value�Ƿ���b�����޹�
//����ǣ���value����b����Ϊ����һ����
int _insertLB(llt value,llt b[],int siz){
    for(int i=siz-1;i>=0;--i){
        if(value&(1LL<<i)){
            if(!b[i]){//value��һ����
                b[i] = value;
                return 1;
            }
            value ^= b[i];
            //value������b�е����ɻ����б��
            if(!value) return 0;
        }
    }
    return 0;
}

//�������Ի�
//a��Դ���飬n��������b�ǽ��,siz�����λ�ټ�1
//���ػ�������
int buildLB(llt const a[],int n,llt b[],int siz){
    fill(b,b+siz,0LL);

    int cnt = 0;
    for(int i=0;i<n;++i){
        cnt += _insertLB(a[i],b,siz);
    }
    return cnt;
}

//�������Ի������ܹ���ɵ������
llt max(llt const b[],int siz){
    llt ret = 0LL,tmp;
    for(int i=siz-1;i>=0;--i){
        if((tmp=ret^b[i])>ret){
            ret = tmp;
        }
    }
    return ret;
}

int N;
llt A[110],B[110];

int main(){
    //freopen("1.txt","r",stdin);
    scanf("%d",&N);
    for(int i=0;i<N;++i)scanf("%lld",A+i);

    buildLB(A,N,B,50);
    printf("%lld\n",max(B,50));
    return 0;
}
