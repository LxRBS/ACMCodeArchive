//四点共面
#include <stdio.h>

struct point_t{
    int x,y,z;
    point_t(int xx=0,int yy=0,int zz=0):x(xx),y(yy),z(zz){}
};
point_t const ZERO(0,0,0);

bool operator == (point_t const&a,point_t const&b){
    return a.x == b.x && a.y == b.y && a.z == b.z;
}
point_t cross(point_t const&O,point_t const&A,point_t const&B){
    int xoa = A.x - O.x;
    int yoa = A.y - O.y;
    int zoa = A.z - O.z;
    int xob = B.x - O.x;
    int yob = B.y - O.y;
    int zob = B.z - O.z;
    return point_t(yoa*zob-zoa*yob,xob*zoa-xoa*zob,xoa*yob-xob*yoa);
}

point_t cross(point_t const&a,point_t const&b){
    return point_t(a.y*b.z-b.y*a.z,b.x*a.z-a.x*b.z,a.x*b.y-b.x*a.y);
}
point_t A,B,C,D;
int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        scanf("%d%d%d%d%d%d%d%d%d%d%d%d",&A.x,&A.y,&A.z,&B.x,&B.y,&B.z,&C.x,&C.y,&C.z,&D.x,&D.y,&D.z);
        printf(ZERO==cross(cross(A,B,C),cross(D,B,C))?"Yes\n":"No\n");
    }
    return 0;
}
