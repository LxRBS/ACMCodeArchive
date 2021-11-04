/**
 * 给定一个n位三进制数x，要求找到2个n位三进制数a和b，满足
 * a^b = x，且max(a,b)尽可能小
 * 构造求解即可
 * 0不用考虑
 * 前导2全部平分即可，第一个遇到的1，就分给a
 * 此后遇到的1和2都分给b即可
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
