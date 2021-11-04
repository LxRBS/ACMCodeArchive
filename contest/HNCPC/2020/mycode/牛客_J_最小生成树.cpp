/**
    ����һ������ͼ�����i���ߵı�ȨΪai+bi*x������xΪδ֪��
    ��xȡ��[L, R]ʱ�����Եõ���ͼ��n��MST
    ����n��MST�е���Сֵ
    ��������x�µ�һ��֧��������߼��ϼ���E��Ȩֵ����W(x)=aE+bE*x
    ���ڿ��ǵ�x+1ʱ����ȻȡE����Ȩֵ����W(x+1)=aE+bE*x+bE��
    ���������ֿ��ܣ�
    һ����W(x)>=W(x+1)��������£��׵�W(x+1)>=W(x+2)>=...
    ˵��x�϶�ȡ������Сֵ��ֻ������Rȡ����
    ��һ����W(x)<W(x+1)��������£���Ȼ��W(x)>W(x-1)>...
    ����Lȡ����
    ����ֻ�����˵㼴�ɡ�
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long llt;

int const SIZE = 200010;

int Father[SIZE];

void init(int n){for(int i=1;i<=n;++i)Father[i]=i;}
int find(int x){return x==Father[x]?x:Father[x]=find(Father[x]);}
void unite(int x,int y){Father[find(y)]=find(x);}

int N, M, L, R;
struct _t{
    int from, to;
    llt w;
}A[SIZE],B[SIZE];

bool operator < (const _t&a, const _t&b){
    return a.w < b.w;
}

llt proc(){
    init(N);
    sort(A,A+M);
    llt a = 0LL;
    int cnt = 1;
    for(int i=0;i<M;++i){
        if(find(A[i].from)==find(A[i].to)) continue;

        unite(A[i].from, A[i].to);
        a += A[i].w;
        if(++cnt==N) break;
    }

    init(N);
    sort(B,B+M);
    llt b = 0LL;
    cnt = 1;
    for(int i=0;i<M;++i){
        if(find(B[i].from)==find(B[i].to)) continue;

        unite(B[i].from, B[i].to);
        b += B[i].w;
        if(++cnt==N) break;
    }

    return min(a, b);
}

int main(){
    //freopen("1.txt","r",stdin);
    while(4==scanf("%d%d%d%d",&N,&M,&L,&R)){
        for(int u,v,a,b,i=0;i<M;++i){
            scanf("%d%d%d%d",&u,&v,&a,&b);
            A[i].from = B[i].from = u;
            A[i].to = B[i].to = v;
            A[i].w = a + (llt)b * L;
            B[i].w = a + (llt)b * R;
        }
        printf("%lld\n", proc());
    }
    return 0;
}
