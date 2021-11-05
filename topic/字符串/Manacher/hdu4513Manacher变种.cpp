/*
    ��������Ӵ�
    ������Ҫ����
    ��ManacherҪ��һ���˽⣬����ģ�岻��
*/
#include <stdio.h>
#include <algorithm>
using namespace std;
int const SIZE = 2000010;

//Manacher�㷨
//src��Դ�ַ�����tmp����ʱ�ַ�����r�ǰ뾶���飬n��Դ�ַ����ĳ���
//tmp��r����������2n
//startΪ����Ŀ�ʼ�ĵط�
//����ֵΪԴ�е�������Ӵ��ĳ���
int Manacher(int const src[],int t[],int r[],int const n,int&start){
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

        //�뾶������1
        r[x+k] = k == r[x] ? 1 : r[x-k];
        //���±��Ƶ�x+k
        x += k;
        //ԭʼ������뾶
        while( t[x+r[x]] == t[x-r[x]] && t[x-r[x]] <= t[x-r[x]+2] ) ++r[x];
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

int N;
int A[SIZE],Tmp[SIZE],R[SIZE];

void read(){
    scanf("%d",&N);
    for(int i=0;i<N;++i) scanf("%d",A+i);
}
int main(){
    int start,nofkase;
    scanf("%d",&nofkase);
    while(nofkase--){
        read();
        printf("%d\n",Manacher(A,Tmp,R,N,start));
    }
    return 0;
}
