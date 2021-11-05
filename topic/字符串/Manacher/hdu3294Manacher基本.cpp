/*
    ���ַ�����һ����ĸ����ĸ��ӳ��
    Ȼ����������Ӵ� 
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

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
        //ԭʼ������뾶
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

char Dic[128];
void f(char ch){
    for(int i=0;i<26;++i){
        int idx = i + ch;
        if ( idx > 'z' ) idx = idx - 'z' - 1 + 'a';
        Dic[idx] = 'a' + i;
    }
}
int const SIZE = 200010;
int N;
char C[3];
char A[SIZE],T[SIZE<<1];
int R[SIZE<<1];
int main(){
    while( EOF != scanf("%s%s",C,A) ){
        f(*C);
        N = strlen(A);

        int start;
        int n = Manacher(A,T,R,N,start);

        if ( 1 == n ){
            printf("No solution!\n");
        }else{
            printf("%d %d\n",start,n+=start-1);
            for(int i=start;i<=n;++i) putchar(Dic[(int)A[i]]);
            printf("\n");
        }
    }
    return 0;
}
