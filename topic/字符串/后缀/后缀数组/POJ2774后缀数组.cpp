/*
    给定2个字符串，求最长公共子串
*/
#include <stdio.h>
#include <string.h>

#define SIZE 200002

#define F(x) ((x)/3+((x)%3==1?0:tb))
#define G(x) ((x)<tb?(x)*3+1:((x)-tb)*3+2)

int wa[SIZE],wb[SIZE],wv[SIZE],ws[SIZE];

int c0(int *r,int a,int b){
	return r[a] == r[b]
	&& r[a+1] == r[b+1]
	&& r[a+2] == r[b+2];
}
int c12(int k,int *r,int a,int b){
	if(k==2) return r[a] < r[b]
	|| r[a] == r[b]
	&& c12(1,r,a+1,b+1);
	return r[a] < r[b]
	|| r[a] == r[b]
	&& wv[a+1] < wv[b+1];
}
void sort(int *r,int *a,int *b,int n,int m){
	int i;
	for(i=0;i<n;i++) wv[i]=r[a[i]];
	for(i=0;i<m;i++) ws[i]=0;
	for(i=0;i<n;i++) ws[wv[i]]++;
	for(i=1;i<m;i++) ws[i]+=ws[i-1];
	for(i=n-1;i>=0;i--) b[--ws[wv[i]]]=a[i];
	return;
}
//r和sa需要有3倍的空间
//n是数组长度
//m是数组的取值个数，一般比实际取值的个数多1
void dc3(int *r,int *sa,int n,int m){
	int i,j,*rn=r+n,*san=sa+n,ta=0,tb=(n+1)/3,tbc=0,p;
	r[n]=r[n+1]=0;
	for(i=0;i<n;i++) if(i%3!=0) wa[tbc++]=i;
	sort(r+2,wa,wb,tbc,m);
	sort(r+1,wb,wa,tbc,m);
	sort(r,wa,wb,tbc,m);
	for(p=1,rn[F(wb[0])]=0,i=1;i<tbc;i++)
		rn[F(wb[i])]=c0(r,wb[i-1],wb[i])?p-1:p++;
	if(p<tbc) dc3(rn,san,tbc,p);
	else for(i=0;i<tbc;i++) san[rn[i]]=i;
	for(i=0;i<tbc;i++) if(san[i]<tb) wb[ta++]=san[i]*3;
	if(n%3==1) wb[ta++]=n-1;
	sort(r,wb,wa,ta,m);
	for(i=0;i<tbc;i++) wv[wb[i]=G(san[i])]=i;
	for(i=0,j=0,p=0;i<ta && j<tbc;p++)
		sa[p]=c12(wb[j]%3,r,wa[i],wb[j])?wa[i++]:wb[j++];
	for(;i<ta;p++) sa[p]=wa[i++];
	for(;j<tbc;p++) sa[p]=wb[j++];
	return;
}

int rank[SIZE],height[SIZE];

void calheight(int *r,int *sa,int n)
{
	int i,j,k=0;
	for(i=1;i<n;i++) rank[sa[i]]=i;//原论文使用源数组的长度,此处使用经过+1以后的长度
	for(i=0;i<n-1;height[rank[i++]]=k)//所以上一行不使用小于等于而用小于，这一行用n-1而不用n
		for(k?k--:0,j=sa[rank[i]-1];r[i+k]==r[j+k];k++);
	return;
}

char Str[SIZE/2];

int R[SIZE*3];
int Sa[SIZE*3];


int main(){
	int len0,len1;
	int i;
	int ans = 0;

	scanf("%s",Str);

	len0 = strlen(Str);
    for(i=0;i<len0;i++) R[i] = Str[i] - 'a' + 1;
	R[len0] = 27;

	scanf("%s",Str);
    for(i=0;Str[i];i++) R[len0+1+i] = Str[i] - 'a' + 1;
	R[len1=len0+1+i] = 0;
	len1++;

	dc3(R,Sa,len1,28);
	calheight(R,Sa,len1);


	for(i=2;i<len1;i++){
		if( Sa[i-1] < len0 && Sa[i] > len0 
			|| Sa[i-1] > len0 && Sa[i] < len0 )
			if ( ans < height[i] )
			    ans = height[i];
	}

	printf("%d\n",ans);

	return 0;
}