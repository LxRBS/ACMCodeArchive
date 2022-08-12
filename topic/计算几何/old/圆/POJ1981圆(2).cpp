#include <stdio.h>
#include <math.h>

struct point_t{
	double x,y;     
};

double const EPS = 1E-6;
double const PI = 3.1415926;

#define isZero(x) ( (x) < EPS && (x) > -EPS )

struct point_t P[300];
struct point_t Cen;

int main(){
	int i,j,k,n;
	double dist2,xtmp;
	double xx,yy,midx,midy,angle;

	int ans;
	int tmp;

	while( scanf("%d",&n) && n ){
		ans = 1;

		for(i=0;i<n;i++){
			scanf("%lf%lf",&(P+i)->x,&(P+i)->y);
		}
        
		for(i=0;i<n-1;i++){
			for(j=i+1;j<n;j++){
				xx = (P+i)->x - (P+j)->x;
				yy = (P+i)->y - (P+j)->y;
				dist2 = xx * xx + yy * yy; 

				if ( dist2 <= 4.0 ){
					midx = ( (P+i)->x + (P+j)->x ) / 2.0;
					midy = ( (P+i)->y + (P+j)->y ) / 2.0;
				
// 					if ( isZero(yy) ) angle = PI / 2.0;
// 					else              angle = atan(-xx/yy);
// 					
// 					dist2 = sqrt( 1.0 - dist2 / 4.0 );
// 					
// 					Cen.x = midx + dist2 * cos(angle);
// 					Cen.y = midy + dist2 * sin(angle);

					if ( isZero(yy) ){
						Cen.x = midx;
						Cen.y = midy + sqrt( 1.0 - dist2 / 4.0 );
					}else{
						xtmp = yy * sqrt( ( 1.0 - dist2 / 4.0 ) / dist2 );
						Cen.x = midx + xtmp;
                        Cen.y = midy - xtmp * xx / yy;
					}


					tmp = 2;
					for(k=0;k<n;k++)if(k!=i&&k!=j){
						double xx = Cen.x - (P+k)->x;
						double yy = Cen.y - (P+k)->y;
						double dist2 = xx * xx + yy * yy;

						if ( dist2 <= 1.0 )
							tmp++;
					}
					if ( tmp > ans ) ans = tmp;

				}

			}
		}
		
		printf("%d\n",ans);
	}

	return 0;    
}
