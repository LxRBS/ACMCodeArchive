/**
 ����a��b��Ҫ���ҵ����ٵ����ļ��ϣ�ʹ�ã�
 �ü��ϵ�mex��a���ü��ϵ�������b
 ���ȸü�����������a����[0~a-1]��Ȼ�������a����������
 ����ú�Ϊb����𰸾���a������ֻ�����һ����������������Ϊb��
 ���Ǵ�ʱ��Ҫ����һ���£�����ӵ���������ܵ���a��������Ҫ���2������
*/
#include<bits/stdc++.h>
using namespace std;

char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)

int getUnsigned(){
	char ch = __hv007();
	while( ch < '0' || ch > '9' ) ch = __hv007();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = __hv007() ) && ch <= '9' ) ret = (ret<<1) + (ret<<3) + (int)(ch-'0');
	return ret;
}


#define pb push_back
typedef vector<int> vi;

template<typename T>string value2string(const T &t){
    stringstream ss;
    ss<<t;
    return ss.str();
}


#ifndef ONLINE_JUDGE
int const SIZE = 120;
#else
int const SIZE = 300010;
#endif

int Xor[SIZE];

int proc(int a, int b){
    if(a == 1){
        if(!b) return 1;
        return b != 1 ? 2 : 3;
    } 
    if(a != b){
        if(Xor[a-1] == b) return a;
        int tmp = Xor[a-1] ^ b;
        return tmp != a ? a + 1 : a + 2;        
    }
    if(Xor[a-1] == b) return a;
    int tmp = Xor[a-1] ^ b;
    return tmp != a ? a + 1 : a + 2;  
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
#endif
    Xor[0] = 0;
    for(int i=1;i<SIZE;++i) Xor[i] = Xor[i-1] ^ i;

    int nofkase = getUnsigned();
    while(nofkase--){
        int a = getUnsigned();
        int b = getUnsigned();
        printf("%d\n", proc(a, b));
    }
    return 0;
}
