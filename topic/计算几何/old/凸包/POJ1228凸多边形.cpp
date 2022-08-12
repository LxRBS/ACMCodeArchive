#include <iostream>
#include <algorithm>

using namespace std;

#define SIZE 1001

struct point_t{
	int x;
	int y;
	point_t(int xx=0,int yy=0):x(xx),y(yy){}
}P[SIZE];

int cross(point_t const&O,point_t const&A,point_t const&B){
    int xoa = A.x - O.x;
	int yoa = A.y - O.y;
	int xob = B.x - O.x;
	int yob = B.y - O.y;
	return xoa * yob - yoa * xob;
};

class fun_t{
private:
	point_t origin;
public:
	fun_t(point_t const p=point_t(0,0)):origin(p){}
	bool operator () (point_t const&l,point_t const&r){
		int xl = l.x - origin.x;
		int yl = l.y - origin.y;
		int xr = r.x - origin.x;
		int yr = r.y - origin.y;
		int xmul = xl * yr - yl * xr;
		//����l��r��ת���жϼ��Ǵ�С
		if ( xmul < 0 ) return false;
		if ( xmul > 0 ) return true;
		//����һ����������ĸ�С
		if ( xl*xl+yl*yl < xr*xr+yr*yr ) return true;
		return false;
	}
};


//���ֵ�Graham������ҪGraham��͹������������
bool Graham(int n){
	//���������Լ�����
    fun_t fun(*P);
	sort(P+1,P+n,fun);

	//������һ����û�����㹲�ߣ���Ϊ��
	if ( 0 != cross(P[0],P[n-1],P[n-2]) ) return false;

	//Ѱ�����һ���߹��ߵľ���ԭ������ĵ�����
	int x = n - 2;
	while( 0 == cross(P[0],P[x+1],P[x]) ) --x;

	P[n-1] = P[x];
	n = x + 1;

	int t;
	bool flag = false;
    int k = 0;
	for(int i=2;i<n;++i){
		t = cross(P[i-2],P[i-1],P[i]);
		if ( 0 == t ) {
			flag = true;
		}else if( t > 0 ){
			if ( false == flag ) return false;
			flag = false;
			++k;
		}
	}

	return k;
}

int main(){
	int kase;
	scanf("%d",&kase);

	while(kase--){
        int n;
		scanf("%d",&n);

		int index = -1;
		int ymin = INT_MAX;
		int xmin = INT_MAX;

		//���룬��Ѱ�����������
		for(int i=0;i<n;++i){
			scanf("%d%d",&P[i].x,&P[i].y);
			if ( P[i].y < ymin ){
				index = i;
				ymin = P[i].y;
				xmin = P[i].x;
			}else if ( P[i].y == ymin && P[i].x < xmin ){
				index = i;
				xmin = P[i].x;
			}
		}

		if ( n < 6 ){
			printf("NO\n");
			continue;
		}

		//������������������
		point_t pointtmp(*P);
		P[0] = P[index];
		P[index] = pointtmp;

		if ( Graham(n) ) printf("YES\n");
		else             printf("NO\n");
	}

	return 0;
}