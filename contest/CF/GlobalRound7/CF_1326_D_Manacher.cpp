/**
 * �����ַ���s���ҵ�����ַ���t������
 * 1 t�ĳ��Ȳ�����s
 * 2 t��һ�����Ĵ�
 * 3 t���Է��ֽ�Ϊab������a��s��ǰ׺��b��s�ĺ�׺
 * ���Ƚ�s������β��ȵ��ַ����޳�������s�����: abxyzba��
 * ��ab...ba��һ���ó�������һ�ο϶������ڴ��
 * ������ֻҪ����xyz����
 * ��ʣ�µ��ַ�����ֻ��Ѱ�����ǰ׺������ĺ�׺Ϊ���ĵļ��ɡ�
 * ���Manacher���飬Ȼ���������飬ȡ�����Ǹ����ɡ�
*/
#include <bits/stdc++.h>
using namespace std;

//Manacher�㷨
//src��Դ�ַ�����tmp����ʱ�ַ�����r�ǰ뾶���飬n��Դ�ַ����ĳ���
//tmp��r����������2n
//startΪ����Ŀ�ʼ�ĵط�
//����ֵΪԴ�е�������Ӵ��ĳ���
int Manacher(char const src[],char t[],int r[],int const n){
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

    return 0;
}

#ifndef ONLINE_JUDGE
int const SIZE = 12;
#else
int const SIZE = 1000010;
#endif

char A[SIZE],Tmp[SIZE<<1];
int R[SIZE<<1];

//��ǰ�������������
int f(int n){
    //��һ������������i-ri==0
    int ans = 2;
    n = n + n + 2;
    for(int i=n-1;i>=2;--i)if(i==R[i]){ans=i;break;}
    return ans - 1;
}

int g(int n){
    //����2n+2==i+ri
    int ans = n+n+1;
    for(int i=1;i<=n+n+1;++i)if(n+n+2==i+R[i]){ans=i;break;}
    return R[ans]-1;
}
int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
#endif
    int kase;
    scanf("%d",&kase);
    while(kase--){
        scanf("%s",A);
        int n = strlen(A);
        int k = 0;
        while(k<n/2&&A[k]==A[n-k-1])++k;
        if(k==n/2){
            printf("%s\n",A);
            continue;
        }
        int m = n - k - k;
        Manacher(A+k,Tmp,R,m);
        int a = f(m);
        int b = g(m);
        if(a>=b){
            A[k+a]='\0';
            printf("%s%s\n",A,A+n-k);
        }else{
            A[k] = '\0';
            printf("%s%s\n",A,A+n-k-b);
        }
    }
    return 0;
}
