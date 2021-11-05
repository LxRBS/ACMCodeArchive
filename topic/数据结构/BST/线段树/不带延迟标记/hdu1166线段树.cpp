#include <iostream>
using namespace std;

int const SIZE = 50004;
//������ʵ���߶���
int SegTree[SIZE<<2];
int Arr[SIZE];

#define lson(x) ( ( (x) << 1 ) | 1 )
#define rson(x) ( ( (x) + 1 ) << 1 )

//ȷ�����ڵ�Ĵ洢ֵ
void calDad(int root,int st[]){
    st[root] = st[lson(root)] + st[rson(root)];
}

//��st�ｨ���߶�������֤st���㹻�Ŀռ䣬�˴�������������
void build(int root,int left,int right,int st[]){
    //���������Ϊ1
    if ( left == right ){
        st[root] = Arr[left];
        return;
    }
    int mid = ( left + right ) >> 1;
    //�ݹ�
    build(lson(root),left,mid,st);
    build(rson(root),mid+1,right,st);
    //�����ӽڵ���Ϣ���¼��㸸�ڵ�
    calDad(root,st);
}

//���£���sn���ڵ�������num��
void update(int root,int left,int right,int sn,int num,int st[]){
    //���������Ϊ1
    if ( left == right ){
        st[root] += num;
        return;
    }
    //�ݹ�
    int mid = ( left + right ) >> 1;
    if ( sn <= mid ) update(lson(root),left,mid,sn,num,st);
    else             update(rson(root),mid+1,right,sn,num,st); 
    //�����ӽڵ���Ϣ���¼��㸸�ڵ�
    calDad(root,st);
}
//��ѯ[a,b]֮��Ĵ洢ֵ
int query(int root,int left,int right,int a,int b,int st[]){
    //���[a,b]���串��root����
    if ( a <= left && right <= b ) return st[root];
    //�ݹ�
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
        //�����߶�������Ŵ�0��ʼ���������1��ʼ
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