/*
    POJ3461����׼���ַ���ƥ������
	KMP�㷨
*/
#include <cstdio>
#include <cstring>
using namespace std;
#define SIZE 1000005

void getKMPNext(char const P[],int n,int Next[]){
    Next[0] = -1;
    int i = 0, k = -1;
    while( i < n ){
    	while( k >= 0 && P[i] != P[k] )
    		k = Next[k];
    	++i,++k;
    	if ( i == n ) return;
    	Next[i] = ( P[i] == P[k] ) ? Next[k] : k;
    }
}

int KMP(char const T[],char const P[],int Next[]){
    int ret = 0;
    int const plen = strlen(P);
    int const tlen = strlen(T);
    if ( tlen < plen ) return 0;
    int tp = 0, pp = 0;
    while( tp < tlen ){//�������̣�tp�������� 
    	if ( -1 == pp || T[tp] == P[pp] )++tp,++pp;
    	else pp = Next[pp];
    	if ( plen == pp  ){
    		++ret;//�ҵ�һ����ȫƥ��
    		pp = Next[plen];//�������������������õ�
    	}
    }
    return ret;
}

char P[10001];
char T[SIZE];
int Next[10001];
int main(){
    int nofkase;
    scanf("%d",&nofkase);
    while(nofkase--){
    	scanf("%s%s",P,T);
    	getKMPNext(P,strlen(P)+1,Next);//�����һ��������
    	printf("%d\n",KMP(T,P,Next));
    }
	return 0;
}
