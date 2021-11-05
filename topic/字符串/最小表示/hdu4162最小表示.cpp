#include <cstdio>
#include <cstring>

char T[300002];
char P[300002*2];

int miniPresent(int len){
	//���Ƚ�P�ظ�һ��
	for(int i=len;i<len+len;++i)
		P[i] = P[i - len];

	P[len+len] = 0;

	int i = 0,j = 1;//����ָ��
	int k = 0;

	while(1){
		//�����Ժ�һ���д�
		if ( i + k >= len || j + k >= len ) break;
		//������������λ
		if ( P[i+k] == P[j+k] ){
			++k;
			continue;
		}

		//�����һ��i��j�е�һ��
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

		//��С��ʾ����ans����ʼ
		int ans = miniPresent(len);
		P[ans+len] = 0;
		printf("%s\n",P+ans);
	}    
	return 0;
}
