//47ms������DC3��32ms 
#include <cstdio>
#include <algorithm>
using namespace std;

int const SIZE = 20005;
//�ָ������മ����ʱ��Ҫ�õ�����0��Ϊ���������϶��õ�
char const DELIMETER[] = {'#'};
int const DELIMETER_CNT = 1;
//��ĸ�����ĸ����
int const ALPHA_SIZE = DELIMETER_CNT + 26;
//charתint
inline int tr(char ch){
    if ( DELIMETER[0] == ch ) return 0;
    return ch - 'a' + 1;
}
//�������飬���»��߿�ͷ
int _wa[SIZE],_wb[SIZE],_wv[SIZE],_ws[SIZE];
//��������
int _cmp(int const r[],int a,int b,int l){return r[a]==r[b]&&r[a+l]==r[b+l];}
//���׺����ı����㷨
//r: Դ���飬�ҳ�r[n-1]�⣬����r[i]>0
//n: r�ĳ���
//m: r�е�Ԫ��ȡֵ���Ͻ磬������r[i]<m
//sa:��׺���飬�����
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

//����rank������height����
//r:  Դ����
//sa: ��׺����
//n:  Դ����ĳ���
//rank: rank���飬��������
//height: height���飬��������
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

int R[SIZE];
int SA[SIZE],Rank[SIZE],Height[SIZE];
int N,K;
int A[SIZE];
int Idx[1000005];
bool read(){
	if ( EOF == scanf("%d%d",&N,&K) ) return false;
	//����Ŀ���ȡֵΪ1000000����һ����ɢ�����Ե�20000
    for(int i=0;i<N;++i)scanf("%d",A+i),R[i]=A[i];
    sort(A,A+N);
    int n = unique(A,A+N) - A;
    for(int i=0;i<n;++i)Idx[A[i]] = i + 1;
    for(int i=0;i<N;++i) R[i] = Idx[R[i]];
    R[N++] = 0;
    return true;
}
//�ж�nֵ�Ƿ���������
//Height��������������K-1��ֵ��С��v
bool check(int v){
    int i = 1;
    while( i < N ){
    	while( i < N && Height[i] < v ) ++i;
    	int k = 0;
        while( i + k < N && Height[i+k] >= v && k < K - 1 ) ++k;
        if( K - 1 == k ) return true;
        i += k + 1;
    }
    return false;
}
int proc(){
    da(R,N,N+2,SA);
    calHeight(R,SA,N,Rank,Height);

    /*
    dispArray(R,N);
    dispArray(SA,N);
    dispArray(Rank,N);
    dispArray(Height,N);
    //*/
    //���ַ����������ظ���k�ε��Ӵ�������ȣ����ص�
    int left = 0;//��������0
    int right = N - K;//��������N-k
    do{
    	int mid = ( left + right ) >> 1;
    	if ( check(mid) ) left = mid + 1;
    	else right = mid - 1;
    }while( left <= right );
    return right;
}

int main(){
    while( read() )printf("%d\n",proc());
    return 0;
}


