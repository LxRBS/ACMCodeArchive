/*
    n��������������һЩ�����������
    ��ʣ�µ���Χ����
    �󿳵���Щ���ԴﵽĿ�겢�ҷ�����С
*/

#include <stdio.h>
#include <math.h>
#include <algorithm>
using namespace std;

//������ݽṹ
struct point_t{
	int x,y;
	point_t(int a=0,int b=0):x(a),y(b){}
};

//���OA��OB
int cross(point_t const&O,point_t const&A,point_t const&B){
	int xoa = A.x - O.x;
	int yoa = A.y - O.y;
	int xob = B.x - O.x;
	int yob = B.y - O.y;
	return xoa * yob - xob * yoa;
}

inline double dist(point_t const&lhs,point_t const&rhs){
    double x = lhs.x - rhs.x;
    double y = lhs.y - rhs.y;
    return sqrt(x*x+y*y);
}

//�жϵ�l�Ƿ�ȵ�r���¸���
bool isBottomLeft(point_t const&l,point_t const&r){
	if ( l.y != r.y ) return l.y < r.y;
	return l.x < r.x;
}

//ΪGraham������׼��
point_t* pOrigin;
bool is4Graham(point_t const&l,point_t const&r){
	int t = cross(*pOrigin,l,r);
	if ( t ) return t > 0;
	return (l.x-pOrigin->x)*(l.x-pOrigin->x)<(r.x-pOrigin->x)*(r.x-pOrigin->x);
}

//Graham���ϸ�͹��
int Graham(point_t p[],int n){
	if ( 1 == n ) return 1;

	//�����������
	point_t* t = min_element(p,p+n,isBottomLeft);

	//��0�㽻��λ��
	point_t ptmp(*t);
	*t = p[0];
	p[0] = ptmp;

	//�����0������
	pOrigin = p;
	sort(p+1,p+n,is4Graham);

	//��ջѭ��
	int top = 2;
	for(int i=2;i<n;++i){
		while( top>1 && cross(p[top-2],p[top-1],p[i])<=0 )
			--top;
		p[top++] = p[i];
	}

	if( top>=3 && 0==cross(p[0],p[top-1],p[top-2]) )
		--top;

	return top;
}

int N;
point_t P[20];
int V[20],L[20];
bool read(){
    scanf("%d",&N);
    if ( 0 == N ) return false;
    for(int i=0;i<N;++i)scanf("%d%d%d%d",&P[i].x,&P[i].y,V+i,L+i);
    return true;
}

point_t Q[20];
int main(){
    //freopen("1.txt","r",stdin);

    for(int kase=1;read();++kase){
        int ansValue = 10000000;
        int ansCnt = 20;
        int ansStatus;
        double ansLen;

        int ii,n,value,len,cnt;
        for(int i=1;i<(1<<N);++i){

            for(value=len=n=ii=0;ii<N;++ii){
                if(i&(1<<ii)) value += V[ii], len += L[ii];//����
                else Q[n++] = P[ii];//���µ���
            }

            cnt = N - n;
            if ( n ) n = Graham(Q,n);
            Q[n] = Q[0];

            //���ܳ�
            double cir = 0;
            if ( n >= 2 ) for(ii=0;ii<n;++ii)cir += dist(Q[ii],Q[ii+1]);

            //�ж�
            if ( cir < len ){
                if ( value < ansValue || (value == ansValue && cnt < ansCnt) ){
                    ansValue = value;
                    ansCnt = cnt;
                    ansLen = len - cir;
                    ansStatus = i;
                }
            }
        }

        if (kase!=1) printf("\n");
        printf("Forest %d\nCut these trees:",kase);
        for(int i=0;i<N;++i)if(ansStatus&(1<<i))printf(" %d",i+1);
        printf("\nExtra wood: %.2f\n",ansLen);
    }
    return 0;
}