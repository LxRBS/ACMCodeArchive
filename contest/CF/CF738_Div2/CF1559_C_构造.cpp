/**
    N+1�����ͼ��1~N֮�������бߡ� 
    �ٸ���һ��N���ȵ�01����AiΪ0��ʾi��N+1�бߣ�Ϊ1��ʾN+1��i�б�
    Ҫ�����һ������˳��ʹ��1~N+1��������ֻ����һ��
    �ҵ����һ��0��λ�ã��ߵ�N+1��Ȼ���߻���
    Pos���ǳ�ʼ���ˡ�����������
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

int N;
int A[11110];
int Pos;

int main(){
    //freopen("1.txt","r",stdin);
    int nofkase = getUnsigned();
    while(nofkase--){
        N = getUnsigned();
        Pos = 0;
        for(int i=1;i<=N;++i){
            if(0==(A[i] = getUnsigned())){
                Pos = i;
            }
        }
        for(int i=1;i<=Pos;++i)printf("%d ", i);
        printf("%d ", N+1);
        for(int i=Pos+1;i<=N;++i)printf("%d ", i);
        printf("\n");
    }
    return 0;
}

