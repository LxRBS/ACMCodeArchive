#include <cstdio>
#include <cstring>
char A[20];
int B[20][20];
void disp(){
	for(int i=0;i<strlen(A);++i){
		for(int j=i;j<strlen(A);++j)
		    printf("%8d",B[i][j]);
		printf("\n");
	}
}
int f(char const a[],int i,int j){
	int r = 0;
	for(int k=i;k<=j;++k)
	    r = r * 10 + ( a[k] - '0' );
	return r;
}

bool read(){
	scanf("%s",A);
	if ( 'E' == *A ) return false;
	
	for(int i=0;i<strlen(A);++i)for(int j=i;j<strlen(A);++j){
		B[i][j] = f(A,i,j);
	}
	return true;
}
int Ans = 0;

void dfs2(int current_pos,int target_sum,int sum){
	if ( current_pos == strlen(A) ){
		if ( target_sum == sum ) ++Ans;
		return;
	}
	//��һ�����ĳ��� 
	for(int i=1;i<=strlen(A)-current_pos;++i)
	    dfs2(current_pos+i,target_sum,sum+B[current_pos][current_pos+i-1]);
}

void dfs1(int current_pos,int end_pos,int sum){
	if ( current_pos > end_pos ){
		//����ұߣ����ܷ񹹳�sum
		dfs2(end_pos+1,sum,0);
		return; 
	}
	
	//��һ�����ĳ��� 
	for(int i=1;i<=end_pos+1-current_pos;++i){
		dfs1(current_pos+i,end_pos,sum+B[current_pos][current_pos+i-1]);
	}
}
void proc(){
	Ans = 0;
	//ö�ٵȺŵ�λ��
	for(int pos=0;pos<strlen(A)-1;++pos){
		//��ÿһ���Ⱥţ��������ܹ����ɵĺ�ֵ
		dfs1(0,pos,0); 
	} 
	printf("%d\n",Ans);
}
int main(){
    while( read() ) proc();	
	return 0;
}
