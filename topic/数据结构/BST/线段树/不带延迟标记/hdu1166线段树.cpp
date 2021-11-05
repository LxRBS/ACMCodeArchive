#include <iostream>
using namespace std;

int const SIZE = 50004;
//用数组实现线段树
int SegTree[SIZE<<2];
int Arr[SIZE];

#define lson(x) ( ( (x) << 1 ) | 1 )
#define rson(x) ( ( (x) + 1 ) << 1 )

//确定父节点的存储值
void calDad(int root,int st[]){
    st[root] = st[lson(root)] + st[rson(root)];
}

//在st里建立线段树，保证st有足够的空间，此处保存的是区间和
void build(int root,int left,int right,int st[]){
    //如果区间宽度为1
    if ( left == right ){
        st[root] = Arr[left];
        return;
    }
    int mid = ( left + right ) >> 1;
    //递归
    build(lson(root),left,mid,st);
    build(rson(root),mid+1,right,st);
    //根据子节点信息重新计算父节点
    calDad(root,st);
}

//更新，第sn个节点上增加num个
void update(int root,int left,int right,int sn,int num,int st[]){
    //如果区间宽度为1
    if ( left == right ){
        st[root] += num;
        return;
    }
    //递归
    int mid = ( left + right ) >> 1;
    if ( sn <= mid ) update(lson(root),left,mid,sn,num,st);
    else             update(rson(root),mid+1,right,sn,num,st); 
    //根据子节点信息重新计算父节点
    calDad(root,st);
}
//查询[a,b]之间的存储值
int query(int root,int left,int right,int a,int b,int st[]){
    //如果[a,b]区间覆盖root区间
    if ( a <= left && right <= b ) return st[root];
    //递归
    int mid = ( left + right ) >> 1;
    int ans = 0;
    if ( a <= mid ) ans += query(lson(root),left,mid,a,b,st);
    if ( b > mid )  ans += query(rson(root),mid+1,right,a,b,st);
    return ans;
}

int main(){
    int n = 0,kase;
    scanf("%d",&kase);
    for(int k=1;k<=kase;++k){
        printf("Case %d:\n",k);

        scanf("%d",&n);
        for(int i=0;i<n;++i)scanf("%d",Arr+i);
        //建立线段树，序号从0开始，而题意从1开始
        build(0,0,n-1,SegTree);
        char op[10];
        while( scanf("%s",op) ){
            if ( 'E' == *op ) break;

            int a,b;
            scanf("%d%d",&a,&b);
            
            if ( 'A' == *op ){
                update(0,0,n-1,a-1,b,SegTree);
            }else if ( 'S' == *op ){
                update(0,0,n-1,a-1,-b,SegTree);
            }else{//Q
                printf("%d\n",query(0,0,n-1,a-1,b-1,SegTree));
            }
        }
    }
    return 0;
}