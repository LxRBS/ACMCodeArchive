/**
 * ����n���ַ�����n-2��a��2��b����
 * Ҫ�������kС���������ַ���
 * �۲���ɼ���
 * aa
 * aba  aab  ��λ����2��
 * abba abab aabb ��λ����3��
 * abbba ... aabbb ������4��
 * ...
*/
#include <bits/stdc++.h>
using namespace std;
int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

typedef long long int llt;
long long int f(llt k){//����b������
    double x = (sqrt(1.0+8.0*k)-1.0)*0.5 + 1E-4;
    long long int m = (long long int)x;
    if(m*m-m>=k+k) return m-2;
    if(m*m+m>=k+k) return m-1;
    return m;
}
char A[1000010];
int main(){
    //freopen("1.txt","r",stdin);
    int nofkase = getUnsigned();
    while(nofkase--){
        int n = getUnsigned();
        llt k = getUnsigned();
        //m��bǰ��a������
        llt m = f(k);
        //cout<<m<<endl;
        //�������ǰ���a
        int idx=0;
        for(int i=0,t=n-m-2;i<t;++i)A[idx++]='a';
        A[idx++]='b';
        for(llt i=0,t=(m+2)*(m+1)/2-k;i<t;++i)A[idx++]='a';
        A[idx++]='b';
        for(llt i=0,t=m+k-(m+2)*(m+1)/2;i<t;++i)A[idx++]='a';
        A[idx++]='\0';
        printf("%s\n",A);
    }
    return 0;
}
