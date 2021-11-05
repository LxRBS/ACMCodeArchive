/**
    Manacher�㷨ģ����
*/
#include <bits/stdc++.h>
using namespace std;

int const SIZE = 21000010;

//Manacher�㷨
//src��Դ�ַ�����tmp����ʱ�ַ�����r�ǰ뾶���飬n��Դ�ַ����ĳ���
//tmp��r����������2n
//startΪ����Ŀ�ʼ�ĵط�
//����ֵΪԴ�е�������Ӵ��ĳ���
int Manacher(char const src[],char t[],int r[],int const n,int&start){
    //Ԥ����s�м��������ַ���ͷǰ���벻һ�����ַ�ȷ���жϲ���Խ��
    t[0] = -1;
    t[1] = -2;
    int total = 2;
    for(int i=0;i<n;++i) t[total++] = src[i], t[total++] = -2;
    t[total] = 0;//��β

    //��ʼ��
    r[0] = r[1] = 1;

    //x������¼�������r���±����
    int x = 1,k;
    while( x < total ){
        for(k=1;k<r[x];++k){
            if ( k + r[x-k] == r[x] ) break;
            r[x+k] = min(r[x-k],r[x]-k);
        }

        //�뾶������1����r[x-k]
        r[x+k] = k == r[x] ? 1 : r[x-k];
        //���±��Ƶ�x+k
        x += k;
        //ԭʼ������뾶��ע���ʱx�����Ѿ�������Χ�������鿪��һ���ʼ��Ϊ0����
        while( t[x+r[x]] == t[x-r[x]] ) ++r[x];
    }

    //������ĵĳ����Լ���ʼλ��
    int ret = 0;
    start = 0;
    for(int i=0;i<total;++i){
        int tt = r[i] - 1;
        if ( ret < tt ) ret = tt, start = ( i - ret ) >> 1;
    }
    return ret;
}

char A[SIZE],T[SIZE];
int R[SIZE];
int main(){
    //freopen("1.txt","r",stdin);
    scanf("%s",A);
    int start;
    printf("%d\n",Manacher(A,T,R,strlen(A),start));
    return 0;
}
