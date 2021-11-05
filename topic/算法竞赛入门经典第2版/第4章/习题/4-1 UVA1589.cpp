/**
  中国象棋，问当前局面是否把黑方将死
*/
#include <cstdio>
#include <cstring>

int const DR[] = {-2,-2,-1,1,2,+2,+1,-1};
int const DC[] = {-1,+1,+2,2,1,-1,-2,-2};//horse's move
int const DDR[] = {-1,-1,0,0,1,+1,00,00};
int const DDC[] = {00,00,1,1,0,00,-1,-1};//horse's leg

int N,GR,GC;
int Row[10],Col[10];
char B[20][20];
bool read(){
    scanf("%d%d%d",&N,&GR,&GC);
    if (0==N&&0==GR&&0==GC) return false;

    memset(B,0,sizeof(B));
    char a[3];
    for(int i=0;i<N;++i){
        scanf("%s%d%d",a,Row+i,Col+i);
        B[Row[i]][Col[i]] = *a;
    }
    return true;
}
bool isAttacked(int targetR,int targetC,char ch,int row,int col){
    switch(ch){
    case 'G':{
        if ( targetC != col ) return false;
        for(int r=targetR+1;r<row;++r)if(B[r][col])return false;
        return true;
    }break;
    case 'R':{
        if ( targetR == row ){
            int s = targetC < col ? targetC : col;
            int e = targetC > col ? targetC : col;
            for(int c=s+1;c<e;++c)if(B[row][c])return false;
            return true;
        }else if ( targetC == col ){
            int s = targetR < row ? targetR : row;
            int e = targetR > row ? targetR : row;
            for(int r=s+1;r<e;++r)if(B[r][col])return false;
            return true;
        }else{
            return false;
        }
    }break;
    case 'H':{
        for(int i=0;i<8;++i){
            int dr = row + DR[i];
            int dc = col + DC[i];
            int ddr = row + DDR[i];
            int ddc = col + DDC[i];
            if ( dr == targetR && dc == targetC && B[ddr][ddc] == '\0' ) return true;
        }
        return false;
    }break;
    case 'C':{
        if ( targetR == row ){
            int s = targetC < col ? targetC : col;
            int e = targetC > col ? targetC : col;
            int k = 0;
            for(int c=s+1;c<e;++c)if(B[row][c])++k;
            return 1 == k;
        }else if ( targetC == col ){
            int s = targetR < row ? targetR : row;
            int e = targetR > row ? targetR : row;
            int k = 0;
            for(int r=s+1;r<e;++r)if(B[r][col])++k;
            return 1 == k;
        }else{
            return false;
        }
    }break;
    default:while(1);
    }
}
bool isAttacked(int targetR,int targetC){
    for(int i=0;i<N;++i){
        if ( Row[i] == targetR && Col[i] == targetC ) continue;
        if ( isAttacked(targetR,targetC,B[Row[i]][Col[i]],Row[i],Col[i]) ) return true;
    }
    return false;
}
int DGR[] = {-1,1,0,0};
int DGC[] = {0,0,-1,1};
bool proc(){
     for(int i=0;i<4;++i){
        int dr = GR + DGR[i];
        int dc = GC + DGC[i];
        if ( dr < 1 || dr > 3 || dc < 4 || dc > 6 ) continue;
        if ( !isAttacked(dr,dc) ) return false;
     }
     return true;
}
int main(){
    //freopen("1.txt","r",stdin);
    while( read() ) printf(proc()?"YES\n":"NO\n");
    return 0;
}
