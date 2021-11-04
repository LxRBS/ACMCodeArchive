/*
    ��f(y,K)=SIGMA(y��ÿ�����ֵ�K�η�)
    ���� f(233,2) = 2^2 + 3^2 + 3^2
    ���� x = f(y,K) - y
    ����x��K�����ж��ٸ�y��������
    ����ʹ�����������������֪�����10λ��
    ��A��¼ǰ5λ����fֵ��B��¼��5λ����fֵ
    ԭ���Ϊ�ж��ٸ�Ai��Bj����Ai+Bj==x
    ��A��һ�����򣬿�����10��log(10��)���
*/
#include <stdio.h>
#include <algorithm>
#include <utility>
using namespace std;
typedef long long int llt;

//A[i][j]��ʾj��i�η���ȥj
llt A[10][100000];
//B[i][j]��ʾj��i�η���ȥj*100000
llt B[10][100000];
//Pow[i][j]��ʾi��j�η�
llt Pow[10][10];
//Flag[i]��ʾA��B�ĵ�i���Ƿ�����
bool Flag[10];

llt f(llt y,int k,llt t10){
    int yy = y;
    int a[10],t=0;
    while(y){
        a[t++] = y%10;
        y/=10;
    }
    int sum = 0;
    for(int i=0;i<t;++i){
        sum += Pow[a[i]][k];
    }
    if(yy==42949&&t10==100000){
        int xxxx=1324342;
    }
    return sum - yy*t10;
}

void init(int k){
    if(Flag[k]) return;

    Flag[k] = true;
    //����A��B�ĵ�k��
    for(int n=1;n<100000;++n){
        A[k][n] = f(n,k,1);
        B[k][n] = f(n,k,100000);
    }
    sort(A[k],A[k]+100000);
}


int main(){
    //freopen("1.txt","r",stdin);
    //����Pow
    for(int i=1;i<10;++i){
        Pow[i][0] = 1;
        for(int j=1;j<10;++j){
            Pow[i][j] = Pow[i][j-1] * i;
        }
    }

    int nofkase;
    scanf("%d",&nofkase);
    for(int kase=1;kase<=nofkase;++kase){
        int x,k;
        scanf("%d%d",&x,&k);

        init(k);

        //��A[k]��B[k]�������ж���A[k][i]+B[k][j]==x
        int ans = 0;
        for(int i=0;i<100000;++i){
            llt tmp = x - B[k][i];
            pair<llt*,llt*> pp = equal_range(A[k],A[k]+100000,tmp);
            int tt = pp.second - pp.first;
            if(tt>0){
                ans += tt;
                //�������Ļ���Ҫ��1
                if(*pp.first<=0&&(0<*pp.second||pp.second==A[k]+100000)){
                    --ans;
                }

            }
        }
        printf("Case #%d: %d\n",kase,ans);
    }
    return 0;
}
