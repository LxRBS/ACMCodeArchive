/*
     ������1~N�����У�������1~M������
     ÿ�Գ������ߣ���һ���ж��ٸ�����
     ���߼���x�����߼���y
     ��(x1-x2)*(y1-y2)<0ʱ�н���
     Ҳ����˵��ÿһ���㣬�����������ж��ٸ���

     ��ά����
     ��y���������У�y��ͬx����
     ���ڵ�i��˵���������ϵĵ�ֻ������[i+1,K)֮��ĵ�
     ����Щ��֮�䣬���x�ȵ�iС����ô��ȷ��ȷΪ���ϣ�
     ���ַ�������ͳ�Ƴ��ϸ����ϣ��������������ϣ��ĵ�
*/
#include <stdio.h>
#include <math.h>
#include <algorithm>
using namespace std;

typedef long long llt;

int const SIZE = 1020;
llt C[SIZE];//��״����

inline int lowbit(int x){return x&-x;}

llt query(int idx){
    llt ans = 0;
    for(int i=idx;i>0;i-=lowbit(i))ans+=C[i];
    return ans;
}

void modify(int idx,int delta,int n){
    for(int i=idx;i<=n;i+=lowbit(i)) C[i] += delta;
}

struct _t{
    int x,y;
};

bool operator < (_t const&lhs,_t const&rhs){
    return lhs.y < rhs.y || (lhs.y==rhs.y&&lhs.x<rhs.x);
}

int N,M,K;
_t B[SIZE*SIZE];

bool read(){
    scanf("%d%d%d",&N,&M,&K);
    for(int i=0;i<K;++i)scanf("%d%d",&B[i].x,&B[i].y);
    return true;
}

int main(){
    //freopen("1.txt","r",stdin);

    int nofkase;
    scanf("%d",&nofkase);
    for(int kase=1;kase<=nofkase;++kase){
        read();
        sort(B,B+K);
        fill(C,C+SIZE,0LL);

        llt ans = 0;
        for(int i=K-1;i>=0;--i){
            ans += query(B[i].x-1);
            modify(B[i].x,1,M);
        }
        printf("Test case %d: %lld\n",kase,ans);
    }
    return 0;
}
