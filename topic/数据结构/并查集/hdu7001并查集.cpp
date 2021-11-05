/**
  一个数组两种操作，初始全为0
  1 x: 把x位置设置为1
  2 x: 假设x位置是1，问从1位置开始向右，第一个碰到的0位置
  对每个位置，记录它最右边的1位置，可以使用并查集来优化
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

int const SIZE = 5000010;

int N;
int Father[SIZE];

int find(int x){return Father[x]==x?x:Father[x]=find(Father[x]);}
void unite(int x, int y){
    x = find(x); y = find(y);
    if(x<y) swap(x, y);
    Father[y] = x;
}

int main(){
    //freopen("1.txt","r",stdin);
    N = getUnsigned();
    for(int tmp, cmd, x, qi=1;qi<=N;++qi){
            if(qi==10){
                int x=3;
            }
        if(1==(cmd=getUnsigned())){
            if(0==Father[x=getUnsigned()]){
                Father[x] = x;
                if(Father[x-1]) unite(x, x-1);
                if(Father[x+1]) unite(x, x+1);
            }
        }else{
            if((tmp=find(1))<(x=getUnsigned())-1) {
                printf("%d\n", tmp+1);
            }else{
                printf("%d\n", (tmp=find(x+1))?tmp+1:x+1);
            }
        }
    }
    return 0;
}
