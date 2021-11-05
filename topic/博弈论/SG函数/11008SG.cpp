#include <iostream>
#include <algorithm>
#include <set>
#include <cstring>
using namespace std;

//����������״̬������Ϊ���棬����ֵΪ״̬
int encode(int const a[]){
    int ret = 0;
	for(int i=5;i>=0;--i)
        ret = ret * 5 + a[i];
	return ret;
}
//����״̬������
void decode(int st,int a[]){
	for(int i=0;i<6;++i){
		a[i] = st % 5;
		st = st / 5;
	}
	return;
}
//�������
int sigma(int const a[]){
	return a[0] * 1 + a[1] * 2 + a[2] * 3 
	    + a[3] * 4 + a[4] * 5 + a[5] * 6;
}

int Sg[15625] = {0};
int St[6] = {0};

int dp(){
    int s = encode(St);
    if ( -1 != Sg[s] ) return Sg[s];
	if ( sigma(St) >= 31 ) return 0;

	//��ÿһ������״̬
	bool flag[8] = {false};
	for(int i=0;i<6;++i){
		if ( 4 == St[i] ) continue;

		++St[i];

		if ( sigma(St) > 31 ){
		    --St[i];
			continue;
		}

        flag[dp()] = true;
		--St[i];
	}

	int x = 0;
	for(;x<8;++x)if(!flag[x])break;
	return Sg[s] = x;
}

char Input[25];
int main(){
	fill(Sg,Sg+15625,-1);

	while( EOF != scanf("%s",Input) ){
		fill(St,St+6,0);

		for(int i=0;i<strlen(Input);++i){
			int x = ( Input[i] - '0' ) - 1;
            ++St[x];
		}

		//��������ΪB��ż��ΪA
		char winner = ( strlen(Input) & 1 ) ? 'B' : 'A';
		
		//���SGֵΪ0�����ֱذ�
		if ( 0 == dp() ) winner = 'B' - winner + 'A';

		printf("%s %c\n",Input,winner);
	}

	return 0;
}