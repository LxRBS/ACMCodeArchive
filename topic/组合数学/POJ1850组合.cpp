#include <iostream>
using namespace std;

int C[27][27] = {0};

//���������
void init(){
	for(int i=0;i<27;++i)for(int j=0;j<=i;++j){
		if ( 0 == j || i == j ) C[i][j] = 1;
		else                    C[i][j] = C[i-1][j-1] + C[i-1][j];
	}
	C[0][0] = 0;
}

int main(){
	init();

	char word[16];
	while( EOF != scanf("%s",word) ){
        int len = 1;
		//����Ƿ�����
		bool flag = true;
		while( word[len] ){
			if ( word[len] <= word[len-1] ){
				flag = false;
				break;
			}
			++len;
		}

		if ( !flag ){
			printf("0\n");
			continue;
		}

		int sum = 0;
		//�����str�̵��ַ�������
		for(int i=1;i<len;++i) sum += C[26][i];//�ù�ʽ����ѧ�Ƶ�
		//������strһ������������ǰ��ĸ���
		for(int i=0;i<len;++i){
			char ch;
			if ( 0 == i ) ch = 'a';
			else          ch = word[i-1]+1;

			while( ch < word[i] ){
				sum += C['z'-ch][len-1-i];
				++ch;
			}
		}

		printf("%d\n",++sum);
	}
	return 0;
}