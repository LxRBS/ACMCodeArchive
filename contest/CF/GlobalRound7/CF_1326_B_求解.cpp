/**
 * ��������A���ٸ�������X������Xi=max(0, A1...A[i-1])
 * �ٸ�������B����Bi=Ai-Xi
 * ������֪����B��Ҫ���Ƴ�����A
 * 
 * ��������xΪ��ǰA��������ֵ����ʼΪ0��
 * ����Ai=Bi+x����
*/
#include <bits/stdc++.h>
using namespace std;

int getInt(){
	int sgn = 1;
	char ch = getchar();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = getchar();
	if ( '-' == ch ) {sgn = 0;ch=getchar();}

	int ret = (int)(ch-'0');
	while( '0' <= (ch=getchar()) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return sgn ? ret : -ret;
}

int const SIZE = 220000;
int B[SIZE];
int main(){
    //freopen("1.txt","r",stdin);
    int n = getInt();
    int mmax = 0;
    for(int i=0;i<n;++i){
        int b = getInt();
        int a = b + mmax;
        printf("%d ", a);
        if(a>mmax) mmax = a;
    }
    printf("\n");
    return 0;
}
