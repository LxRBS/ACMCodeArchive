#include <cstdio>
#include <cstring>

//这是一个结构体的定义，该结构体有2个成员，分别是w和h，这个结构体表示矩形类型
struct Rect{
    int w,h;
}R[6];

bool isEq(Rect a,Rect b){
    return a.w == b.w && a.h == b.h || ( a.w == b.h && a.h == b.w );
}

int main(){
    //freopen("1.txt","r",stdin);

    while( EOF != scanf("%d%d%d%d%d%d%d%d%d%d%d%d",&R[0].w,&R[0].h
                        ,&R[1].w,&R[1].h,&R[2].w,&R[2].h,&R[3].w
                        ,&R[3].h,&R[4].w,&R[4].h,&R[5].w,&R[5].h) ){

        int k0;
        for(k0=1;k0<6;++k0){   //首先找到与第0面相等的面
            if ( isEq(R[0],R[k0]) ) break;
        }

        if ( 6 == k0 ){         
            printf("IMPOSSIBLE\n");
            continue;
        }

        int k1 = 1;           //然后确定看k1面，k1是1或者2
        if ( 1 == k0 ) k1 = 2;
        int kk1 = k1 + 1;
        for(;kk1<6;++kk1){    //查找与k1面相等的面
            if ( kk1 == k0 ) continue;
            if ( isEq(R[k1],R[kk1]) ) break;
        }

        if ( 6 == kk1 ){
            printf("IMPOSSIBLE\n");
            continue;
        }

        int k2 = 2;           //到此0和k0匹配，k1和kk1匹配
        while( k2 == k0 || k2 == k1 || k2 == kk1 ) ++k2;
        int kk2 = 0 + 1 + 2 + 3 + 4 + 5 - 0 - k0 - k1 - kk1 - k2;

        if ( !isEq(R[k2],R[kk2]) ){ //判断k2和kk2是否匹配
            printf("IMPOSSIBLE\n");
            continue;
        }

        int a = R[0].w, b = R[0].h; //确定是否只有3条边
        int c = 0;
        if ( R[k1].w == a || R[k1].w == b ) c = R[k1].h;
        else if ( R[k1].h == a || R[k1].h == b ) c = R[k1].w;

        if ( 0 == c ){
            printf("IMPOSSIBLE\n");
            continue;
        }

        printf( ( R[k2].w==c&&(R[k2].h==a||R[k2].h==b) )
               || ( R[k2].h==c&&(R[k2].w==a||R[k2].w==b) )
               ? "POSSIBLE\n" : "IMPOSSIBLE\n" );
    }

    return 0;
}
