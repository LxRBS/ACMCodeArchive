/*
     ���ֲ�����
     ��ָ��Ԫ�ؼ�������
     ��ָ��Ԫ�ص�������
     ���a��ĵ�kС���������������⣩

     Ԫ��ֵ��������(0,100000)
     ���Խ�Ԫ�صĸ�������Դ���鼰��״����
     ÿ����һ��e�����൱��A[e]Ҫ��1
     ÿɾ��һ��e���൱��A[e]Ҫ��1
     ��a��ĵ�kС���������൱������״�������ҵ�һ���±�x��
     ʹ��sum[a+1...x]=k
*/
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

int const SIZE = 100010;
int A[SIZE];//Դ����
int C[SIZE];//��״����

inline int lowbit(int x){return x&-x;}

int query(int x){
    int ans = 0;
    for(int i=x;i>0;i-=lowbit(i)) ans += C[i];
    return ans;
}

inline int query(int s,int e){return query(e)-query(s-1);}

void modify(int x,int delta,int n){
    for(int i=x;i<=n;i+=lowbit(i)) C[i] += delta;
}

//�ұ�a��ĵ�k����
int proc(int a,int k){
    if ( query(a+1,99999) < k ) return -1;
    int left = a, right = 99999, mid;
    do{
        mid = ( left + right ) >> 1;
        if ( query(a+1,mid) < k ) left = mid + 1;
        else right = mid - 1;
    }while(left<=right);
    return left;
}

int main(){
    //freopen("1.txt","r",stdin);

    int m,cmd,a,k;
    while( 1 == scanf("%d",&m) ){
        fill(A,A+SIZE,0);
        fill(C,C+SIZE,0);

        while(m--){
            scanf("%d%d",&cmd,&a);
            if ( 0 == cmd ){//push
                modify(a,1,99999);
                ++A[a];
            }else if ( 1 == cmd ){//pop
                if ( 0 == A[a] ){
                    puts("No Elment!");
                }else{
                    --A[a];
                    modify(a,-1,99999);
                }
            }else{
                scanf("%d",&k);
                int ans = proc(a,k);
                if ( -1 == ans ) puts("Not Find!");
                else printf("%d\n",ans);
            }
        }
    }
    return 0;
}
