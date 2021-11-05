#include <stdio.h>

struct point_t{
	int x;
	int y;
};

int cross(struct point_t const* pO,struct point_t const* pA,struct point_t const* pB){
	int xoa = pA->x - pO->x;
	int yoa = pA->y - pO->y;
	int xob = pB->x - pO->x;
	int yob = pB->y - pO->y;
	return xoa * yob - yoa * xob;
}

//根据基点与朝向，得到下一个点
void getPt(struct point_t const* pO,struct point_t* pA,char orient){
    *pA = *pO;
	switch( orient ){
		case '1': pA->x -= 1;pA->y -= 1;return;
		case '2': pA->y -= 1;return;
		case '3': pA->x += 1;pA->y -= 1;return;
		case '4': pA->x -= 1;return;
		case '6': pA->x += 1;return;
		case '7': pA->x -= 1;pA->y += 1;return;
		case '8': pA->y += 1;return;
		case '9': pA->x += 1;pA->y += 1;return;
	}
}

char Digit[1000000+1];
struct point_t Origin,A,B;

int main(){
    int t;
	scanf("%d",&t);

	//原点
	Origin.x = Origin.y = 0;

	while(t--){
		long long int ans = 0;
		char* p = Digit;

		scanf("%s",Digit);

		//保证有多边形出现
		if ( '5' == *Digit || '5' == *(Digit+1) ){
			printf("0\n");
			continue;
		}

		//首先取出2个点
        getPt(&Origin,&A,*p);
		p++;

		getPt(&A,&B,*p);
		p++;

		ans += cross(&Origin,&A,&B);

		while( '5' != *p ){
	        A.x = B.x;
			A.y = B.y;
		    getPt(&A,&B,*p);
			p++;
			ans += cross(&Origin,&A,&B);
		}

		if ( ans < 0 ) ans = -ans;

		if ( ans % 2 ) printf("%I64d.5\n",ans / 2);
		else           printf("%I64d\n",ans/2);
	}
	return 0;
}