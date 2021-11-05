//��״���飬156ms��1048k��1651B
#include <iostream>
#include <cstring>
using namespace std;

#define SIZE 100004

//��״����
int C[SIZE] = {0};

//Դ����
int A[SIZE] = {0};

//����x�Ķ�����λ�����λ1�������ֵ
int lowbit(int x){
    return x & ( x ^ ( x - 1 ) );
}

//���£�����idx�ڵ�ֵ����v
//��״�����ܳ���Ϊn���±귶Χ��1��n
void update(int idx,int v,int n){
	while( idx <= n ){
	    C[idx] += v;
		idx += lowbit(idx);
	}
}

//��ǰx�����
int sum(int x){
    int sum = 0;
	while( x > 0 ){
	    sum += C[x];
		x -= lowbit(x);
	}
    return sum;
}

//��¼���Ҵ�С����
int L_G[SIZE],L_L[SIZE];
int R_G[SIZE],R_L[SIZE];

int main(){
    int tofkase;
	scanf("%d",&tofkase);
	while(tofkase--){
	    int n;
		scanf("%d",&n);

		//����Դ����
		for(int i=1;i<=n;++i)
			scanf("%d",A+i);

		//�����״����
		memset(C,0,sizeof(C));

		//�������ҽ���������״���飬ÿһ�������е�ֵ����ӳ�˵�i������ߵ����
		for(int i=1;i<=n;++i){
			//��A[i]Ϊ�±꣬���±괦+1
			//���б�A[i]С������ָʾ�Ľڵ㶼���ᷢ���ı�
		    update(A[i],1,SIZE);

			//A[i]���һ���ж��ٸ�1����͵õ������Ǳ�A[i]С�����ĸ���
			L_L[i] = sum( A[i] - 1 );
            //sum(SIZE)�����е����ĸ���(i�����),sum(A[i])������С�ڵ���A[i]�����ĸ���
			L_G[i] = sum( SIZE ) - sum( A[i] );
		}

		//�����״����
		memset(C,0,sizeof(C));

		//����������������״����
		for(int i=n;i>=1;--i){
		    update(A[i],1,SIZE);
            R_L[i] = sum( A[i] - 1 );
			R_G[i] = sum( SIZE ) - sum( A[i] );
		}

		long long ans = 0;
		for(int i=1;i<=n;++i)
			ans += L_L[i] * R_G[i] + L_G[i] * R_L[i];

		printf("%I64d\n",ans);
	}
	return 0;
}