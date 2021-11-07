/**
    数组A表示有N个权值
	数组B表示对应Ai权值有Bi个
	现在从A0开始往后连续的取若干个权值
	A0必须取光，问此情况下取走的最大权值
	对A求一个前缀和S，初始区间为[0,N-1]，
	令already记录已经取走的个数 
	每次在区间[0, right]中找到最大的Sj
	再在该区间中找到最小的Bi， 
	则本轮ans可以增加Sj*(Bi-already)
	然后将right改为i-1,already改为Bi，进行下一轮
	因为最大值与最小值都是不变的，可以使用SparseTable 
    每次查询均从0开始，可以不用ST，直接一个数组即可
    最后注意会超longlong范围，需要用int128，可以用devcpp
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
	/*因为总是从0开始查询，可以不用ST 
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

//区间[s, e]的极大值坐标 
inline int qMax(int s,int e,int n){//s必然是0 
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

