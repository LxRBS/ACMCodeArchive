/**
    ����A��ʾ��N��Ȩֵ
	����B��ʾ��ӦAiȨֵ��Bi��
	���ڴ�A0��ʼ����������ȡ���ɸ�Ȩֵ
	A0����ȡ�⣬�ʴ������ȡ�ߵ����Ȩֵ
	��A��һ��ǰ׺��S����ʼ����Ϊ[0,N-1]��
	��already��¼�Ѿ�ȡ�ߵĸ��� 
	ÿ��������[0, right]���ҵ�����Sj
	���ڸ��������ҵ���С��Bi�� 
	����ans��������Sj*(Bi-already)
	Ȼ��right��Ϊi-1,already��ΪBi��������һ��
	��Ϊ���ֵ����Сֵ���ǲ���ģ�����ʹ��SparseTable 
    ÿ�β�ѯ����0��ʼ�����Բ���ST��ֱ��һ�����鼴��
    ���ע��ᳬlonglong��Χ����Ҫ��int128��������devcpp
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long llt;
typedef __int128_t llllt;

int getInt(){
	int sgn = 1;
	char ch = getchar();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = getchar();
	if ( '-' == ch ) {sgn = 0;ch=getchar();}

	int ret = (int)(ch-'0');
	while( '0' <= (ch=getchar()) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return sgn ? ret : -ret;
}

int const SIZE = 100010;
int A[SIZE],B[SIZE];
llt S[SIZE];

int STMax[SIZE][20];
int STMin[SIZE][20];

int STMax2[SIZE];
int STMin2[SIZE];

void sparseTable(int n){
	/*��Ϊ���Ǵ�0��ʼ��ѯ�����Բ���ST 
	for(int i=0;i<n;++i)STMax[i][0]=STMin[i][0]=i;
	for(int j=1,tmp;(tmp=1<<j)<=n;++j)for(int i=0;i+tmp<=n;++i){
		STMax[i][j] = S[STMax[i][j-1]] > S[STMax[i+(tmp>>1)][j-1]] ? STMax[i][j-1] : STMax[i+(tmp>>1)][j-1];
		STMin[i][j] = B[STMin[i][j-1]] <= B[STMin[i+(tmp>>1)][j-1]] ? STMin[i][j-1] : STMin[i+(tmp>>1)][j-1];
	}//*/	
	STMax2[0] = STMin2[0];
	for(int i=1;i<n;++i){
		STMax2[i] = S[STMax2[i-1]] > S[i] ? STMax2[i-1] : i;
		STMin2[i] = B[STMin2[i-1]] <= B[i] ? STMin2[i-1] : i;
	}
}

//����[s, e]�ļ���ֵ���� 
inline int qMax(int s,int e,int n){//s��Ȼ��0 
	/* 
	int k = (int)(log(double(e-s+1))/log(2.0));
	return S[STMax[s][k]] > S[STMax[e-(1<<k)+1][k]]	? STMax[s][k] : STMax[e-(1<<k)+1][k];
	//*/
	return STMax2[e];
}

inline int qMin(int s,int e,int n){
	/*
	int k = (int)(log(double(e-s+1))/log(2.0));
	return B[STMin[s][k]] <= B[STMin[e-(1<<k)+1][k]] ? STMin[s][k] : STMin[e-(1<<k)+1][k];
	//*/
	return STMin2[e];
}

llllt f(int n){
    S[0] = A[0];
	for(int i=1;i<n;++i)S[i]=S[i-1]+A[i];
	
	sparseTable(n);		
	
	llllt ans = 0;
	int already = 0;
	int right = n - 1;
	while(right>=0){
		int idx = qMax(0,right,n);
		int jdx = qMin(0,right,n);
		ans += (llllt)S[idx] * (llllt)(B[jdx]-already);
		right = jdx - 1;
		already = B[jdx];
	}
	return ans;
}

void output(ostream&os,llllt const&a){
	if(a>9)output(os,a/10);
	os<<(int)(a%10);
}

ostream& operator << (ostream&os, llllt const&a){
	if(a<0){
		os<<"-";output(os,-a);
	}else{
		output(os,a);
	}
	return os;	
}

int main(){
    //freopen("1.txt","r",stdin);
    //freopen("2.txt","w",stdout);
    int nofkase = getInt();
    for(int kase=1;kase<=nofkase;++kase){
        int n = getInt();
        for(int i=0;i<n;++i)A[i]=getInt();
        for(int i=0;i<n;++i)B[i]=getInt();
        cout<<"Case #"<<kase<<": "<<B[0]<<" "<<f(n)<<endl;
    }
    return 0;
}

