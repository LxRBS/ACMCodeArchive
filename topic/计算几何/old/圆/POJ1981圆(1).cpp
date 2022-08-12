#include <stdio.h>
#include <math.h>

struct point_t{
    double x,y;     
};

double const EPS = 1E-4;

#define isZero(x) ( (x) < EPS && (x) > -EPS )

struct point_t P[300];
struct point_t Cen[44850];

int main(){
    int i,j,n;
    double dist2;
    double xx,yy;
	double midx,midy,xtmp;

    int ck;
    int ans;
    int tmp;
    
    while( scanf("%d",&n) && n ){
        ans = 1;
        ck = 0;
    
        for(i=0;i<n;i++){
            scanf("%lf%lf",&(P+i)->x,&(P+i)->y);
            
            for(j=i-1;j>=0;j--){
                xx = (P+i)->x - (P+j)->x;
                yy = (P+i)->y - (P+j)->y;
                dist2 = xx * xx + yy * yy;   
                
                if ( dist2 <= 4.0 + EPS ){
					midx = ( (P+i)->x + (P+j)->x ) / 2.0;
					midy = ( (P+i)->y + (P+j)->y ) / 2.0;

					if ( isZero(yy) ){
						(Cen+ck)->x = midx;
						(Cen+ck)->y = midy + sqrt( 1.0 - dist2 / 4.0 );
						ck++;
					}else{
						xtmp = yy * sqrt( ( 1.0 - dist2 / 4.0 ) / dist2 );
						(Cen+ck)->x = midx + xtmp;
						(Cen+ck)->y = midy - xtmp * xx / yy;
						ck++;
					}
                }      
            }                 
        } 
        
        //对每一个园计算覆盖点数 
        for(i=0;i<ck;i++){
           tmp = 0;
           for(j=0;j<n;j++){
               xx = (Cen+i)->x - (P+j)->x;
               yy = (Cen+i)->y - (P+j)->y;
               if ( xx * xx + yy * yy <= 1.0 + EPS )
                   tmp++;                 
           }  
           if ( tmp > ans ) ans = tmp;           
        }      
        
        printf("%d\n",ans);
    }
    
    return 0;    
}
