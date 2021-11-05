/*
    给定字符串P，一定有 P = a^n，其中a是某一个字符串，求最大的n
	例如：
	    输入：aaaa
		输出：4
*/
#include <string>
#include <iostream>
#include <cstring>

using namespace std;

/*  
求给定模式的特征向量
arg1：模式P，C char*类型
arg2：特征向量数组，特征向量保存在该数组中
arg3：模式P的长度，也是特征向量数组的有效长度
*/
bool getNext(char const P[],int next[],int n){
	int i,k;
	next[0] = 0;
	for ( i=1;i<n;i++ ){
		k = next[i-1];
		while( k > 0 && P[i] != P[k]  )
			k = next[k-1];
		if ( P[i] == P[k] ) next[i] = k + 1;
		else next[i] = 0;
	}
	return true;
}

#define  SIZE 1000001
#define CLEAR_ADDR(addr) ( memset( (addr) , 0 , sizeof( (addr) ) ) )

char P[SIZE];
int next[SIZE];

int main(){
    int i;
	int len;
	int n;
	int k;
	while( scanf("%s",P) ){
		if ( P[0] == '.' && P[1] == 0 ) return 0;
		len = strlen(P);
		getNext(P,next,len+1);
        k = len - next[len-1];     /*如果能够成某次方，则后移位数比能被长度整除*/
		if ( len % k == 0 ) printf("%d\n",len/k);
		else                printf("1\n");
	}
	return 0;
}
