//��ͬ�Ӵ������� 
#include <cstdio>
#include <algorithm>
using namespace std;

int const SIZE = 1005;
//�ָ������മ����ʱ��Ҫ�õ�����0��Ϊ���������϶��õ�
char const DELIMETER[] = {'#'};
int const DELIMETER_CNT = 1;
//��ĸ�����ĸ����
int const ALPHA_SIZE = DELIMETER_CNT + 128;
//charתint
inline int tr(char ch){
    if ( DELIMETER[0] == ch ) return 0;
    return ch;
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
char A[SIZE];
bool read(){
	scanf("%s",A);
	for(N=0;A[N];++N) R[N] = tr(A[N]);
	R[N++] = 0;
    return true;
}

int proc(){
    da(R,N,ALPHA_SIZE,SA);
    calHeight(R,SA,N,Rank,Height);

    /*
    dispArray(R,N);
    dispArray(SA,N);
    dispArray(Rank,N);
    dispArray(Height,N);
    //*/

    //���Ҳ�ͬ���Ӵ������������Ҳ�ͬ��ǰ׺����
    //ÿ����׺���Դ���N-SA[i]��ǰ׺��������ͬ����Height[i]��
    //���Ľ�����ǻ����N������Ӧ�����
    int r = -N;
    for(int i=0;i<N;++i) r += N - SA[i] - Height[i];
    return r;
}

int main(){
	int nofkase;
	scanf("%d",&nofkase);
	while( nofkase-- ){
		read();
		printf("%d\n",proc());
	}
    return 0;
}
