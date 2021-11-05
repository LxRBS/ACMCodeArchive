#include <cstdio>
#include <cstring>

char T[300002];
char P[300002*2];

int miniPresent(int len){
	//首先将P重复一次
	for(int i=len;i<len+len;++i)
		P[i] = P[i - len];

	P[len+len] = 0;

	int i = 0,j = 1;//两个指针
	int k = 0;

	while(1){
		//超出以后一定有答案
		if ( i + k >= len || j + k >= len ) break;
		//如果相等往后移位
		if ( P[i+k] == P[j+k] ){
			++k;
			continue;
		}

		//不相等一定i、j中的一个
		if ( P[i+k] > P[j+k] ) i += k + 1;
		else                   j += k + 1;
		k = 0;
		if ( i == j ) ++j;
	}

	return i < j ? i : j;
}

int main(){
	while( EOF != scanf("%s",T) ){
		int len = strlen(T);
		for(int i=0;i<len-1;++i){
			P[i] = T[i+1] - T[i];
			if ( P[i] < 0 ) 
				P[i] += (char)8;
			P[i] += '0';
		}

		P[len-1] = T[0] - T[len-1];
		if ( P[len-1] < 0 ) P[len-1] += (char)8;
		P[len-1] += '0';
		P[len] = 0;

		//最小表示，从ans处开始
		int ans = miniPresent(len);
		P[ans+len] = 0;
		printf("%s\n",P+ans);
	}    
	return 0;
}
