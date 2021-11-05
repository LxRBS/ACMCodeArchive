#include <cstdio>
#include <cstring>
#define SIZE 1005
typedef long long int llt;
char A[SIZE];
int B[SIZE];
int SA[SIZE];//后缀数组
int wa[SIZE],wb[SIZE],wv[SIZE],ws[SIZE];//临时数组
int cmp(int *r,int a,int b,int l){return r[a]==r[b]&&r[a+l]==r[b+l];}//辅助函数
//倍增算法计算r数组的SA数组，n为r数组的长度，m为r的上界
void da(int r[],int sa[],int n,int m){
	int i,j,p,*x=wa,*y=wb,*t;
	for(i=0;i<m;i++)ws[i]=0;
	for(i=0;i<n;i++)ws[x[i]=r[i]]++;
	for(i=1;i<m;i++)ws[i]+=ws[i-1];
	for(i=n-1;i>=0;i--)sa[--ws[x[i]]]=i;
	for(j=1,p=1;p<n;j*=2,m=p){
		for(p=0,i=n-j;i<n;i++)y[p++]=i;
		for(i=0;i<n;i++)if(sa[i]>=j)y[p++]=sa[i]-j;
		for(i=0;i<n;i++)wv[i]=x[y[i]];
		for(i=0;i<m;i++)ws[i]=0;
		for(i=0;i<n;i++)ws[wv[i]]++;
		for(i=1;i<m;i++)ws[i]+=ws[i-1];
		for(i=n-1;i>=0;i--)sa[--ws[wv[i]]]=y[i];
		for(t=x,x=y,y=t,p=1,x[sa[0]]=0,i=1;i<n;i++)
			x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p-1:p++;
	}
	return;
}

//名次数组与Height数组
int Rank[SIZE],Height[SIZE];
//计算height数组与名次数组，r为源数组，sa为后缀数组，n为r的长度
void calHeight(int r[],int sa[],int n){
	int i,j,k=0;
	for(i=1;i<n;i++)Rank[sa[i]]=i;//原论文使用的是原长度，此处使用的实际是原长度+1
	for(i=0;i<n-1;Height[Rank[i++]]=k)
		for(k?k--:0,j=sa[Rank[i]-1];r[i+k]==r[j+k];k++);
}

llt solve(int n){
	llt ret = 0LL;
	//对每一个长度i，问有没有这种长度的重复子串
	for(int i=1;i<=(n>>1);++i){
		int left = n+100,right = -1; 
        //遍历height数组，查找其连续区间值至少为i的,然后判断是否重叠
		for(int j=2;j<n;++j){
			if ( Height[j] >= i ){//Height[j]表示SA[j-1]和SA[j]的最长公共前缀的长度
                if ( SA[j-1] < left ) left = SA[j-1];
				if ( SA[j-1] > right ) right = SA[j-1];
				if ( SA[j] < left ) left = SA[j];
				if ( SA[j] > right ) right = SA[j];
			}else{//说明一段连续区间已经结束，进行判断
                if ( left != n + 100 && -1 != right && right - left >= i ) ++ret;
				left = n + 100;
				right = -1;
			}
		}
		if ( left != n + 100 && -1 != right && right - left >= i ) ++ret;
	}
	return ret;
}
int main(){
	while(1){
		scanf("%s",A);
		if ( '#' == *A ) return 0;
		int n=0;
        for(;A[n];++n) B[n] = (int)(A[n]);
		B[n++] = 0;
        da(B,SA,n,'z'+1);
		calHeight(B,SA,n);
        printf("%I64d\n",solve(n));
	}
	return 0;
}