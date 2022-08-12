#include <cstdio>
#include <algorithm>
using namespace std;
typedef double llt;
struct point_t{
	int x;
	int y;
	point_t(int xx=0,int yy=0):x(xx),y(yy){}
	void disp()const{printf("(%d,%d)",x,y);}
};
bool operator != (point_t const&lhs,point_t const&rhs){
	return lhs.x != rhs.x || lhs.y != rhs.y;
}
//����ֵ��˻ᳬ��Χ 
llt cross(point_t const&O,point_t const&A,point_t const&B){
	llt xoa = A.x - O.x;
	llt xob = B.x - O.x;
	llt yoa = A.y - O.y;
	llt yob = B.y - O.y;
	return xoa * yob - xob * yoa;
}
//�жϵ�P���߶�AB��
bool isInter(point_t const&P,point_t const&A,point_t const&B){
	return 0 == cross(P,A,B)
		&& P.x <= max(A.x,B.x)
		&& P.x >= min(A.x,B.x)
		&& P.y <= max(A.y,B.y)
		&& P.y >= min(A.y,B.y);
}
//�߶�AB��CD�Ƿ��ཻ
bool isInter(point_t const&A,point_t const&B,point_t const&C,point_t const&D){
    return max(A.x,B.x) >= min(C.x,D.x)
    	&& max(A.y,B.y) >= min(C.y,D.y)
		&& max(C.x,D.x) >= min(A.x,B.x)
		&& max(C.y,D.y) >= min(A.y,B.y)
		&& cross(A,C,B) * cross(A,B,D) >= 0
		&& cross(C,A,D) * cross(C,D,B) >= 0;
}
bool isPolygon(point_t const P[],int n){
    if ( P[0] != P[n] )
    	return false;

    for(int i=0;i<n-2;++i)for(int j=i+2;j<n-1;++j)
    	if(isInter(P[i],P[i+1],P[j],P[j+1]))
    		return false;

    return true;
}
//��p�Ƿ��ڶ����P��,P�����ǰ���
bool isIn(point_t const&p,point_t const P[],int n){
    point_t q(10000000,p.y);
    int ret = 0;
    for(int i=0;i<n;++i){
    	//���ڱ���
    	if ( isInter(p,P[i],P[i+1]) ) return false;
    	//ˮƽ�߲��㣬���ཻ����
        if ( P[i].y == P[i+1].y || !isInter(p,q,P[i],P[i+1]) )continue;

        //�ཻ�ڽϸߵĶ˵�Ҳ����
        if ( ( P[i].y > P[i+1].y && isInter(P[i],p,q) )
          || ( P[i+1].y > P[i].y && isInter(P[i+1],p,q) ) ) continue;

        ++ret;
    }

    //������������p��P��
    return ret & 1;
}
//�����PQ�Ƿ��ཻ
bool isInter(point_t const P[],int n,point_t const Q[],int m){
    for(int i=0;i<n;++i)for(int j=0;j<m;++j)
    	if ( isInter(P[i],P[i+1],Q[j],Q[j+1]) )
    		return true;
    return false;
}
//�����P�Ƿ���Q�ڣ��Ѿ�ȷ��P��Q���ཻ
bool isIn(point_t const P[],int n,point_t const Q[],int m){
    for(int i=0;i<n;++i)
    	if ( !isIn(P[i],Q,m) )return false;
    return true;
}
int N;
int Cnt[50];
point_t P[50][51];
void read(){
    scanf("%d",&N);
    for(int i=0;i<N;++i){
    	scanf("%d",Cnt+i);
    	for(int j=0;j<Cnt[i];++j)
    		scanf("%d%d",&P[i][j].x,&P[i][j].y);
    	--Cnt[i];
    }
}

char ANS[4][25] = {
	"CORRECT",
	"INVALID POLYGON",
	"INVALID NESTING",
	"INTERSECTING POLYGONS"
};
int proc(){
    for(int i=0;i<N;++i)
    	if( !isPolygon(P[i],Cnt[i]) )
    		return 1;

    for(int i=0;i<N-1;++i)for(int j=i+1;j<N;++j)
    	if( isInter(P[i],Cnt[i],P[j],Cnt[j]) ) return 3;

    int a[50] = {0};
    for(int i=0;i<N;++i)for(int j=0;j<N;++j){
    	if ( i == j ) continue;
    	if ( isIn(P[i],Cnt[i],P[j],Cnt[j]) ){
    		++a[i];
            if ( a[i] >= 2 ) return 2;
    	}
    }
    return 0;
}
int main() {
	int kase;
	scanf("%d",&kase);
	while(kase--){
		read();
        printf("%s\n",ANS[proc()]);
	}
	return 0;
}
