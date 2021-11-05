/*
    ��һ����������Ҫ���ɸ�B��S��C
    ����B/S/C������
    �ٸ���B/S/C�ĵ��ۣ�����ʹ������۸�ȥ����
    �ٸ�������ӵ�е�Ǯ
    �����������������
*/
#include <stdio.h>
#include <iostream>
using namespace std;
typedef long long llt;

char T[110];
int Nb,Ns,Nc,Pb,Ps,Pc;
int Cb,Cs,Cc;//һ�����������ĸ����ϵ�����
llt Money;
bool read(){
    if ( ! (cin>>T>>Nb>>Ns>>Nc>>Pb>>Ps>>Pc>>Money) ) return false;

    Cb = Cs = Cc = 0;
    for(char*p=T;*p;++p)if('B'==*p)++Cb;else if('S'==*p)++Cs;else++Cc;
    return true;
}

//����Ƿ�������m������
bool check(llt m){
    llt a = ( m * Cb - Nb ) * Pb;
    if ( a < 0 ) a = 0LL;
    llt b = ( m * Cs - Ns ) * Ps;
    if ( b < 0 ) b = 0LL;
    llt c = ( m * Cc - Nc ) * Pc;
    if ( c < 0 ) c = 0LL;
    return Money >= a + b + c;
}

llt proc(){
    llt mid,left = 0LL, right = 1000000000000LL+100LL;
    
    //���н��С��������ȡ����
    //���ж�����Ϊ��������Ϊright
    do{
        mid = ( left + right ) >> 1;
        if ( check(mid) ) left = mid + 1;
        else right = mid - 1;
    }while( left <= right );
    return right;
}
int main(){
    //freopen("1.txt","r",stdin);
    while( read() ) cout<<proc()<<endl;
    return 0;
}
