#include <cstdio>
#include <algorithm>
using namespace std;

struct _t{
    int a[6];//Բ�̵Ľṹ
    int up;  //���ϱߵ����
}Piece[7];

//��t��ת��ʹ��n����posλ��,pos�ֱ�Ϊ0,1,2,3,4,5
void rotate(int n,int pos,_t&t){
    //�ҵ�n������ڵ�ǰup��λ��
    int ppos = 0;
    while( t.a[(t.up+ppos)%6] != n ) ++ppos;

    //��ת
    t.up += ppos - pos;
    if ( t.up < 0 ) t.up += 6;
    t.up %= 6;
}

bool Flag[7];//��־λ
int PosIdx[7];//��¼λ�������ŵ�Բ�̱��
bool isAns;//�Ƿ�õ���

//�жϷ��µ��������ڵ���λ���Ƿ��Ǻ�
//deepΪ��ǰ�Ѿ��źõģ�idxΪҪ�ŵ���
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

    //��deepΪ5ʱ����Ҫ�ж��������ڵ���
    if ( a.a[a.up+0] != b.a[(b.up+3)%6] ) return false;

    _t const& t = Piece[PosIdx[1]];
    return t.a[(t.up+4)%6] == b.a[(b.up+1)%6];
}

//deepΪ�������
void dfs(int deep){
    if ( 6 == deep ){isAns=true;return;}

    //ȡ����0���̵�deepλ�õ���
    _t const& pt = Piece[PosIdx[0]];
    int t = pt.a[(pt.up+deep)%6];

    for(int i=0;i<7;++i){
        if( Flag[i] ) continue;

        //����i������ת������λ��
        rotate(t,(deep+3)%6,Piece[i]);

        //�жϸ�������һ���̵�λ���Ƿ��Ǻ�
        if ( !isValid(deep,i) ) continue;

        //�ݹ�
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

        //����i���̷����м�
        for(int i=0;i<7;++i){
            //��1��ת������
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
