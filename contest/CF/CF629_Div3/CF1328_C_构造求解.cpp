/**
 * ����һ��nλ��������x��Ҫ���ҵ�2��nλ��������a��b������
 * a^b = x����max(a,b)������С
 * ������⼴��
 * 0���ÿ���
 * ǰ��2ȫ��ƽ�ּ��ɣ���һ��������1���ͷָ�a
 * �˺�������1��2���ָ�b����
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

char X[60000],A[60000]={'1'},B[60000]={'1'};
int main(){
    //freopen("1.txt","r",stdin);
    int nofkase = getUnsigned();
    while(nofkase--){
        int n = getUnsigned();
        scanf("%s",X);
        char *px = X+1,*pa=A+1,*pb=B+1;
        bool flag = true;
        for(;*px;++px){
            switch(*px){
                case '0':*pa++=*pb++='0';break;
                case '2':{
                    if(flag){
                        *pa++=*pb++='1';
                    }else{
                        *pa++='0';*pb++='2';
                    }
                }break;
                default:{
                    if(flag){
                        flag = false;
                        *pa++='1';*pb++='0';
                    }else{
                        *pa++='0';*pb++='1';
                    }
                }
            }
        }
        *pa=*pb='\0';
        printf("%s\n%s\n",A,B);
    }
    return 0;
}
