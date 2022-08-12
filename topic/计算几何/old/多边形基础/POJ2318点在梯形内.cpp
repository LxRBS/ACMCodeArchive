/*
    ����ƽ��ֱ��֮�����������Σ��ٸ������ɸ��㣬��ÿ���������ж��ٸ���
    ʵ���Ͼ����жϵ��Ƿ��������ڣ�Ҳ���ǵ��Ƿ���͹������ڣ�Ҳ����ʹ�ò�� 
*/
#include <iostream>
using namespace std;

int n,m;
int xleftmost,ytopmost,xrightmost,ybottommost;
int U[5001];
int L[5001];
struct point_t{
	int x;
	int y;
	point_t(int xx=0,int yy=0){x=xx;y=yy;}
};

/* OA �� OB */
int crossMulti(const point_t & O, const point_t &A, const point_t &B){
	int xA = A.x - O.x;
	int yA = A.y - O.y;
	int xB = B.x - O.x;
	int yB = B.y - O.y;
	return xA * yB - yA * xB;
}

point_t toys[5001];
int cnt[5002];

/* �ж�p�Ƿ�������x1234�ڣ�����ʱ�����У�x1�ǵ׶˿���ĵ�*/
/* ���������� */
bool isIn( point_t p,int x1, int x2, int x3, int x4 ){
    if ( p.y > ytopmost || p.y < ybottommost ) return false;
	if ( p.y == ytopmost && ( p.x - x1 ) * ( p.x - x4 ) <= 0 ) return true;
	if ( p.y == ybottommost && ( p.x - x2 ) * ( p.x - x3 ) <= 0 ) return true;
	int c23 = crossMulti(p,point_t(x2,ybottommost),point_t(x3,ytopmost));
    int c41 = crossMulti(p,point_t(x4,ytopmost),point_t(x1,ybottommost));
	return c23 >= 0 && c41 >= 0 ;
}

int main(){
    int flag = 0;
	while( cin>>n && n ){
		memset(cnt,0,sizeof(cnt));
        if ( flag++ ){cout<<endl;}
		cin>>m>>xleftmost>>ytopmost>>xrightmost>>ybottommost;
		int i;
		for ( i=0;i<n;i++ )
			cin>>U[i]>>L[i];
		for( i=0;i<m;i++ ){
			cin>>toys[i].x>>toys[i].y;
			if ( isIn(toys[i],xleftmost,L[0],U[0],xleftmost) ){
				cnt[0]++;continue;
			}
			if ( isIn(toys[i],L[n-1],xrightmost,xrightmost,U[n-1]) ){
				cnt[n]++;continue;
			}
			for( int j=1;j<n;j++ ){
				if ( isIn(toys[i],L[j-1],L[j],U[j],U[j-1]) ){
					cnt[j]++;break;
				}
			}
		}
        for ( i=0;i<=n;i++ )
			cout<<i<<": "<<cnt[i]<<endl;
        
	}
	return 0;
}
