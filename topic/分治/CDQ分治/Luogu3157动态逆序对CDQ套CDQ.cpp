/**
   动态逆序对，给定一个排列，再给出顺序删掉一些数，问每次删数之前的逆序对
   按照删除的逆序，给每个数规定一个出现的时间
   则就是问Ti<Tj且Pi<Pj且Vi>Vj的数量
   或则Ti<Tj且Pi>Pj且Vi<Vj的数量
   三维偏序。
*/
#include <bits/stdc++.h>
using namespace std;

char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)

int getUnsigned(){
	char ch = __hv007();
	while( ch < '0' || ch > '9' ) ch = __hv007();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = __hv007() ) && ch <= '9' ) ret = (ret<<1) + (ret<<3) + (int)(ch-'0');
	return ret;
}

typedef long long llt;
int const SIZE = 120000;

int N, M;
llt Ans[SIZE]={0};

struct cdq_t{
    int time;
    int pos;
    int val;
    int b;
}A[SIZE],B[SIZE],C[SIZE];

bool operator < (const cdq_t&lhs, const cdq_t&rhs){
    if(lhs.time!=rhs.time) return lhs.time < rhs.time;
    if(lhs.pos!=rhs.pos) return lhs.pos < rhs.pos;
    return lhs.val < rhs.val;
}


void CDQ2(int s,int e,int flag){
    if(s==e)return;

    int mid=(s+e)>>1;
    CDQ2(s,mid,flag);CDQ2(mid+1,e,flag);

    int a=s,b=mid+1,t=s,cnt=0;
    while(a<=mid&&b<=e){
        if(flag&1){
            if(B[a].val>B[b].val){
                cnt += B[a].b;
                C[t++] = B[a++];
            }else{
                if(!B[b].b) Ans[B[b].time] += cnt;
                C[t++] = B[b++];
            }
        }else{
            if(B[a].val<B[b].val){
                cnt += B[a].b;
                C[t++] = B[a++];
            }else{
                if(!B[b].b) Ans[B[b].time] += cnt;
                C[t++] = B[b++];
            }
        }
    }
    while(a<=mid){
        cnt += B[a].b;
        C[t++] = B[a++];
    }
    while(b<=e){
        if(!B[b].b) Ans[B[b].time] += cnt;
        C[t++] = B[b++];
    }
    copy(C+s,C+e+1,B+s);
}

///flag为1时统计pos小但val大的
///flag为2时统计pos大但val小的
void CDQ(int s,int e,int flag){
    if(s==e)return;
    int mid=(s+e)>>1;
    CDQ(s,mid,flag);CDQ(mid+1,e,flag);

    int a=s, b=mid+1, t=s;
    while(a<=mid&&b<=e){
        if(flag&1){
            if(A[a].pos<=A[b].pos){
                B[t] = A[a++];
                B[t++].b = 1;
            }else{
                B[t] = A[b++];
                B[t++].b = 0;
            }
        }else{
            if(A[a].pos>A[b].pos){
                B[t] = A[a++];
                B[t++].b = 1;
            }else{
                B[t] = A[b++];
                B[t++].b = 0;
            }
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
    CDQ2(s,e,flag);
}

int Val2Pos[SIZE];
int main(){
    //freopen("1.txt","r",stdin);
    N = getUnsigned();
    M = getUnsigned();
    for(int i=1;i<=N;++i){
        A[Val2Pos[A[i].val = getUnsigned()] = A[i].pos = i].time = 1;
    }
    for(int v, i=1;i<=M;++i){
        A[Val2Pos[v = getUnsigned()]].time = M - i + 1;
    }
    sort(A, A+N+1);
    CDQ(1,N,1);

    sort(A, A+N+1);
    CDQ(1,N,2);
    for(int i=1;i<=M;++i)Ans[i] += Ans[i-1];
    for(int i=M;i>=1;--i)printf("%lld\n", Ans[i]);
    return 0;
}
