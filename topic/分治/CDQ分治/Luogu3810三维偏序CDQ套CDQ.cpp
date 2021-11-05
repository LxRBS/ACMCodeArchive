/// CDQÌ×CDQ£¬ÈýÎ¬Æ«ÐòÄ£°åÌâ
#include <bits/stdc++.h>
using namespace std;

int const SIZE = 120000;

int N,K;
int Ans[SIZE]={0};
int Cnt[SIZE]={0};

struct cdq_t{
    int x,y,z;
    bool b;
    int *ans;
    inline void get(){
        scanf("%d%d%d",&x,&y,&z);
        return;
    }
    bool operator==(const cdq_t &rhs)const{
        return x==rhs.x&&y==rhs.y&&z==rhs.z;
    }
    bool operator < (const cdq_t &rhs)const{
        if(x!=rhs.x) return x < rhs.x;
        if(y!=rhs.y) return y < rhs.y;
        return z < rhs.z;
    }
}A[SIZE],B[SIZE],C[SIZE];


void CDQ2(int s,int e){
    if(s==e)return;

    int mid=(s+e)>>1;
    CDQ2(s,mid);CDQ2(mid+1,e);

    int a=s,b=mid+1,t=s,cnt=0;
    while(a<=mid&&b<=e){
        if(B[a].z<=B[b].z){
            cnt += B[a].b;
            C[t++] = B[a++];
        }else{
            if(!B[b].b) *B[b].ans += cnt;
            C[t++] = B[b++];
        }
    }
    while(a<=mid){
        //cnt += B[a].b;
        C[t++] = B[a++];
    }
    while(b<=e){
        if(!B[b].b) *B[b].ans += cnt;
        C[t++] = B[b++];
    }
    copy(C+s,C+e+1,B+s);
}

void CDQ(int s,int e){
    if(s==e)return;
    int mid=(s+e)>>1;
    CDQ(s,mid);CDQ(mid+1,e);

    int a=s, b=mid+1, t=s;
    while(a<=mid&&b<=e){
        if(A[a].y<=A[b].y){
            B[t] = A[a++];
            B[t++].b = 1;
        }else{
            B[t] = A[b++];
            B[t++].b = 0;
        }
    }
    while(a<=mid){
        B[t] = A[a++];
        B[t++].b = 1;
    }
    while(b<=e){
        B[t] = A[b++];
        B[t++].b = 0;
    }
    copy(B+s, B+e+1, A+s);
    CDQ2(s,e);
}

int main(){
    scanf("%d%d",&N,&K);
    for(int i=1;i<=N;++i){
        A[i].get(),A[i].ans=&Ans[i],Ans[i]=0;
    }

    sort(A+1,A+N+1);
    for(int i=N-1;i;--i){
        if(A[i]==A[i+1]){
            *A[i].ans=*A[i+1].ans+1;
        }
    }


    CDQ(1,N);
    for(int i=1;i<=N;++i)++Cnt[Ans[i]];
    for(int i=0;i<N;++i)printf("%d\n",Cnt[i]);
    return 0;
}
