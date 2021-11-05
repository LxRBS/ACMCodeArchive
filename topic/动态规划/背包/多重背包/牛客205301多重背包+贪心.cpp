/**
   ����һ���ַ�����һ��K
   ����ѡKλ����Ҫ��3������Խ��Խ��
   K���ܴܺ�����̰�İ�K����100
   Ȼ����ر���
*/
#include <bits/stdc++.h>
using namespace std;

int const SIZE = 100010;
char S[SIZE];
int N, K;
int Cnt[11];
char Ans[SIZE];

struct _t{  //����
    int a[10];//ai��ʾi������
    int left; //����
    bool flag;//������ʾ�Ƿ�����
    void init(){fill(a,a+10,0);left=0;flag=false;}
    _t():left(0),flag(false){fill(a,a+10,0);}
}D[3][SIZE];// Dij��ʾ����Ϊi������j��ʱ�����

bool operator < (const _t&lhs,const _t&rhs){
    for(int i=9;i>=0;--i){
        if(lhs.a[i]<rhs.a[i]) return true;
        else if(lhs.a[i]>rhs.a[i]) return false;
    }
    return false;
}

const _t operator * (int lhs, _t const&rhs){
    _t tmp(rhs);
    for(int i=0;i<=9;++i)tmp.a[i] *= lhs;
    tmp.left = tmp.left * lhs % 3;
    tmp.flag = true;
    return tmp;
}

typedef _t gains_t;//type of gains

//one iteration of 01 knapsack problem
//d is the result array
//maxv is the upper bound of the cost namely it is volume in classical problem
//cost is the current cost
//gains is the current gains
void zeroOneKnapsack(gains_t d[][SIZE],int maxv,int cost,gains_t const& gains){
    for(int ni,v=maxv;v>=cost;--v){
        for(int i=0;i<3;++i){//i��ʾ����
            const gains_t& rf = d[i][v-cost];
            if(rf.flag){
                _t tmp;
                for(int j=0;j<10;++j)tmp.a[j] = rf.a[j] + gains.a[j];
                tmp.flag = true;
                ni = tmp.left = (rf.left+gains.left)%3;

                if(!d[ni][v].flag || d[ni][v] < tmp){
                    d[ni][v] = tmp;
                }
            }
        }
    }
}

//one iteration of complete knapsack problem
//d is the result array
//maxv is the upper bound of the cost namely it is volume in classical problem
//cost is the current cost
//gains is the current gains
void completeKnapsack(gains_t d[][SIZE],int maxv,int cost,gains_t const&gains){
    for(int ni,v=cost;v<=maxv;++v){
        for(int i=0;i<3;++i){
            const _t& rf = d[i][v-cost];
            if(rf.flag){
                _t tmp;
                for(int j=0;j<=9;++j)tmp.a[j] = rf.a[j] + gains.a[j];
                tmp.flag = true;
                ni = tmp.left = (rf.left+gains.left)%3;

                if(!d[ni][v].flag || d[ni][v] < tmp){
                    d[ni][v] = tmp;
                }
            }
        }
    }
}

//one iteration of multiple knapsack problem
//d is the result array
//maxv is the upper bound of the cost namely it is volume in classical problem
//cost is the current cost
//gains is the current gains
//cnt is the current available count
void multipleKnapsack(gains_t d[][SIZE],int maxv,int cost,gains_t const&gains,int cnt){
    if ( cost * cnt >= maxv ){
        completeKnapsack(d,maxv,cost,gains);
        return;
    }

    for(int k=1;k<cnt;k<<=1){
        zeroOneKnapsack(d,maxv,k*cost,k*gains);
        cnt -= k;
    }

    if(cnt) zeroOneKnapsack(d,maxv,cnt*cost,cnt*gains);
}

int main(){
    //freopen("1.txt","r",stdin);
    //freopen("2.txt","w",stdout);
    gains_t gain[10];
    for(int i=0;i<10;++i){
        gain[i].flag = true;
        gain[i].left = i % 3;
        gain[i].a[i] = 1;
    }


    int nofkase;
    scanf("%d",&nofkase);

    while(nofkase--){
        fill(Cnt,Cnt+10,0);

        scanf("%s%d",S,&K);
        int original_k = K;
        N = 0;
        for(char *p=S;*p;++p){//ȷ��ÿ�����ֵ�����
            ++Cnt[*p - '0'];
            ++N;
        }

        if (K<=Cnt[9]){//ֱ�������
            fill(Ans,Ans+K,'9');
            Ans[K] = '\0';
            puts(Ans);
            continue;
        }

        //��һ��Ԥ����
        D[0][0].init();D[0][0].flag = true;
        for(int i=9;i>=0;--i){
            //����������ȡ3�ı���������Ҫ��K����1000
            int t = Cnt[i] - Cnt[i] % 3;
            if ( K - t < 100 ) break;
            //ȡt��
            D[0][0].a[i] = t;
            K -= t;
            Cnt[i] -= t;
            D[0][0].left = i * t % 3;
            break;
        }

        //��ʼ��
        D[0][1].init();D[0][2].init();
        for(int i=1;i<=K;++i){
            D[0][i].init();D[1][i].init();D[2][i].init();
        }

        //���ر���
        for(int i=0;i<=9;++i)if(Cnt[i]){
            multipleKnapsack(D,K,1,gain[i],Cnt[i]);
        }

        //�����
        const _t& rf = D[0][K];
        if(!D[0][K].flag){
            puts("-1");
            continue;
        }

        bool flag = false;
        for(int i=9;i>=1;--i){
            if(rf.a[i]) flag = true;
        }

        if(!flag){//��������û��
            if(rf.a[0] && 1==original_k){
                puts("0"); //�����0����KΪ1�����һ��
            }else{
                puts("-1");
            }
            continue;
        }

        for(int i=9;i>=0;--i){
            fill(Ans,Ans+rf.a[i],i+'0');
            *(Ans+rf.a[i]) = '\0';
            printf("%s",Ans);
        }
        printf("\n");
    }
    return 0;
}
