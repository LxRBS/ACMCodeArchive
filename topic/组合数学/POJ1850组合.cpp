#include <iostream>
using namespace std;

int C[27][27] = {0};

//生成组合数
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
		//检查是否升序
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
		//计算比str短的字符串个数
		for(int i=1;i<len;++i) sum += C[26][i];//该公式由数学推导
		//计算与str一样长但是在它前面的个数
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