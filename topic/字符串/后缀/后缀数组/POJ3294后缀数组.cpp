/*
    给定n个字符串
    求出现在不少于k/2个字符串中的最长公共子串 
*/
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

int const SIZE = 1005 * 100;
//分隔符，多串连接时需要用到，第0个为结束符，肯定用到
char const DELIMETER[] = {'#'};
int const DELIMETER_CNT = 100;
//字母表的字母个数
int const ALPHA_SIZE = DELIMETER_CNT + 26;
//char转int
inline int tr(char ch){
    return ch - 'a' + 1;
}
//辅助宏，以下划线开头
#define _F(x) ((x)/3+((x)%3==1?0:tb))
#define _G(x) ((x)<tb?(x)*3+1:((x)-tb)*3+2)
//辅助数组，以下划线开头
int _wa[SIZE],_wb[SIZE],_wv[SIZE],_ws[SIZE];
//辅助函数
int _c0(int const r[],int a,int b){
	return r[a] == r[b]
		&& r[a+1] == r[b+1]
		&& r[a+2] == r[b+2];
}
int _c12(int k,int *r,int a,int b){
	if( 2 == k ) return r[a]<r[b] || ( r[a]==r[b]&&_c12(1,r,a+1,b+1) );
    return r[a]<r[b] || ( r[a]==r[b]&&_wv[a+1]<_wv[b+1] );
}
void _sort(int const r[],int *a,int *b,int n,int m){
    int i;
    for(i=0;i<n;i++) _wv[i] = r[a[i]];
    for(i=0;i<m;i++) _ws[i] = 0;
    for(i=0;i<n;i++) _ws[_wv[i]]++;
    for(i=1;i<m;i++) _ws[i] += _ws[i-1];
    for(i=n-1;i>=0;i--) b[--_ws[_wv[i]]] = a[i];
    return;
}
//后缀数组的dc3算法，使用此dc3算法一定要保证r与sa的最大长度不小于3倍原长度
//r: 源数组，且除r[n-1]外，其余r[i]>0
//n: r的长度
//m: r中的元素取值的上界，即任意r[i]<m
//sa:后缀数组，即结果
void dc3(int r[],int n,int m,int sa[]){
    int i,j,*rn=r+n,*san=sa+n,ta=0,tb=(n+1)/3,tbc=0,p;
    r[n] = r[n+1] = 0;
    for(i=0;i<n;i++) if(i%3!=0) _wa[tbc++]=i;
    _sort(r+2,_wa,_wb,tbc,m);
    _sort(r+1,_wb,_wa,tbc,m);
    _sort(r,_wa,_wb,tbc,m);
    for(p=1,rn[_F(_wb[0])]=0,i=1;i<tbc;i++)
        rn[_F(_wb[i])] = _c0(r,_wb[i-1],_wb[i])?p-1:p++;
    if(p<tbc) dc3(rn,tbc,p,san);
    else for(i=0;i<tbc;i++) san[rn[i]]=i;
    for(i=0;i<tbc;i++) if(san[i]<tb) _wb[ta++] = san[i]*3;
    if(n%3==1) _wb[ta++]=n-1;
    _sort(r,_wb,_wa,ta,m);
    for(i=0;i<tbc;i++) _wv[_wb[i] = _G(san[i])] = i;
    for(i=0,j=0,p=0;i<ta&&j<tbc;p++)
        sa[p] = _c12(_wb[j]%3,r,_wa[i],_wb[j]) ? _wa[i++] : _wb[j++];
    for(;i<ta;p++) sa[p] = _wa[i++];
    for(;j<tbc;p++) sa[p] = _wb[j++];
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

int R[SIZE*3],SA[SIZE*3];//3倍!!!
int Rank[SIZE],Height[SIZE];

int N;
char A[1005];
int Len[105],Start[105];
int MiniLen;
bool read(){
	scanf("%d",&N);
	if ( 0 == N ) return false;

	if ( 1 == N ){
		scanf("%s",A);
		printf("%s\n",A);
		return true;
	}

	Start[0] = 0;
	MiniLen = SIZE;
	for(int i=0;i<N;++i){
		scanf("%s",A);
		Len[i] = strlen(A);
		if ( MiniLen > Len[i] ) MiniLen = Len[i];
		for(int j=0;j<Len[i];++j) R[j+Start[i]] = tr(A[j]);
		R[Start[i] + Len[i]] = i + 27;
		Start[i+1] = Start[i] + Len[i] + 1;
	}
	R[Start[N]-1] = 0;
	return true;
}

//返回后缀所在的字符串编号
int _g(int sa){
    for(int i=1;i<N;++i){
    	if ( Start[i-1] <= sa && sa < Start[i] )
		    return i - 1;
    }
    return N - 1;
}
//检查v是否符合条件
//Height中存在[i...j]，不小于v
//且SA[i-1,...,j]分别属于N/2个区间的正序或者逆序，
bool check(int v){
    int cnt = 0;
    bool a[100] = {false};
    a[_g(SA[0])] = true;
    cnt = 1;
    for(int i=1;i<Start[N];++i){
        if ( Height[i] >= v ){
            int t = _g(SA[i]);
            if ( !a[t] ) a[t] = true, ++cnt;
            if ( cnt + cnt > N ) return true;
        }else{
            memset(a,0,sizeof(a));
            a[_g(SA[i])] = true;
            cnt = 1;
        }
    }
    return false;
}
int proc(){
	dc3(R,Start[N],ALPHA_SIZE,SA);
	calHeight(R,SA,Start[N],Rank,Height);
	/*
	dispArray(Start,N+1);
	dispArray(R,Start[N]);
	dispArray(SA,Start[N]);
	dispArray(Rank,Start[N]);
	dispArray(Height,Start[N]);
	//*/

	//二分法查找满足条件的值
	int left = 1;//答案至少是0
	int right = MiniLen;//最多是MiniLen，这是一个BUG，但数据没检测出来 
	do{
		int mid = ( left + right ) >> 1;
		if ( check(mid) ) left = mid + 1;
		else right = mid - 1;
	}while( left <= right );
    return right;
}
inline char itr(int v){return v-1+'a';}

void output(int v,int saidx){
	int k = SA[saidx];
    for(int i=0;i<v;++i)printf("%c",itr(R[k++]));
    printf("\n");
}
//输出所有满足条件的长度为t的子串
void output(int v){
	int i = 1;
	while( i < Start[N] ){
        while( Height[i] < v ) ++i;
        if ( i == Start[N] ) return;

        int k = 0;
        int cnt = 1;
        bool a[100] = {false};
        int t = _g(SA[i-1]);
        a[t] = true;
        while( i + k < Start[N] && Height[i+k] >= v ){
        	int tt = _g(SA[i+k]);
        	if ( !a[tt] ){
        		a[tt] = true, ++cnt;
        	}
        	++k;
        }
        if ( cnt + cnt > N ) output(v,i-1);
        i += k;
	}
}
int main() {
	bool flag = false;
	while( read() ){
		if ( flag ) printf("\n");
		flag = true;
		int t = proc();
		if ( 0 == t ) printf("?\n");
		else output(t);
	}
	return 0;
}
