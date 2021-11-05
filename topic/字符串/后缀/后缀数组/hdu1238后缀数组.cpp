//求多个字符串的最长子串，顺序或者逆序均可
//可以使用暴力法

#include <cstdio>
#include <cstring>
using namespace std;

//用于判断100个位
struct bit_t{
    int b[4];
    //设置第idx位，从0开始
    void set(int idx){b[idx/32] |= 1 << (idx % 32);}
    void clear(){b[0]=b[1]=b[2]=b[3]=0;}
    //判断是否全为1，共有n个
    bool ones(int n)const{
        int t = n / 32;
        for(int i=0;i<t;++i)if(b[i]!=0xFFFFFFFF)return false;
        return b[t] == ( 1 << ( n % 32 ) ) - 1;
    }
}Bit;

int const SIZE = 30000;
//分隔符，多串连接时需要用到，第0个为结束符，肯定用到
char const DELIMETER[] = {'#'};
int const DELIMETER_CNT = 201;
//字母表的字母个数
int const ALPHA_SIZE = 52;
//char转int
int L2I[256];
//必须首先调用一次
void initL2I(){
    for(int i=1;i<=26;++i) L2I['A'+i-1] = i;
    for(int i=27;i<=52;++i) L2I['a'+i-27] = i;
}
//辅助数组，以下划线开头
int _wa[SIZE],_wb[SIZE],_wv[SIZE],_ws[SIZE];
//辅助函数
int _cmp(int const r[],int a,int b,int l){return r[a]==r[b]&&r[a+l]==r[b+l];}
//求后缀数组的倍增算法
//r: 源数组，且除r[n-1]外，其余r[i]>0
//n: r的长度
//m: r中的元素取值的上界，即任意r[i]<m
//sa:后缀数组，即结果
void da(int const r[],int n,int m,int sa[]){
	int i,j,p,*x=_wa,*y=_wb,*t;
    for(i=0;i<m;i++) _ws[i] = 0;
    for(i=0;i<n;i++) _ws[x[i] = r[i]]++;
    for(i=1;i<m;i++) _ws[i] += _ws[i-1];
    for(i=n-1;i>=0;i--) sa[--_ws[x[i]]]=i;
    for(j=1,p=1;p<n;j*=2,m=p){
        for(p=0,i=n-j;i<n;i++) y[p++]=i;
        for(i=0;i<n;i++) if(sa[i]>=j) y[p++]=sa[i]-j;
        for(i=0;i<n;i++) _wv[i]=x[y[i]];
        for(i=0;i<m;i++) _ws[i]=0;
        for(i=0;i<n;i++) _ws[_wv[i]]++;
        for(i=1;i<m;i++) _ws[i] += _ws[i-1];
        for(i=n-1;i>=0;i--) sa[--_ws[_wv[i]]] = y[i];
        for(t=x,x=y,y=t,p=1,x[sa[0]]=0,i=1;i<n;i++)
            x[sa[i]]=_cmp(y,sa[i-1],sa[i],j)?p-1:p++;
    }
    return;
}

//计算rank数组与height数组
//r:  源数组
//sa: 后缀数组
//n:  源数组的长度
//rank: rank数组，即计算结果
//height: height数组，即计算结果
void calHeight(int const r[],int const sa[],int n,int rank[],int height[]){
    int i,j,k=0;
    for(i=1;i<n;i++) rank[sa[i]]=i;
    for(i=0;i<n-1;height[rank[i++]]=k)
    for(k?k--:0,j=sa[rank[i]-1];r[i+k]==r[j+k];k++);
    return;
}

void dispArray(int const a[],int n){
	for(int i=0;i<n;++i)printf("%d ",a[i]);
	printf("\n");
}

int N,Len[210],Start[220];
int MinLen,TotalLen;
char A[110][1005];
int R[SIZE],SA[SIZE];
int Rank[SIZE],Height[SIZE];
void read(){
	scanf("%d",&N);

	TotalLen = 0;
	MinLen = 10000000;

	//正着连
	for(int i=0;i<N;++i){
		scanf("%s",A[i]);
		int& l = Len[i];
		Start[i] = TotalLen;
		for(l=0;A[i][l];++l)R[TotalLen++]=L2I[A[i][l]];
		R[TotalLen++] = 52 + i + 1;
        if ( l < MinLen ) MinLen = l;
	}

	//反着连
	for(int i=0;i<N;++i){
		Start[N+i] = TotalLen;
        for(int j=Len[i]-1;j>=0;--j) R[TotalLen++] = L2I[A[i][j]];
        R[TotalLen++] = 52 + i + 101;
	}
	Start[N+N] = TotalLen;
	R[TotalLen-1] = 0;
}
//返回后缀所在的字符串编号
int _g(int sa){
	for(int i=1;i<=N;++i){
		if ( Start[i-1] <= sa && sa < Start[i] ){
			return i - 1;
		}
		if ( Start[N+i-1] <= sa && sa < Start[N+i] )
			return i - 1;
	}
	return -1;
}
//检查v是否符合条件
//Height[i-1.....j]均不小于v，且每个字符串的正序或者逆序均有分布
bool check(int v){
	int i = 1;
	while( i < TotalLen ){
        Bit.clear();
        while( i < TotalLen && Height[i] >= v ){
            int pos = _g(SA[i-1]);
            Bit.set(pos);
            if ( Bit.ones(N) ) return true;
            ++i;
        }

        int pos = _g(SA[i-1]);
        Bit.set(pos);
        if ( Bit.ones(N) ) return true;

        while( i < TotalLen && Height[i] < v ) ++i;
	}
	return false;
}

void proc(){
	da(R,TotalLen,256,SA);
	calHeight(R,SA,TotalLen,Rank,Height);

	/*
	dispArray(R,n);
	dispArray(SA,n);
	dispArray(Rank,n);
	dispArray(Height,n);
	//*/

	//二分
    int left = 1;      //最小的可能答案+1
    int right = MinLen;//最大可能答案
    do{
    	int mid = ( left + right ) >> 1;
    	if ( check(mid) ) left = mid + 1;
    	else right = mid - 1;
    }while( left <= right );

    printf("%d\n",right);
}
int main() {
    //freopen("1.txt","r",stdin);
    initL2I();
    int nofkase;
    scanf("%d",&nofkase);
	while( nofkase-- ) {
        read();
        proc();
	}
	return 0;
}
