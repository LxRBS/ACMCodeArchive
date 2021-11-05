/**
   ֻ��������1-6���ַ�����֧��2�ֲ���
   1. һ�����ֱ����һ������
   2. һ�����ֱ����һ������
   ����Դ��Ŀ�꣬������Ҫ���ٲ���
   ���Ȳ�����110
   �²�1/2������˳�򲢲���Ҫ
   ���ֻ����2������1����ֱ�Ӽ��㼴��
   Ԥ����ֻ��2������123456���������п��ܵ����
*/

#include <stdio.h>
#include <string.h>
#include <queue>
#include <algorithm>
using namespace std;

//�����ַ���a��b��ͬ����ĸ����
int cha(char a[],char b[]){
    int ans = 0;
    for(char *pa=a,*pb=b;*pa;++pa,++pb){
        if(*pa!=*pb){
            ++ans;
        }
    }
    return ans;
}

//�����е�old���nv
int f(int const a[],int old,int nv){
    int ans = 0;
    for(int i=5;i>=0;--i){
        ans = ans * 10 + (a[i]==old?nv:a[i]);
    }
    return ans;
}

//һ����6^6��״̬����111111��666666
int State[50000];
int SCnt = 0;
int D[674322];
void bfs(){
    memset(D,-1,sizeof(D));

    queue<int> q;
    q.push(123456);
    D[State[SCnt++]=123456] = 0;

    int h,step;
    while(!q.empty()){
        step = D[h = q.front()];
        q.pop();

        bool flag[7] = {false};
        int a[6],k=0;
        while(h){
            flag[a[k++] = h % 10]=true;
            h /= 10;
        }

        //���36�ֱ仯
        for(int newValue,old=1;old<=6;++old)if(flag[old])for(int nv=1;nv<=6;++nv){
             if(-1==D[newValue = f(a,old,nv)]){
                D[newValue] = step + 1;
                q.push(State[SCnt++]=newValue);
             }
        }
    }
}

char A[120],B[120];

//��B�е�123456���state��Ȼ����A������
int f(int state){
    char tmp[120];
    strcpy(tmp,B);

    int n = state;
    int a[10]={0},k=6;
    while(n){
        a[k--] = n % 10;
        if(n%10<1||n%10>6)while(1);
        n /= 10;
    }

    for(char *p=tmp;*p;++p){
        *p = a[*p-'0'] + '0';
    }

    return cha(A,tmp);
}
int main(){
    //freopen("1.std.in","r",stdin);
    bfs();
    while(EOF!=scanf("%s%s",A,B)){
        int ans = cha(A,B);

        for(int i=0;i<SCnt;++i){
            //��B�е�123456���state
            int state = State[i];
            
            //Ȼ�󿴱����Ժ��B��A�����
            int tmp = D[state]+f(state);
            if(tmp<ans){
                ans = tmp;
                //printf("%d\n",state);
            }
        }
        printf("%d\n",ans);
    }
}
