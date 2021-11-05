/*
     三种操作：
     将指定元素加入容器
     将指定元素弹出容器
     求比a大的第k小的数（题意有问题）

     元素值的区间在(0,100000)
     可以将元素的个数做成源数组及树状数组
     每加入一个e，就相当于A[e]要加1
     每删除一个e，相当于A[e]要减1
     比a大的第k小的数，就相当于在树状数组上找到一个下标x，
     使得sum[a+1...x]=k
*/
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

int const SIZE = 100010;
int A[SIZE];//源数组
int C[SIZE];//树状数组

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

//找比a大的第k个数
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
