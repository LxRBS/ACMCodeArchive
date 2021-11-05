#include <cstdio>
#include <algorithm>
using namespace std;

struct _t{
    int a[6];//圆盘的结构
    int up;  //最上边的序号
}Piece[7];

//将t旋转，使得n到达pos位置,pos分别为0,1,2,3,4,5
void rotate(int n,int pos,_t&t){
    //找到n的相对于当前up的位置
    int ppos = 0;
    while( t.a[(t.up+ppos)%6] != n ) ++ppos;

    //旋转
    t.up += ppos - pos;
    if ( t.up < 0 ) t.up += 6;
    t.up %= 6;
}

bool Flag[7];//标志位
int PosIdx[7];//记录位置上所放的圆盘编号
bool isAns;//是否得到答案

//判断放下的盘与相邻的盘位置是否吻合
//deep为当前已经放好的，idx为要放的盘
bool isValid(int deep,int idx){
    if ( 0 == deep ) return true;

    _t const& a = Piece[PosIdx[deep]];
    _t const& b = Piece[idx];

    if ( 1 == deep )
        return a.a[(a.up+2)%6] == b.a[(b.up+5)%6];

    if ( 2 == deep )
        return a.a[(a.up+3)%6] == b.a[b.up+0];

    if ( 3 == deep )
        return a.a[(a.up+4)%6] == b.a[(b.up+1)%6];

    if ( 4 == deep )
        return a.a[(a.up+5)%6] == b.a[(b.up+2)%6];

    //当deep为5时，需要判断两个相邻的盘
    if ( a.a[a.up+0] != b.a[(b.up+3)%6] ) return false;

    _t const& t = Piece[PosIdx[1]];
    return t.a[(t.up+4)%6] == b.a[(b.up+1)%6];
}

//deep为搜索深度
void dfs(int deep){
    if ( 6 == deep ){isAns=true;return;}

    //取出第0个盘的deep位置的数
    _t const& pt = Piece[PosIdx[0]];
    int t = pt.a[(pt.up+deep)%6];

    for(int i=0;i<7;++i){
        if( Flag[i] ) continue;

        //将第i个盘旋转至合适位置
        rotate(t,(deep+3)%6,Piece[i]);

        //判断该盘与另一个盘的位置是否吻合
        if ( !isValid(deep,i) ) continue;

        //递归
        Flag[i] = true;
        PosIdx[deep+1] = i;
        dfs(deep+1);
        if ( isAns ) return;
        Flag[i] = false;
    }
}

int main(){
    int nofcase;
    scanf("%d",&nofcase);
    for(int kase=1;kase<=nofcase;++kase){
        for(int i=0;i<7;++i){
            for(int j=0;j<6;++j)scanf("%d",&Piece[i].a[j]);
            Piece[i].up = 0;
        }

        fill(Flag,Flag+7,false);
        isAns = false;

        //将第i个盘放在中间
        for(int i=0;i<7;++i){
            //将1旋转至最上
            rotate(1,0,Piece[i]);
            Flag[i] = true;
            PosIdx[0] = i;
            dfs(0);
            if ( isAns ) break;
            Flag[i] = false;
        }

        printf("Case %d:",kase);
        if ( isAns )for(int i=0;i<7;++i)printf(" %d",PosIdx[i]);
        else printf(" No solution");
        printf("\n");
    }
    return 0;
}
