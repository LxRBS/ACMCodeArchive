/**
   ��һ���ַ��������Ƿ��ܹ��ָ�Ϊ���ɳ��ȴ���1��ѭ��ͬ�����Ӵ�
   ���ȱ�Ȼ��Լ����Ȼ���ÿ��Լ�����ѭ��ͬ������
   ������
*/
//#include <bits/stdc++.h>
#include <stdio.h>
using namespace std;

typedef long long llt;

//����ɸ��
int const SIZE = 5000010;//һ��ֻɸ��30000+����
bool isComp[SIZE] = {false};//isComp[i]Ϊ��˵��i�Ǻ���
int P[SIZE];//P[i]Ϊ��i��������i��0��ʼ
int PCnt = 0;//PCnt��¼1~SIZE֮��������ĸ���
void sieve(){
    for(int i=2;i<SIZE;++i){
        if ( !isComp[i] ) P[PCnt++] = i;

        for(int j=0;j<PCnt&&(llt)i*P[j]<SIZE;++j){
            isComp[i*P[j]] = true;
            if ( 0 == i % P[j] ) break;
        }
    }
}

int N;
char A[SIZE];

bool checkSingle(){
    char const *p = A + 1;
    while(*p)if(*p!=*A)return false;else ++p;
    return true;
}

//���[start1,len+start1)��[start2,len+start2)�Ƿ�Ϊѭ��ͬ��
bool check(int start1,int start2,int len){
    int n1 = start1 + len;
    int n2 = start2 + len;
    int i = 0, j = 0;
    int k = 0;
    while(i<n1&&j<n2){
        while(A[start1+(i+k)%len]==A[start2+(j+k)%len]&&k<len) ++k;
        if(k==len) return true;
        if(A[start1+(i+k)%len]>A[start2+(j+k)%len]) i += k + 1;
        else j += k + 1;
        k = 0;
    }
    return false;
}

//����Ƿ����k-ͬ��
bool check(int k){
    for(int i=k;i<N;i+=k){
        if(!check(0,i,k)) return false;
    }
    return true;
}

bool proc(){
    if(1==N) return false;
    if(2==N) return *A == *(A+1);
    if(checkSingle()) return true;
    if(!isComp[N]) return false;

    int nn = N;
    for(llt i=2;i*i<=N;++i){
        if(N%i==0){
            if(check(i)) return true;
            if(check(N/i)) return true;
        }
    }
    return false;
}

int main(){
    //freopen("1.txt","r",stdin);
    sieve();
    int nofkase;
    scanf("%d",&nofkase);
    while(nofkase--){
        scanf("%d%s",&N,A);
        puts(proc()?"Yes":"No");
    }
    return 0;
}
