/*
    һ�����֣��ֳ�5�����֣�������ӼӼ��˳�4������
    ���ܹ��õ��������
    ��ȻҪ����������������ܵ�С
    �˷�ֻҪ1λ��1λ���ɣ�����������һλ������λ����������λ����
    �ӷ�ֻ�������������һλ��ʣ�µģ��������һλ��ʣ�µ�
    ��Щ�������ľ��ǽ��
*/
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

typedef long long int llt;
char S[110];

llt f(int idx,int jdx){
    llt ret = 0LL;
    for(char*p=S+idx;p!=S+jdx;++p){
        ret = ret*10LL + (*p-'0');
    }
    return ret;
}

//����Ϊһλ
llt f1(){
    int n = strlen(S);
    llt e = S[n-1]-'0';
    llt d = S[n-2]-'0';
    llt c = S[n-3]-'0';
    llt tmp = c*d/e;
    //����Ӻ�
    llt tt = f(0,n-4) + S[n-4]-'0';
    llt tt2 = *S-'0'+f(1,n-3);
    if(tt<tt2) tt=tt2;
    return tt-tmp;
}
//����Ϊ��λ
llt f2(){
    int n = strlen(S);
    llt e = f(n-2,n);
    llt d = S[n-3]-'0';
    llt c = S[n-4]-'0';
    llt tmp = c*d/e;
    //����Ӻ�
    llt tt = f(0,n-5) + S[n-5]-'0';
    llt tt2 = *S-'0'+f(1,n-4);
    if(tt<tt2) tt=tt2;
    return tt-tmp;
}
//����Ϊ��λ
llt f3(){
int n = strlen(S);
    llt e = f(n-3,n);
    llt d = S[n-4]-'0';
    llt c = S[n-5]-'0';
    llt tmp = c*d/e;
    //����Ӻ�
    llt tt = f(0,n-6) + S[n-6]-'0';
    llt tt2 = *S-'0'+f(1,n-5);
    if(tt<tt2) tt=tt2;
    return tt-tmp;
}
llt proc(){
    int n = strlen(S);

    llt t1 = f1();
    if(n<6) return t1;

    llt t2 = f2();
    if(n<7) return max(t1,t2);

    llt t3 = f3();
    return max(t1,max(t2,t3));
}
int main(){
    int nofkase;
    scanf("%d",&nofkase);
    for(int kase=1;kase<=nofkase;++kase){
        scanf("%s",S);
        printf("Case #%d: %I64d\n",kase,proc());
    }
    return 0;
}
