/**
  ƽ����һ�����ǣ�ÿһ����һ������ͳ�ʼ����
  Ȼ����������ʱ���������Ա仯����MAX�Ժ��0��ʼ
  ����Q��ѯ�ʣ�ÿ����tiʱ�̾��������ǵ������ܺ�
  ���ȣ������Ƕ�άƫ��Ȼ����x,y���ڣ�
  ʱ��С����ʱ�̴�ľ���Ҫͳ�ƣ���άƫ��CDQ����
  �����ʱ��Ҫע��
*/
#include<bits/stdc++.h>
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

const int SIZE = 250500;
llt Cnt[SIZE], Sum[SIZE];

llt Time[SIZE];//��ɢ������
int TIdx;//��ɢ����

inline int lowbit(int x){return x&-x;}
void modify(llt *a, int i, llt x){while(i <= TIdx) a[i] += x, i += lowbit(i);return;}
llt query(llt *a, int i){llt res = 0;while(i) res += a[i], i -= lowbit(i); return res;}


int N, Q, QCnt;
llt MAX, Ans[SIZE];
struct cdq_t{
    int x, y, op;//op����������ͣ�id����һ��ѯ�ʵĳ�ʼλ��
    llt time, pos;//posΪ��ɢ����Ĳ�ѯ��/�޸ĵ�
    llt *pans;
    bool operator < (const cdq_t& a)const {
        if(x!=a.x) return x < a.x;
        if(y!=a.y) return y < a.y;
        //if(time!=a.time) return time < a.time; // ��һ�䲻�ܼ�
        return op < a.op;//���x������ͬ������Ҫ�����ڲ�ѯ
    }
}A[SIZE], B[SIZE];


void CDQ(int s, int e){
    if(s>=e) return;

    int mid = (s+e)>>1;
    CDQ(s, mid); CDQ(mid+1, e);

    int a = s, b = mid+1, t = s;
    while(a <= mid && b <= e){
        if(A[a].y <= A[b].y){
            if(A[a].op == -2){//��������
                modify(Cnt, A[a].pos, 1);
                modify(Sum, A[a].pos, A[a].time);
            }
            B[t++] = A[a++];
        }
        else{
            if(A[b].op != -2){
                llt v = query(Sum, TIdx);//�ܵĳ�ʼ��ֵ
                llt cnt1 = query(Cnt, TIdx);//�ܵ�����
                llt cnt2 = query(Cnt, A[b].pos);//��[0, MAX-time]������
                //Ans[A[b].id] += A[b].op*( v + cnt1*(A[b].time) - (cnt1 - cnt2)*(MAX+1) );
                //*A[b].pans += A[b].op*( v + cnt1*(A[b].time) - (cnt1 - cnt2)*(MAX+1) );
                *A[b].pans += A[b].op * (v + cnt2*MAX-cnt1*A[b].time-(cnt1-cnt2));
            }
            B[t++] = A[b++];
        }
    }
    while(b <= e){//�ȰѲ�ѯ������
        if(A[b].op != -2){
            llt v = query(Sum, TIdx);
            llt cnt1 = query(Cnt, TIdx), cnt2 = query(Cnt, A[b].pos);
            //Ans[A[b].id] += A[b].op*( v + cnt1*(A[b].time) - (cnt1 - cnt2)*(MAX+1) );
            //*A[b].pans += A[b].op*( v + cnt1*(A[b].time) - (cnt1 - cnt2)*(MAX+1) );
            *A[b].pans += A[b].op * (v + cnt2*MAX-cnt1*A[b].time-(cnt1-cnt2));
        }
        B[t++] = A[b++];
    }
    for(int i = s; i < a; ++i){//ɾ��֮ǰ�ĸ���
        if(A[i].op == -2){
            modify(Cnt, A[i].pos, -1);
            modify(Sum, A[i].pos, -A[i].time);
        }
    }
    while(a <= mid) B[t++] = A[a++];//�ٰ����ʣ��Ĵ�����
    copy(B+s, B+e+1, A+s);
}


int main(){
    //freopen("1.txt","r",stdin);
    N = getUnsigned();
    Q = getUnsigned();
    MAX = getUnsigned();
	TIdx = 0;
	for(int i = 1; i <= N; ++i){
        A[i].x = getUnsigned();
        A[i].y = getUnsigned();
        Time[TIdx++] = A[i].time = getUnsigned() - MAX;
        A[i].op = -2;
	}
	QCnt = N;
	for(int t,x1,y1,x2,y2,i = 1; i <= Q; ++i){
        t = getUnsigned();
        x1 = getUnsigned();
        y1 = getUnsigned();
        x2 = getUnsigned();
        y2 = getUnsigned();

        A[++QCnt].pans = Ans+i, A[QCnt].op = 1, A[QCnt].x = x1 - 1, A[QCnt].y = y1 - 1, A[QCnt].time = -t;
        A[++QCnt].pans = Ans+i, A[QCnt].op = 1, A[QCnt].x = x2, A[QCnt].y = y2, A[QCnt].time = -t;
        A[++QCnt].pans = Ans+i, A[QCnt].op = -1, A[QCnt].x = x2, A[QCnt].y = y1 - 1, A[QCnt].time = -t;
        A[++QCnt].pans = Ans+i, A[QCnt].op = -1, A[QCnt].x = x1 - 1, A[QCnt].y = y2, A[QCnt].time = -t;
        Time[TIdx++] =  - t;
	}

	sort(A+1, A+QCnt+1);
	sort(Time, Time+TIdx);
	TIdx = unique(Time,Time+TIdx) - Time;
	for(int i = 1; i <= QCnt; ++i) A[i].pos = lower_bound(Time,Time+TIdx, A[i].time) - Time + 1;
	CDQ(1, QCnt);
	for(int i = 1; i <= Q; ++i) printf("%lld\n", Ans[i]);
}

