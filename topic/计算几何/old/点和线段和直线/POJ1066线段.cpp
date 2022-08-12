/*
������������N���߶Σ��߶εĶ˵��ھ��α��ϣ���������һ�������ĵ㣬��Ϊtreasure���ڵĵص㡣�ʣ��Ӹõ㵽���α߾������߶����������Ƕ��٣�������߶��е㴩���߶Σ����α�ԵҲ��һ���߶Σ�
*/
#include <stdio.h>

#define MIN(x,y) ( ( x ) < ( y ) ? ( x ) : ( y ) )
#define MAX(x,y) ( ( x ) > ( y ) ? ( x ) : ( y ) )

#define SIZE 30

struct point_t{
	float x;
	float y;
};

//�����OA��OB
float cross(struct point_t O,struct point_t A,struct point_t B){
    float xoa = A.x - O.x;
	float yoa = A.y - O.y;
	float xob = B.x - O.x;
	float yob = B.y - O.y;
	return xoa * yob - xob * yoa;
}
//�ж��߶�AB��CD�Ƿ��ཻ
//�����ų�ʵ�顢����ʵ��
int isInter(struct point_t A,struct point_t B,struct point_t C,struct point_t D){
    return MAX(A.x,B.x) >= MIN(C.x,D.x)
		&& MAX(A.y,B.y) >= MIN(C.y,D.y)
		&& MAX(C.x,D.x) >= MIN(A.x,B.x)
		&& MAX(C.y,D.y) >= MIN(A.y,B.y)
		&& cross(A,C,B) * cross(A,B,D) >= 0
		&& cross(C,A,D) * cross(C,D,B) >= 0;
}

//����������ǽ�ϵĵ�
struct point_t Ext[4][SIZE+2];

//ָʾ��ǽ�ϵ�ĸ���
int Index[4] = {1,1,1,1};

//��ǽ�����߶�
struct point_t Wall[2][SIZE];

//���������Ӧ�����飬��һ�������������
void insert(float x,float y){
	if ( 0 == y ){
		int k = Index[0] - 1;
        if ( 0 == x || 100 == x ) return;
		while( x < Ext[0][k].x ){
			Ext[0][k+1].x = Ext[0][k].x;
			k--;
		}
		Ext[0][k+1].x = x;
		Ext[0][Index[0]].y = 0.f;
		Index[0]++;
		return;
	}else if ( 100 == y ){
        int k = Index[3] - 1;
		if ( 0 == x || 100 == x ) return;
		while( x < Ext[3][k].x ){
			Ext[3][k+1].x = Ext[3][k].x;
			k--;
		}
		Ext[3][k+1].x = x;
		Ext[3][Index[3]].y = 100.f;
		Index[3]++;
		return;
	}else if ( 0 == x ){
		int k = Index[2] - 1;
		while( y < Ext[2][k].y ){
			Ext[2][k+1].y = Ext[2][k].y;
			k--;
		}
        Ext[2][k+1].y = y;
		Ext[2][Index[2]].x = 0.f;
		Index[2]++;
		return;
	}else if ( 100 == x ){
		int k = Index[1] - 1;
		while( y < Ext[1][k].y ){
			Ext[1][k+1].y = Ext[1][k].y;
			k--;
		}
		Ext[1][k+1].y = y;
		Ext[1][Index[1]].x = 100.f;
		Index[1]++;
		return;
	}
	printf("ERROR\n");
}

int main(){
	int i,n;
	struct point_t trea,mid;
	int ans = 100;

	scanf("%d",&n);
	
	//��ʼ��4����ǽ�����
	Ext[0][0].x = 0.f;
	Ext[0][0].y = 0.f;

	Ext[1][0].x = 100.f;
	Ext[1][0].y = 0.f;

	Ext[2][0].x = 0.f;
	Ext[2][0].y = 0.f;

	Ext[3][0].x = 0.f;
	Ext[3][0].y = 100.f;

	for(i=0;i<n;i++){
		scanf("%f%f%f%f",&Wall[0][i].x,&Wall[0][i].y,&Wall[1][i].x,&Wall[1][i].y);
		insert(Wall[0][i].x,Wall[0][i].y);
		insert(Wall[1][i].x,Wall[1][i].y);
	}

    scanf("%f%f",&trea.x,&trea.y);

	//ȷ��4����ǽ���յ�
    Ext[0][Index[0]].x = 100.f;
	Ext[0][Index[0]].y = 0.f;

	Ext[1][Index[1]].x = 100.f;
	Ext[1][Index[1]].y = 100.f;

	Ext[2][Index[2]].x = 0.f;
	Ext[2][Index[2]].y = 100.f;

	Ext[3][Index[3]].x = 100.f;
	Ext[3][Index[3]].y = 100.f;

	for(i=0;i<3;i++) Index[i]++;

	//��һ����ǽ
	for(i=1;i<Index[0];i++){
		//��������㲻�غ�
		if ( Ext[0][i-1].x != Ext[0][i].x ){
			int j,itmp = 1;
			//ȡ���е�
            mid.x = ( Ext[0][i-1].x + Ext[0][i].x ) / 2.f;
			mid.y = 0.f;
			//��treasure�㵽���е�һ���뼸���߶��ཻ
            for(j=0;j<n;j++)
				itmp += isInter(trea,mid,Wall[0][j],Wall[1][j]);
			//���´�
			if ( itmp < ans ) ans = itmp;
		}
	}

	for(i=1;i<Index[1];i++){
		if ( Ext[1][i-1].y != Ext[1][i].y ){
			int j, itmp = 1;
			mid.x = 100.f;
			mid.y = ( Ext[1][i-1].y + Ext[1][i].y ) / 2.f;
			for(j=0;j<n;j++)
				itmp += isInter(trea,mid,Wall[0][j],Wall[1][j]);
			if ( itmp < ans ) ans = itmp;
		}
	}

	for(i=1;i<Index[3];i++){
		//��������㲻�غ�
		if ( Ext[3][i-1].x != Ext[3][i].x ){
			int j,itmp = 1;
			//ȡ���е�
			mid.x = ( Ext[3][i-1].x + Ext[3][i].x ) / 2.f;
			mid.y = 100.f;
			//��treasure�㵽���е�һ���뼸���߶��ཻ
			for(j=0;j<n;j++)
				itmp += isInter(trea,mid,Wall[0][j],Wall[1][j]);
			//���´�
			if ( itmp < ans ) ans = itmp;
		}
	}

	for(i=1;i<Index[2];i++){
		if ( Ext[2][i-1].y != Ext[2][i].y ){
			int j, itmp = 1;
			mid.x = 0.f;
			mid.y = ( Ext[2][i-1].y + Ext[2][i].y ) / 2.f;
			for(j=0;j<n;j++)
				itmp += isInter(trea,mid,Wall[0][j],Wall[1][j]);
			if ( itmp < ans ) ans = itmp;
		}
	}

	printf("Number of doors = %d\n",ans);

	return 0;
}