//250ms���ȱ����㷨ʱ�仹��һ�� 
#include <cstdio>

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
//�����꣬���»��߿�ͷ
#define _F(x) ((x)/3+((x)%3==1?0:tb))
#define _G(x) ((x)<tb?(x)*3+1:((x)-tb)*3+2)
//�������飬���»��߿�ͷ
int _wa[SIZE],_wb[SIZE],_wv[SIZE],_ws[SIZE];
//��������
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
//��׺�����dc3�㷨��ʹ�ô�dc3�㷨һ��Ҫ��֤r��sa����󳤶Ȳ�С��3��ԭ����
//r: Դ���飬�ҳ�r[n-1]�⣬����r[i]>0
//n: r�ĳ���
//m: r�е�Ԫ��ȡֵ���Ͻ磬������r[i]<m
//sa:��׺���飬�����
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

int R[SIZE*3],SA[SIZE*3];//3��������
int Rank[SIZE],Height[SIZE];
int N;
bool read(){
	scanf("%d",&N);
	if ( 0 == N ) return false;
	int x,y;
	scanf("%d",&x);
    for(int i=0;i<N-1;++i){
    	scanf("%d",&y);
    	R[i] = x - y + 89;
    	x = y;
    }
    R[N-1] = 0;
    return true;
}
//�ж�vֵ�Ƿ���������
//Height�����д���һ������i��j,Height[i...j]>=v����SA[i]��SA[j]�ľ�����ڵ���v
bool check(int v){
    int valley = SA[1];
    int peak = SA[1];
    for(int i=2;i<N;++i){
    	if ( Height[i] >= v ){
    		if ( valley > SA[i] ) valley = SA[i];
    		if ( peak < SA[i] ) peak = SA[i];
    		if ( peak - valley >= v ) return true;
    	}else{
    		peak = valley = SA[i];
    	}
    }
    return false;
}
int proc(){
	if ( N < 10 ) return 0;
    dc3(R,N,88*2+10,SA);
    calHeight(R,SA,N,Rank,Height);

    //���ַ����Ҳ��ص�����Ӵ�
    int left = 0;//��������0
    int right = N >> 1;//��������N/2
    do{
    	int mid = ( left + right ) >> 1;
    	if ( check(mid) ) left = mid + 1;
    	else right = mid - 1;
    }while( left <= right );
    return right >= 4 ? right + 1 : 0;
}

int main(){
    while( read() )printf("%d\n",proc());
    return 0;
}


