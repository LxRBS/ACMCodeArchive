/**
    原始排列1~N，做若干次变换
    每一次变换，将k-约瑟夫环做x次
    问最后的排列
    首先求一次k-约瑟夫环，
    利用树状数组可以在n乘以log平方时间内求出一个k-约瑟夫环的置换
    然后求置换的快速幂，可以在nlogm时间完成，m是幂次
    最后求置换即可
*/
#include <bits/stdc++.h>
using namespace std;

int const SIZE = 100010;

//树状数组
int C[SIZE];
inline int lowbit(int x){return x&(-x);}
int query(int idx){
    int ans = 0;
    for(;idx>0;idx-=lowbit(idx))ans+=C[idx];
    return ans;
}
//idx位置减1
void modify(int idx,int delta,int n){
    for(;idx<=n;idx+=lowbit(idx))C[idx]+=delta;
}

//求一个K约瑟夫环的置换，需要用到树状数组
//n是总数量，k是约瑟夫参数，c是树状数组，ans是答案
void k_Josephus(int n,int k,int c[],int ans[]){
    //初始情况，1~n各有一个
    fill(C,C+n+1,0);
    for(int i=1;i<=n;++i)modify(i,1,n);
    int lastpos = 1;  //上次取出数的位置，初始为1
    for(int i=1,cnt=n;cnt>0;++i,--cnt){//cnt是当前还剩下的数量
        //每次取出的数应该是 (lastpos-1+k-1)%cnt+1
        //二分搜索，找到第一个求和为target的地方
        int target = (lastpos-1+k-1)%cnt + 1;
        int mid, left = 1, right = n;
        do{
            mid = (left + right) >> 1;
            if(query(mid)>=target) right = mid - 1;
            else left = mid + 1;
        }while(left<=right);
        //left就是答案
        lastpos = target;
        modify(ans[i] = left,-1,n);
    }
}

void disp(int const a[],int n){
    for(int i=1;i<=n;++i)cout<<a[i]<<" ";
    cout<<endl;
}

//求置换的快速幂
//a是原始置换，n是排列长度
//m是幂次，ret是结果,tmp是临时数组
//a、ret、tmp各不相同，运算完以后a会发生改变
void power(int a[],int n,int m,int ret[],int tmp[]){
    for(int i=1;i<=n;++i)ret[i]=i;
    while(m){
        if(m&1){
            for(int i=1;i<=n;++i)tmp[i] = a[ret[i]];
            copy(tmp,tmp+n+1,ret);
        }
        m>>=1;
        for(int i=1;i<=n;++i)tmp[i] = a[a[i]];
        copy(tmp,tmp+n+1,a);
    }
    return;
}

int Zhi[SIZE],Tmp[SIZE],Ans[SIZE];
int Total[SIZE];
int main(){
    //freopen("1.txt","r",stdin);
    int n,m;
    scanf("%d%d",&n,&m);

    for(int i=1;i<=n;++i)Total[i] = i;

    while(m--){
        int k,x;
        scanf("%d%d",&k,&x);
        //K约瑟夫环的置换
        k_Josephus(n,k,C,Zhi);
        //对这个置换求幂
        power(Zhi,n,x,Ans,Tmp);
        //Ans是幂次以后的置换
        for(int i=1;i<=n;++i){
            Tmp[i] = Total[Ans[i]];
        }
        copy(Tmp,Tmp+n+1,Total);
    }
    for(int i=1;i<=n;++i)printf("%d ",Total[i]);
    printf("\n");
    return 0;
}
