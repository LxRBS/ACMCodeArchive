/*
    ����n���ַ���
    ����Ӵ�������ÿ���ַ��������ٳ������� 
*/
#include <cstring>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int const SIZE = 10005 * 10;
//�ָ���������������Ϊ1����Ϊ��Ҫ������
char const DELIMETER[] = {'#'};
int const DELIMETER_CNT = 10;
//��ĸ�����ĸ����
int const ALPHA_SIZE = DELIMETER_CNT + 26;
//charתint
inline int tr(char ch){
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
char A[10005];
int Len[11];
int Start[11];
int MiniLen;
bool read(){
	scanf("%d",&N);
	Start[0] = 0;
	MiniLen = SIZE;
	for(int i=0;i<N;++i){
		scanf("%s",A);
		Len[i] = strlen(A);
		if ( MiniLen > Len[i] ) MiniLen = Len[i];
        for(int j=0;j<Len[i];++j)R[j+Start[i]]=tr(A[j]);
        R[Len[i]+Start[i]] = 27 + i;
        Start[i+1] = Start[i] + Len[i] + 1;
	}
	R[Start[N]-1] = 0;//��Start[N]�����ܳ���
    return true;
}

int Flag[] = {
    0,1,3,7,0xF,0x1F,0x3F,0x7F,0xFF,0x1FF,0x3FF,0x7FF
};
int _g(int sa){
	for(int i=1;i<N;++i){
		if ( sa < Start[i] ) return i - 1;
	}
	return N - 1;
}
void _f(int valley[],int peak[]){
	for(int i=0;i<N;++i) valley[i] = SIZE, peak[i] = -1;
}
void _d(int valley[],int peak[]){
	printf("valley:");
	for(int i=0;i<N;++i)printf(" %d",valley[i]);
	printf("\npeak:");
	for(int i=0;i<N;++i)printf(" %d",peak[i]);
	printf("\n");
}
//�ж�v�Ƿ���������
//����Height[i...j]������Ϊ2N-1��ֵ��С��v
//��SA[i-1,...,j]��������[Start[0],Start[1]),[Start[1],Start[2]),...���������2������ͬһ�����ֵ��С��v
bool check(int v){
	int valley[10];
	int peak[10];
	_f(valley,peak);
	int t = _g(SA[0]);
	valley[t] = peak[t] = SA[0];
	int flag = 0;
	for(int i=1;i<Start[N];++i){
        if ( Height[i] >= v ){
            t = _g(SA[i]);
            if ( valley[t] > SA[i] ) valley[t] = SA[i];
            if ( peak[t] < SA[i] ) peak[t] = SA[i];
            if ( peak[t] != -1
              && valley[t] != SIZE
			  && peak[t] - valley[t] >= v
			) flag |= 1 << t;

            if ( flag == Flag[N] ) return true;
        }else{
        	_f(valley,peak);
        	t = _g(SA[i]);
        	valley[t] = peak[t] = SA[i];
        	flag = 0;
        }
	}
    return false;
}
int proc(){
    da(R,Start[N],ALPHA_SIZE,SA);
    calHeight(R,SA,Start[N],Rank,Height);

    /*
    dispArray(R,Start[N]);
    dispArray(SA,Start[N]);
    dispArray(Rank,Start[N]);
    dispArray(Height,Start[N]);
    //*/

    //���ַ����������������ֵ
    int left = 1;//����Ϊ0
    int right = MiniLen >> 1;//���Ϊ��С���ȳ�2
    do{
    	int mid = ( left + right ) >> 1;
    	if ( check(mid) ) left = mid + 1;
    	else right = mid - 1;
    }while( left <= right );
    return right;
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
