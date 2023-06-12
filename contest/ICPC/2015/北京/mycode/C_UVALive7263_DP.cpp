/**
   只包含数字1-6的字符串，支持2种操作
   1. 一个数字变成另一个数字
   2. 一种数字变成另一种数字
   给定源和目标，问最少要多少操作
   长度不超过110
   猜测1/2操作的顺序并不重要
   因此只搜索2操作，1操作直接计算即可
   预处理只用2操作从123456到其他所有可能的情况
*/

#include <stdio.h>
#include <string.h>
#include <queue>
#include <algorithm>
using namespace std;

//计算字符串a、b不同的字母个数
int cha(char a[],char b[]){
    int ans = 0;
    for(char *pa=a,*pb=b;*pa;++pa,++pb){
        if(*pa!=*pb){
            ++ans;
        }
    }
    return ans;
}

//把所有的old变成nv
int f(int const a[],int old,int nv){
    int ans = 0;
    for(int i=5;i>=0;--i){
        ans = ans * 10 + (a[i]==old?nv:a[i]);
    }
    return ans;
}

//一共有6^6个状态，从111111到666666
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

        //最多36种变化
        for(int newValue,old=1;old<=6;++old)if(flag[old])for(int nv=1;nv<=6;++nv){
             if(-1==D[newValue = f(a,old,nv)]){
                D[newValue] = step + 1;
                q.push(State[SCnt++]=newValue);
             }
        }
    }
}

char A[120],B[120];

//将B中的123456变成state，然后看与A相差多少
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
            //把B中的123456变成state
            int state = State[i];
            
            //然后看变完以后的B与A差多少
            int tmp = D[state]+f(state);
            if(tmp<ans){
                ans = tmp;
                //printf("%d\n",state);
            }
        }
        printf("%d\n",ans);
    }
}