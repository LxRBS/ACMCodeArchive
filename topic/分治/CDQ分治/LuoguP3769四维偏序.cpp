#include <bits/stdc++.h>
using namespace std;

typedef long long llt;
int const SIZE = 50010;

int WCnt;
int BIT[SIZE];

inline int lowbit(int x){return x & -x;}
void modify(int pos, int delta){
    for(;pos<=WCnt;pos+=lowbit(pos))BIT[pos] = max(BIT[pos], delta);
}
void modify(int pos){
    for(;pos<=WCnt;pos+=lowbit(pos))BIT[pos] = 0;
}
int query(int pos){
    int ans = 0;
    for(;pos;pos-=lowbit(pos)) ans = max(ans, BIT[pos]);
    return ans;
}
struct cdq_t{
    int x,y,z,w;
    int cnt;
    int *pans;
    bool b;
    void get(){
        scanf("%d%d%d%d",&x,&y,&z,&w);
    }
    bool operator < (const cdq_t &rhs)const{
        if(x!=rhs.x) return x < rhs.x;
        if(y!=rhs.y) return y < rhs.y;
        if(z!=rhs.z) return z < rhs.z;
        return w < rhs.w;
    }
    bool operator == (const cdq_t &rhs)const{
        return x==rhs.x&&y==rhs.y&&z==rhs.z&&w==rhs.w;
    }
}A[SIZE];

bool cmp2(const cdq_t &lhs, const cdq_t &rhs){
    if(lhs.y!=rhs.y) return lhs.y < rhs.y;
    if(lhs.x!=rhs.x) return lhs.x < rhs.x;
    if(lhs.z!=rhs.z) return lhs.z < rhs.z;
    return lhs.w < rhs.w;
}

bool cmp3(const cdq_t &lhs, const cdq_t &rhs){
    if(lhs.z!=rhs.z) return lhs.z < rhs.z;
    if(lhs.x!=rhs.x) return lhs.x < rhs.x;
    if(lhs.y!=rhs.y) return lhs.y < rhs.y;
    return lhs.w < rhs.w;
}


int Ans[SIZE];
int N, W[SIZE];

void CDQ2(int s, int e){
    if(s>=e) return;

    int mid = (s + e) >> 1;
    CDQ2(s, mid);

    sort(A+s,A+mid+1,cmp3); // 两段分别按第三维坐标排序
    sort(A+mid+1,A+e+1,cmp3);

    int a = s, b = mid+1, t = s;
    while(a<=mid&&b<=e){
        if(A[a].z<=A[b].z){
            if(A[a].b){
                modify(A[a].w, *A[a].pans);
            }
            ++a;
        }else{
            if(!A[b].b){
                *A[b].pans = max(*A[b].pans, query(A[b].w) + A[b].cnt);
            }
            ++b;
        }
    }
    while(b<=e){
        if(!A[b].b){
            *A[b].pans = max(*A[b].pans, query(A[b].w) + A[b].cnt);
        }
        ++b;
    }
    for(int i=s;i<a;++i){
        if(A[i].b){
            modify(A[i].w);
        }
    }

    sort(A+mid+1, A+e+1, cmp2);
    CDQ2(mid+1, e);
}

void CDQ(int s, int e){
    if(s>=e) return;

    int mid = (s + e) >> 1;
    CDQ(s, mid);

    for(int i=s;i<=e;++i){
        A[i].b = i <= mid ? 1 : 0;
    }
    sort(A+s, A+e+1, cmp2); // 进入第二层CDQ前，要按第二维坐标排序
    CDQ2(s, e);

    sort(A+s, A+e+1); // 再排回来
    CDQ(mid+1, e);
}

int main(){
    //freopen("1.txt","r",stdin);
    scanf("%d", &N);
    for(int i=1;i<=N;++i){
        A[i].get();
        W[i] = A[i].w;
        A[i].cnt = 1;
    }

    sort(W+1, W+N+1);
    WCnt = unique(W+1, W+N+1) - W - 1;

    sort(A+1, A+N+1);
    int k = 1;
    for(int i=2;i<=N;++i){
        if(A[k]==A[i]){
            ++A[k].cnt;
        }else{
            A[++k] = A[i];
        }
    }
    N = k;
    for(int i=1;i<=N;++i){
        A[i].w = lower_bound(W+1,W+WCnt+1,A[i].w) - W;
        *(A[i].pans = Ans + i) = A[i].cnt;
    }
    CDQ(1, N);
    cout<<*max_element(Ans+1, Ans+N+1)<<endl;
    return 0;
}
