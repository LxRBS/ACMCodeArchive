/*
    �����Ŀ�ύPOJͨ�����ύHUNNU����
 ��EPS��1E-6��Ϊ1E-9ͨ��
    �Լ�����һ��������ݣ�������������
 �ļ��Ƿǳ��ӽ�����1E-6���£���������
 ��͹���Ľ�����ȶ�����Ϊ1E-9�Ժ�͹��
 ����ȶ���������������Ҳ��֮�ȶ���
*/
#include <cmath>
#include <algorithm>
#include <iostream>
using namespace std;

struct point_t{
	int x;
	int y;
};

int cross(point_t const& O,point_t const& A,point_t const& B){
	int xoa = A.x - O.x;
	int yoa = A.y - O.y;
	int xob = B.x - O.x;
	int yob = B.y - O.y;
	return xoa * yob - yoa * xob;
}

point_t P[50000];

//Ϊgraham������д�ıȽϺ���
bool cmp(point_t const& left,point_t const& right){
    int xl = left.x - P->x;
	int yl = left.y - P->y;
	int xr = right.x - P->x;
	int yr = right.y - P->y;

	int xmul = xl * yr - yl * xr;

	//��A��BΪ˳ʱ�룬��B�ļ��ǿ϶�С��A��ע�����P[0]�����������
	if ( xmul < 0 ) return false;

	if ( xmul > 0 ) return true;

	//���A��B��ͬһֱ�ߣ��������ĸ�С
	if ( xl * xl + yl * yl < xr * xr + yr * yr )
		return true;

	return false;
}

//����͹���ĵ���
int graham(int n){
	int blk = 0;
	//�����������
	for(int i=1;i<n;i++){
        if ( (P+i)->y < (P+blk)->y || ( (P+i)->y==(P+blk)->y && (P+i)->x<(P+blk)->x ) )
			blk = i;
	}
	//����
	point_t t(*P);
	*P = *(P+blk);
	*(P+blk) = t;

	std::sort(P+1,P+n,cmp);

	int top = 3;

	for(int i=3;i<n;i++){
		//�ϸ�͹����͹����û�й��ߵ�����
		while( cross(*(P+top-2),*(P+top-1),*(P+i)) <= 0 )
			top--;
		*(P+top++) = *(P+i);
	}

	return top;
}

int main(){
	int i,j,k,n;
	while( EOF != scanf("%d",&n) ){
        for(i=0;i<n;i++)scanf("%d%d",&(P+i)->x,&(P+i)->y);
		
		if ( 1 == n || 2 == n ){
			printf("0.00\n");
			continue;
		}

		if ( 3 == n ){
			int ans = cross(*P,*(P+1),*(P+2));
			if ( ans < 0 ) ans = -ans;
				if ( ans % 2 ) printf("%d.50\n",ans/2);
		else           printf("%d.00\n",ans/2);
			continue;
		}

        n = graham(n);


		//����������͹�����������p��������
		int edge;//���ڼ�¼ĳ���������γɵ����������
		int tmp;
		int ans = 0;
		for(i=0;i<n-2;i++){
            j = i + 1;
			k = j + 1;
L1:
			edge = 0;
			while( k < n ){
				tmp = cross(P[i],P[j],P[k]);
				if ( tmp < 0 ) tmp = -tmp;
				if ( edge > tmp ) break;
				edge = tmp;
				k++;
			}
			if ( ans < edge ) ans = edge;
			//��ʱijk����������ijΪ�ߵ����������
			//���´𰸣����k�ѵ����յ㣬������ѭ��j
			//������ѭ��j��k
			k--;
			j++;
			if ( j == n - 1 ) continue;
			goto L1;			
		}
			if ( ans % 2 ) printf("%d.50\n",ans/2);
		else           printf("%d.00\n",ans/2);
	}
	return 0;
}
