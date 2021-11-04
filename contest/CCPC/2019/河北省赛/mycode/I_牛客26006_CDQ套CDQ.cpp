/**
  ƽ����һ�����ǣ�ÿһ����һ������ͳ�ʼ����
  Ȼ����������ʱ���������Ա仯����MAX�Ժ��0��ʼ
  ����Q��ѯ�ʣ�ÿ����tiʱ�̾��������ǵ������ܺ�
  ���ȣ������Ƕ�άƫ��Ȼ����x,y���ڣ�
  ʱ��С����ʱ�̴�ľ���Ҫͳ�ƣ���άƫ��CDQ����
  ����ά������CDQ�������Ҫ�ֿ�ͳ��
  ʱ��ȽϽ��ţ��ƺ����ϻ�T��������A
*/
#pragma GCC optimize("-O2")
#include <bits/stdc++.h>
using namespace std;

char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)

inline int getUnsigned(){
	char ch = __hv007();
	while( ch < '0' || ch > '9' ) ch = __hv007();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = __hv007() ) && ch <= '9' ) ret = (ret<<1) + (ret<<3) + (int)(ch-'0');
	return ret;
}

typedef long long llt;
int const SIZE = 250500;

void write(llt x){if (x<10) {putchar('0'+x); return;} write(x/10); putchar('0'+x%10);}
inline void writeln(int x){ write(x); putchar('\n'); }

llt MAX;
int N, Q, QCnt;
llt Ans[SIZE]={0};

struct cdq_t{
    int time;
    int x;
    int y;
    int op; // ������1��ʾ���룬2��ʾѯ�����Ͻǣ�4��ʾѯ�ʵ�����������
    int b;
    llt* pans; // ��ס�𰸵�λ��
}A[SIZE],B[SIZE],C[SIZE];

inline bool operator < (const cdq_t&lhs, const cdq_t&rhs){
    if(lhs.x!=rhs.x) return lhs.x < rhs.x;
    if(lhs.y!=rhs.y) return lhs.y < rhs.y;
    if(lhs.time!=rhs.time) return lhs.time < rhs.time;
    return lhs.op < rhs.op; // �����һ�������������ǰ
}

inline bool cmp2 (const cdq_t&lhs, const cdq_t&rhs){
    if(lhs.x!=rhs.x) return lhs.x < rhs.x;
    if(lhs.y!=rhs.y) return lhs.y < rhs.y;
    if(lhs.time!=rhs.time) return lhs.time > rhs.time;
    return lhs.op < rhs.op; // �����һ�������������ǰ
}

void disp(int n){
    for(int i=1;i<=n;++i){
        printf("%d: %d %d %d ", i, A[i].time, A[i].x, A[i].y);
        if(A[i].op&1) puts("insert");
        else if(A[i].op&2) puts("query");
        else if(A[i].op&4) puts("q----");
        else throw runtime_error("wrong cmd.");
    }
}

void CDQ2(int s, int e, int flag){
    if(s>=e) return;
    int mid = (s+e) >> 1;
    CDQ2(s, mid, flag); CDQ2(mid+1, e, flag);

    int a = s, b = mid+1, t = s;
    int cnt = 0;
    llt sum = 0;

    while(a<=mid&&b<=e){
        if(flag&1){
            if(B[a].time<=B[b].time){
                if(B[a].op&1){ // �޸Ĳ���
                    cnt += B[a].b;
                    sum += B[a].time * B[a].b;
                }
                C[t++] = B[a++];
            }else{
                if(!B[b].b){
                    if(B[b].op&2){ // ��ѯ����������
                        *B[b].pans += cnt * (MAX-B[b].time) + sum;
                    }else if(B[b].op&4){
                        *B[b].pans -= cnt * (MAX-B[b].time) + sum;
                    }
                }
                C[t++] = B[b++];
            }
        }else{
            if(B[a].time>B[b].time){
                if(B[a].op&1){ // �޸Ĳ���
                    cnt += B[a].b;
                    sum += B[a].time * B[a].b;
                }
                C[t++] = B[a++];
            }else{
                if(!B[b].b){
                    if(B[b].op&2){ // ��ѯ����������
                        *B[b].pans += sum - cnt * B[b].time - cnt;
                    }else if(B[b].op&4){
                        *B[b].pans -= sum - cnt * B[b].time - cnt;
                    }
                }
                C[t++] = B[b++];
            }
        }
    }
    while(a<=mid){
        C[t++] = B[a++];
    }
    while(b<=e){
        if(flag&1){
            if(!B[b].b){
                if(B[b].op&2){ // ��ѯ����������
                    *B[b].pans += cnt * (MAX-B[b].time) + sum;
                }else if(B[b].op&4){
                    *B[b].pans -= cnt * (MAX-B[b].time) + sum;
                }
            }
            C[t++] = B[b++];
        }else{
            if(!B[b].b){
                if(B[b].op&2){ // ��ѯ����������
                    *B[b].pans += sum - cnt * B[b].time - cnt;
                }else if(B[b].op&4){
                    *B[b].pans -= sum - cnt * B[b].time - cnt;
                }
            }
            C[t++] = B[b++];
        }
    }
    copy(C+s,C+e+1,B+s);
}

void CDQ(int s, int e, int flag){
    if(s>=e) return;
    int mid = (s+e) >> 1;
    CDQ(s, mid, flag); CDQ(mid+1, e, flag);

    int a = s, b = mid+1, t = s;
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
    copy(B+s,B+e+1,A+s);
    CDQ2(s, e, flag);
}
int main(){
    //freopen("1.txt","r",stdin);
    N = getUnsigned();
    Q = getUnsigned();
    MAX = getUnsigned();
    for(int i=1;i<=N;++i){
        A[i].x = getUnsigned();
        A[i].y = getUnsigned();
        A[i].time = -(MAX - getUnsigned());
        A[i].op = 1;
    }
    //disp(N);
    QCnt = N;
    for(int t,xl,yl,xr,yr,i=1;i<=Q;++i){
        t = - getUnsigned();
        xl = getUnsigned();
        yl = getUnsigned();
        xr = getUnsigned();
        yr = getUnsigned();
        A[++QCnt].time=t;A[QCnt].x = xl-1;A[QCnt].y=yl-1;A[QCnt].op=2;A[QCnt].pans = Ans+i;
        A[++QCnt].time=t;A[QCnt].x = xl-1;A[QCnt].y=yr;A[QCnt].op=4;A[QCnt].pans = Ans+i;
        A[++QCnt].time=t;A[QCnt].x = xr;A[QCnt].y=yl-1;A[QCnt].op=4;A[QCnt].pans = Ans+i;
        A[++QCnt].time=t;A[QCnt].x = xr;A[QCnt].y=yr;A[QCnt].op=2;A[QCnt].pans = Ans+i;
    }

    sort(A+1, A+QCnt+1);
    CDQ(1,QCnt,1);

    sort(A+1, A+QCnt+1, cmp2);
    CDQ(1,QCnt,2);
    for(int i=1;i<=Q;++i)writeln(Ans[i]);
    return 0;
}
