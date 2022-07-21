/**
 * 01��������պ�װ��ʱ��������Ƕ��٣�1024����Ʒ��������1024���������ֵҲ��1024
 * �����þ��䱳������Ϊ�޷���֤���ֵ��������������ֵ������Ʒ��������
 * ��DijkΪ����Ʒi�����Ϊj���õ������Ϊk��Ϊ1��ʾ�д˷�����Ϊ0��ʾû��
 * �� Dijk = D[i-1][j^Wi][k-Vi]
 * �ռ���Թ���������ʱ��Ҫ��ʱ������ʹ��bitset
 * ����ÿһ��Dj(ע��Dj��һ��01����)���൱�ڽ�D[j^wi]����Viλ
 * ����ʱ�临�Ӷ���O(N^3/32)
 * ���ǵ�j�޷�ȷ������������ʵ����ʹ��һ�����е����������й���
 */
#include <bits/stdc++.h>
using namespace std;

char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)

int getInt(){
    int sgn = 1;
    char ch = __hv007();
    while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = __hv007();
    if ( '-' == ch ) {sgn = 0;ch=__hv007();}

    int ret = (int)(ch-'0');
    while( '0' <= (ch=__hv007()) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
    return sgn ? ret : -ret;
}

#ifndef ONLINE_JUDGE
int const SIZE = 1090;
#else
int const SIZE = 1090;
#endif  

using bt = bitset<SIZE>;

bt D[SIZE], T[SIZE];

int N, M;
int V[SIZE], W[SIZE];

int proc(){
    for(int i=0;i<1024;++i) D[i].reset();
    
    D[0][0] = 1;
    for(int i=0;i<N;++i){
        /// ����D����T
        for(int j=0;j<1024;++j){
            T[j] = D[j] << V[i]; 
        }
        /// ����D
        for(int j=0;j<1024;++j){
            D[j] |= T[j^W[i]];
        }
    }
    int ans = -1;
    for(int i=1023;i>=0;--i){
        if(D[i].test(M)){
            ans = i;
            break;
        }
    }
    return ans;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif  
    int nofkase = getInt();
    while(nofkase--){
        N = getInt(); M = getInt();
        for(int i=0;i<N;++i){
            V[i] = getInt();
            W[i] = getInt();
        }
        cout << proc() << endl;
    }
    return 0;
}