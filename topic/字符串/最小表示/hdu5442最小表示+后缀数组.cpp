#include <cstdio>

#define SIZE 40007
void dispArray(int const a[],int n){
    for(int i=0;i<n;++i)printf("%d ",a[i]);
    printf("\n");
}
//最大表示
int maxiPre(char const s[],int n){
    int i = 0, j = 1;
    int k = 0;
    while(1){
        while( s[(i+k)%n] == s[(j+k)%n] && k < n ) ++k;
        if ( k == n ) return i < j ? i : j;
        if ( s[(i+k)%n] < s[(j+k)%n] ) i += k + 1;
        else j += k + 1;
        if ( i >= n || j >= n ) return i < j ? i : j;
        if ( i == j ) ++j;
        k = 0;
    }
    return -1;//never comes
}

int const DELIMETER_CNT = 1;
//字母表的字母个数
int const ALPHA_SIZE = DELIMETER_CNT + 26;
//char转int
inline int tr(char ch){
    return ch - 'a' + 1;
}
//辅助数组，以下划线开头
int _wa[SIZE],_wb[SIZE],_wv[SIZE],_ws[SIZE];
//辅助函数
int _cmp(int const r[],int a,int b,int l){return r[a]==r[b]&&r[a+l]==r[b+l];}
//求后缀数组的倍增算法
//r: 源数组，且除r[n-1]外，其余r[i]>0
//n: r的长度
//m: r中的元素取值的上界，即任意r[i]<m
//sa:后缀数组，即结果
void da(int const r[],int n,int m,int sa[]){
    int i,j,p,*x=_wa,*y=_wb,*t;
    for(i=0;i<m;i++) _ws[i] = 0;
    for(i=0;i<n;i++) _ws[x[i] = r[i]]++;
    for(i=1;i<m;i++) _ws[i] += _ws[i-1];
    for(i=n-1;i>=0;i--) sa[--_ws[x[i]]]=i;
    for(j=1,p=1;p<n;j*=2,m=p){
        for(p=0,i=n-j;i<n;i++) y[p++]=i;
        for(i=0;i<n;i++) if(sa[i]>=j) y[p++]=sa[i]-j;
        for(i=0;i<n;i++) _wv[i]=x[y[i]];
        for(i=0;i<m;i++) _ws[i]=0;
        for(i=0;i<n;i++) _ws[_wv[i]]++;
        for(i=1;i<m;i++) _ws[i] += _ws[i-1];
        for(i=n-1;i>=0;i--) sa[--_ws[_wv[i]]] = y[i];
        for(t=x,x=y,y=t,p=1,x[sa[0]]=0,i=1;i<n;i++)
            x[sa[i]]=_cmp(y,sa[i-1],sa[i],j)?p-1:p++;
    }
    return;
}
void calHeight(int const r[],int const sa[],int n,int rank[],int height[]){
    int i,j,k=0;
    for(i=1;i<n;i++) rank[sa[i]]=i;
    for(i=0;i<n-1;height[rank[i++]]=k)
    for(k?k--:0,j=sa[rank[i]-1];r[i+k]==r[j+k];k++);
    return;
}

char A[SIZE];
int R[SIZE],SA[SIZE];
int Rank[SIZE],Height[SIZE];

//从Height数组最后往前，Height值不小于n
//序号最靠近n的
int findb(int n){
    int i = n + n;
    int k = SA[i];
    while( Height[i] >= n ){
        int t = SA[i-1];
        if ( t < n && t > k ) k = t;
        --i;
    }
    return k;
}
inline int fb(int k,int n){
    return k < 0 ? k + n : k;
}
int judge(int a,int b,int n){
    for(int i=0;i<n;++i){
        char ca = A[(a+i)%n];
        char cb = A[fb(b-i,n)];
        if ( ca > cb ) return 0;
        if ( cb > ca ) return 1;
    }
    return 2;
}
int main(){
    int tt;
    scanf("%d",&tt);
    while(tt--){
        int n;
        scanf("%d%s",&n,A);

        int a = maxiPre(A,n);

        for(int i=0;i<n;++i){
            R[i] = R[i+n] = tr(A[n-1-i]);
        }
        R[n+n] = 0;
        da(R,n+n+1,ALPHA_SIZE,SA);
        calHeight(R,SA,n+n+1,Rank,Height);

        /*
        dispArray(R,n+n+1);
        dispArray(SA,n+n+1);
        dispArray(Rank,n+n+1);
        dispArray(Height,n+n+1);
        //*/
//*
        int b = n - 1 - findb(n);

        int t = judge(a,b,n);
        if ( 0 == t ) printf("%d 0\n",a+1);
        else if ( 1 == t ) printf("%d 1\n",b+1);
        else{
            if ( a < b ) printf("%d 0\n",a+1);
            else if ( a >b ) printf("%d 1\n",b+1);
            else printf("%d 0\n",a+1);
        }//*/
    }
}
