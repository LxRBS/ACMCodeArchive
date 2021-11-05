/*
    给定一个整数串，求不重叠的最长重复子串
	  这道题目认为：如果两个串的每一个字母都相差一个固定值，两串是相等的，因为这道题目的背景是音乐的旋律
    204ms
*/

#include <iostream>
#include <cstring>
void dispArray(int const array[],int n){
	int i;
	for(i=0;i<n;i++){
		if ( i % 5 == 0 ) printf("\n");
		printf("%-5d",array[i]);
	}
	if ( i % 5 == 1 ) printf("\n");
	printf("\n");
	return ;
}
#define CLEAR(addr) memset((addr),0,sizeof((addr)))
#define  SIZE 20002
#define  RANGE 89
bool cmp(int *r,int a,int b,int len){
	return r[a] == r[b] && r[a+len] == r[b+len];
}
int const maxn = SIZE;   /*maxn设置成超过最大长度且超过最大取值个数即可*/
int wa[maxn],wb[maxn],wv[maxn],box[maxn];
/*wa保存第一关键字，wb保存第二关键字，box是用来桶排序的桶子，wv作用未知*/
void getSA(int const r[],int sa[],int n,int m)
{
	int i,j,p,*x=wa,*y=wb,*t;               /*以下4句是一个标准桶排序过程*/  
	for(i=0;i<m;i++) box[i] = 0;            /*初始化桶子*/    
	for(i=0;i<n;i++) box[x[i]=r[i]]++;      /*第1个箱子保存第1个关键字出现的次数，第2个箱子保存第2个关键字出现的次数...，从0开始计数*/
	for(i=1;i<m;i++) box[i]+=box[i-1];      /*累加的作用是使得第i个关键字开始的下标是box[i]*/
	/*rank[i] = --box[x[i]]                 这句话可以得到第i个元素排第几，因为反向碰到的第1个在其box里面的元素，一定排在第box-1个*/
	for(i=n-1;i>=0;i--) sa[--box[x[i]]]=i;  /* 注意SA与RANK的关系，RANK[i]==j则SA[j]==i，所以直接写出SA，到这一步实际上就得到了SA1*/
	for(j=1,p=1;p<n;j*=2,m=p)               /*已知SAj，现在要求SA2j，相当于第1关键字是[0,j)，第2关键字是[j,2j)*/
	{                                       /*已知SAj，就是已知第1关键字的排列顺序，现在还要求第2关键字的排列顺序*/
		for(p=0,i=n-j;i<n;i++) y[p++]=i;    /*注意到r[0]的第2关键字实际上就是r[j]的第1关键字，r[1]的就是r[j+1]的...超出的部分一律补0，依次排在最前面*/
		for(i=0;i<n;i++) if(sa[i]>=j) y[p++]=sa[i]-j;
		/*现在已知关键字1的单独排序，关键字2的单独排序，要求关键字1/2的联合排序*/
		for(i=0;i<n;i++) wv[i]=x[y[i]];     /*没看懂*/
		for(i=0;i<m;i++) box[i]=0;
		for(i=0;i<n;i++) box[wv[i]]++;
		for(i=1;i<m;i++) box[i]+=box[i-1];
		for(i=n-1;i>=0;i--) sa[--box[wv[i]]]=y[i];
		for(t=x,x=y,y=t,p=1,x[sa[0]]=0,i=1;i<n;i++)
			x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p-1:p++;
	}
	return;
}
/*
函数8
求给定字符串的名次数组及height数组，要先求出后缀数组
arg1：字符串经过预处理后的整型数组，预处理的含义与函数7相同
仍然注意：经过处理后的长度比原字符串长度多1
arg2：arg1的后缀数组
arg3：arg1的长度
arg4：arg1的Rank数组
arg5：arg1的Height数组
返回值：void，结果保存在arg4与arg5中 
*/
void getRankAndHeight(int const r[],int const sa[],int n,int rank[],int height[])
{
	int i,j,k=0;
	for(i=1;i<n;i++) rank[sa[i]]=i;  /*原论文使用源数组的长度，此处实际用的参数是原长度+1*/
	for(i=0;i<n-1;height[rank[i++]]=k)
		for(k?k--:0,j=sa[rank[i]-1];r[i+k]==r[j+k];k++);
	return;
}


int Melody[SIZE];
int Rank[SIZE];
int SA[SIZE];
int Height[SIZE];

/*
在height数组中检查是否有取值不小于ans，且后缀最大距离不小于ans
n为height数组的长度
*/
bool check(int n,int ans){
    int i;
	int min = SA[1];
	int max = SA[1];
    for(i=2;i<n;i++){
		if ( Height[i] >= ans ){
            if ( min > SA[i] ) min = SA[i];
			if ( max < SA[i] ) max = SA[i];
			if ( max - min > ans ) return true;  /*找到了就不用再继续*/
			/*这里注意check的时候是>ans而不是>=ans，因为我们的数组是做差得到的*/
			/*例如差值数组有8个数，则可能出现不重叠的长度为4的重复子串*/
			/*但原始数组中只有9个数，不可能存在长度为5的不重叠数组*/
		}else{ /*进到这个分支说明前面的区间没有符合条件的，需要重新开始*/
            min = max = SA[i];
		}
	}
	return false;
}
int main(){
	int num;
	int i;
LL:
	scanf("%d",&num);
	if ( 0 == num ) return 0;
	for(i=0;i<num;i++) scanf("%d",Melody+i);
	if ( num < 10 ) {
		printf("0\n");
		CLEAR(Melody);
		goto LL;
	}
	Melody[i] = 0;
	for(i=0;i<num-1;i++) {        /*这道题并不处理输入数组本身，而应该处理输入数之间的差*/
		Melody[i] = Melody[i] - Melody[i+1] + RANGE;
//		Melody[i] += RANGE; 
	}
	Melody[i] = 0;
	getSA(Melody,SA,num,RANGE*2+10);             /*求SA*/
	getRankAndHeight(Melody,SA,num,Rank,Height); /*求Rank和Height*/
    /*接下来要找到这样一个k值，
	它使得height数组有区间（1个或者连续数个）取值不小于k，
	而且后缀距离不小于k
	最后，要求的ans就是所有k中最大的
	k值最大可能是num/2，最小当然是0
	所以题目转化为在[0,num/2]区间内找出符合条件的最大值
	注意到如果k符合条件，则所有比k小的都符合条件，如果k不符合条件，则所有比k大的都不符合条件
	所以可以使用二分法*/
    int left = 1;
	int right = num / 2;
	int mid;
	do{
        mid = ( left + right ) / 2;
		if ( check(num,mid) ) left = mid + 1 ;
		else                  right = mid - 1;
	}while( left <= right );
	if ( right >= 4 ) printf("%d\n",right+1);
	else printf("0\n");
	CLEAR(Melody);
	CLEAR(SA);
	CLEAR(Rank);
	CLEAR(Height);
	goto LL;
	return 0;
}
