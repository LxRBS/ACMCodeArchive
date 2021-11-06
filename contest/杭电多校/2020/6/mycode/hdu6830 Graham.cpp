/**
    �������͵ĵ㼯��Ҫ�����ѡ3���㣬���͸�����ͬ
    ��������������
    
    ���������ͷֱ���͹����Ȼ����
    ע��Ҫ�ò��ϸ�͹�����ϸ�͹��WA
    Ҫ�����ϸ�͹����ģ���ǲ��������⣬����ԭ���Ͼ��ǲ��ϸ�͹��
    ������ϸ�͹���б�longlong�ˡ�
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long llt;

int getInt(){
	int sgn = 1;
	char ch = getchar();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = getchar();
	if ( '-' == ch ) {sgn = 0;ch=getchar();}

	int ret = (int)(ch-'0');
	while( '0' <= (ch=getchar()) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return sgn ? ret : -ret;
}

inline llt ABS(llt x){return x>=0?x:-x;}

struct point_t{
    llt x,y;
    point_t(llt a=0,llt b=0):x(a),y(b){}
}P[3][3010];

llt cross(point_t const&O,point_t const&A,point_t const&B){
    llt xoa = A.x - O.x;
    llt yoa = A.y - O.y;
    llt xob = B.x - O.x;
    llt yob = B.y - O.y;
    return xoa * yob - xob * yoa;
}

//A�����B�����¸����󷵻���
bool isLowLeft(point_t const&A,point_t const&B){
	return A.y < B.y || ( A.y == B.y && A.x < B.x );
}

//������pO�ļ������򣬼�����ȵľ����������ǰ��
point_t* pO;
bool comp4Graham(point_t const&A,point_t const&B){
    llt t = cross(*pO,A,B);
	if ( t ) return t > (llt)0;

	llt a1 = A.x > pO->x ? A.x - pO->x : pO->x - A.x;
	llt a2 = B.x > pO->x ? B.x - pO->x : pO->x - B.x;
    if ( a1 != a2 ) return a1 < a2;

	a1 = A.y > pO->y ? A.y - pO->y : pO->y - A.y;
	a2 = B.y > pO->y ? B.y - pO->y : pO->y - B.y;
	return a1 < a2;
}

//Graham��͹������������й��ߵ㣬����������������
int Graham(point_t P[],int n){
    if ( 1 == n ) return 1;

	//Ѱ�����������
	point_t *p = min_element(P,P+n,isLowLeft);

	//����
	swap(*p,P[0]);

	if ( 2 == n ) return 2;

	//���������򣬼�����ȣ������������ǰ��
	pO = P;
	sort(P+1,P+n,comp4Graham);

	//�����һ���ߵĹ��ߵ㵹��������
	int k = n - 1;
	while( k && 0LL == cross(P[0],P[n-1],P[--k]) );//kΪ0˵�����е㹲��
	if ( k ) for(int i=k+1;i<(n+k+1)>>1;++i) swap(P[i],P[n+k-i]);

	//������Grahamѭ��
	int top = 2;
	for(int i=2;i<n;++i){
		while( top > 1 && cross(P[top-2],P[top-1],P[i]) < (llt)0 )
			--top;
		P[top++] = P[i];
	}
	return top;
}

int N;
int R,G,B;

int main(){
    //freopen("1.txt","r",stdin);
    int nofkase = getInt();
    while(nofkase--){
        N = getInt();
        R = G = B = 0;
        for(int x,y,i=0;i<N;++i){
            x = getInt();
            y = getInt();
            switch(getInt()){
            case 0:P[0][R].x=x,P[0][R++].y=y;break;
            case 1:P[1][G].x=x,P[1][G++].y=y;break;
            case 2:P[2][B].x=x,P[2][B++].y=y;break;
            }
        }
        if(0==R||0==G||0==B){
            puts("0.0");
            continue;
        }

        //��͹��
        R = Graham(P[0],R);
        G = Graham(P[1],G);
        B = Graham(P[2],B);

        llt ans = 0LL;
        for(int i=0;i<R;++i)for(int j=0;j<G;++j)for(int k=0;k<B;++k){
            ans = max(ans, ABS(cross(P[0][i],P[1][j],P[2][k])));
        }
        printf("%I64d.",ans>>1);
        puts(ans&1?"5":"0");
    }
    return 0;
}
