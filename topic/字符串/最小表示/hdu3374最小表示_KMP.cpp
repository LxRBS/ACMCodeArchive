//��С��ʾ������ʾ���ֵ�λ���Լ����ֵĴ���
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

//��src������KMPƥ�������������nΪsrc�ĳ���
void getKMPNext(char const src[],int n,int next[]){
    next[0] = -1;
    int i = 0, k = -1;
    while( i < n ){
        while( k >= 0 && src[i] != src[k] ) k = next[k];
        ++i, ++k;
        if ( i == n ) return;
        next[i] = src[i] == src[k] ? next[k] : k;
    }
}


//��P��T�г��ֵĴ����������ص���next�ĳ���Ҫ����pn+1
int KMPCount(char const T[],int tn,char const P[],int pn,int const next[]){
    if ( pn > tn ) return 0;
    int tp = 0, pp = 0, ret = 0;
    while( tp < tn ){
        if ( -1 == pp || T[tp] == P[pp] ) ++tp, ++pp;
        else pp = next[pp];
        if ( pp == pn ){
            ++ret;
            pp = next[pn];
        }
    }
    return ret;
}

int const SIZE = 1000010;

//������С��ʾ��s�е���ţ�s���Ѿ��ظ����ε��ַ���
//nΪδ�ظ�֮ǰ�ĳ���
int miniPre(char const s[],int n){
    int i = 0, j = 1;
    int k = 0;
    while( 1 ){
    	while( s[i+k] == s[j+k] && k < n ) ++k;
    	if ( k == n )return i;//�˴��ɷ���i��j����һ��
    	if ( s[i+k] > s[j+k] ) i += k + 1;
    	else j += k + 1;
    	if ( i >= n || j >= n ) return i < j ? i : j;//�˴�Ҫ����С��
    	if ( i == j ) ++j;//ǿ��j����һλ
    	k = 0;
    }
    return -1;//���ﲻ�ᵽ��
}

//��������ʾ��s�е���ţ�s���Ѿ��ظ����ε��ַ���
//nΪδ�ظ�֮ǰ�ĳ���
int maxiPre(char const s[],int n){
    int i = 0, j = 1;
    int k = 0;
    while( 1 ){
    	while( s[i+k] == s[j+k] && k < n ) ++k;
    	if ( k == n )return i;//�˴��ɷ���i��j����һ��
    	if ( s[i+k] < s[j+k] ) i += k + 1;
    	else j += k + 1;
    	if ( i >= n || j >= n ) return i < j ? i : j;//�˴�Ҫ����С��
    	if ( i == j ) ++j;//ǿ��j����һλ
    	k = 0;
    }
    return -1;//���ﲻ�ᵽ��
}

char A[SIZE<<1],B[SIZE];
int Next[SIZE];

int main(){
    while( EOF != scanf("%s",A) ){
        int n = strlen(A);
        copy(A,A+n,A+n);
        A[n+n] = '\0';

        //����С��ʾ
        int mins = miniPre(A,n);
        //������С��ʾ
        copy(A+mins,A+mins+n,B);
        B[n] = '\0';
        //������С��ʾ���ֵĴ�����ע��A�ĳ���ȡ2n-1
        getKMPNext(B,n+1,Next);
        int minc = KMPCount(A,n+n-1,B,n,Next);

        //������ʾ
        int maxs = maxiPre(A,n);
        //��������ʾ
        copy(A+maxs,A+maxs+n,B);
        B[n] = '\0';
        //��������ʾ���ֵĴ�����ע��A�ĳ���ȡ2n-1
        getKMPNext(B,n+1,Next);
        int maxc = KMPCount(A,n+n-1,B,n,Next);

        printf("%d %d %d %d\n",mins+1,minc,maxs+1,maxc);
    }
    return 0;
}

