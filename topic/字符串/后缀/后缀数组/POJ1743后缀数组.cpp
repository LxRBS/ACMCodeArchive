/*
    ����һ�������������ص�����ظ��Ӵ�
	  �����Ŀ��Ϊ�������������ÿһ����ĸ�����һ���̶�ֵ����������ȵģ���Ϊ�����Ŀ�ı��������ֵ�����
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
int const maxn = SIZE;   /*maxn���óɳ�����󳤶��ҳ������ȡֵ��������*/
int wa[maxn],wb[maxn],wv[maxn],box[maxn];
/*wa�����һ�ؼ��֣�wb����ڶ��ؼ��֣�box������Ͱ�����Ͱ�ӣ�wv����δ֪*/
void getSA(int const r[],int sa[],int n,int m)
{
	int i,j,p,*x=wa,*y=wb,*t;               /*����4����һ����׼Ͱ�������*/  
	for(i=0;i<m;i++) box[i] = 0;            /*��ʼ��Ͱ��*/    
	for(i=0;i<n;i++) box[x[i]=r[i]]++;      /*��1�����ӱ����1���ؼ��ֳ��ֵĴ�������2�����ӱ����2���ؼ��ֳ��ֵĴ���...����0��ʼ����*/
	for(i=1;i<m;i++) box[i]+=box[i-1];      /*�ۼӵ�������ʹ�õ�i���ؼ��ֿ�ʼ���±���box[i]*/
	/*rank[i] = --box[x[i]]                 ��仰���Եõ���i��Ԫ���ŵڼ�����Ϊ���������ĵ�1������box�����Ԫ�أ�һ�����ڵ�box-1��*/
	for(i=n-1;i>=0;i--) sa[--box[x[i]]]=i;  /* ע��SA��RANK�Ĺ�ϵ��RANK[i]==j��SA[j]==i������ֱ��д��SA������һ��ʵ���Ͼ͵õ���SA1*/
	for(j=1,p=1;p<n;j*=2,m=p)               /*��֪SAj������Ҫ��SA2j���൱�ڵ�1�ؼ�����[0,j)����2�ؼ�����[j,2j)*/
	{                                       /*��֪SAj��������֪��1�ؼ��ֵ�����˳�����ڻ�Ҫ���2�ؼ��ֵ�����˳��*/
		for(p=0,i=n-j;i<n;i++) y[p++]=i;    /*ע�⵽r[0]�ĵ�2�ؼ���ʵ���Ͼ���r[j]�ĵ�1�ؼ��֣�r[1]�ľ���r[j+1]��...�����Ĳ���һ�ɲ�0������������ǰ��*/
		for(i=0;i<n;i++) if(sa[i]>=j) y[p++]=sa[i]-j;
		/*������֪�ؼ���1�ĵ������򣬹ؼ���2�ĵ�������Ҫ��ؼ���1/2����������*/
		for(i=0;i<n;i++) wv[i]=x[y[i]];     /*û����*/
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
����8
������ַ������������鼰height���飬Ҫ�������׺����
arg1���ַ�������Ԥ�������������飬Ԥ����ĺ����뺯��7��ͬ
��Ȼע�⣺���������ĳ��ȱ�ԭ�ַ������ȶ�1
arg2��arg1�ĺ�׺����
arg3��arg1�ĳ���
arg4��arg1��Rank����
arg5��arg1��Height����
����ֵ��void�����������arg4��arg5�� 
*/
void getRankAndHeight(int const r[],int const sa[],int n,int rank[],int height[])
{
	int i,j,k=0;
	for(i=1;i<n;i++) rank[sa[i]]=i;  /*ԭ����ʹ��Դ����ĳ��ȣ��˴�ʵ���õĲ�����ԭ����+1*/
	for(i=0;i<n-1;height[rank[i++]]=k)
		for(k?k--:0,j=sa[rank[i]-1];r[i+k]==r[j+k];k++);
	return;
}


int Melody[SIZE];
int Rank[SIZE];
int SA[SIZE];
int Height[SIZE];

/*
��height�����м���Ƿ���ȡֵ��С��ans���Һ�׺�����벻С��ans
nΪheight����ĳ���
*/
bool check(int n,int ans){
    int i;
	int min = SA[1];
	int max = SA[1];
    for(i=2;i<n;i++){
		if ( Height[i] >= ans ){
            if ( min > SA[i] ) min = SA[i];
			if ( max < SA[i] ) max = SA[i];
			if ( max - min > ans ) return true;  /*�ҵ��˾Ͳ����ټ���*/
			/*����ע��check��ʱ����>ans������>=ans����Ϊ���ǵ�����������õ���*/
			/*�����ֵ������8����������ܳ��ֲ��ص��ĳ���Ϊ4���ظ��Ӵ�*/
			/*��ԭʼ������ֻ��9�����������ܴ��ڳ���Ϊ5�Ĳ��ص�����*/
		}else{ /*���������֧˵��ǰ�������û�з��������ģ���Ҫ���¿�ʼ*/
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
	for(i=0;i<num-1;i++) {        /*����Ⲣ�������������鱾����Ӧ�ô���������֮��Ĳ�*/
		Melody[i] = Melody[i] - Melody[i+1] + RANGE;
//		Melody[i] += RANGE; 
	}
	Melody[i] = 0;
	getSA(Melody,SA,num,RANGE*2+10);             /*��SA*/
	getRankAndHeight(Melody,SA,num,Rank,Height); /*��Rank��Height*/
    /*������Ҫ�ҵ�����һ��kֵ��
	��ʹ��height���������䣨1����������������ȡֵ��С��k��
	���Һ�׺���벻С��k
	���Ҫ���ans��������k������
	kֵ��������num/2����С��Ȼ��0
	������Ŀת��Ϊ��[0,num/2]�������ҳ��������������ֵ
	ע�⵽���k���������������б�kС�Ķ��������������k�����������������б�k��Ķ�����������
	���Կ���ʹ�ö��ַ�*/
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
