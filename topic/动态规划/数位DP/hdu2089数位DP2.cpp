/*
    ����4����62�����ǲ�������
    ��[s,e]֮�伪���������ж��ٸ�
*/

#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

typedef long long llt;

//Dij��ʾ����Ϊi��ǰһλΪj��������������
llt D[7][10];
int Dig[100];

//pos��ʾ��ǰ�������λ��ֱ��0
//pre��ʾǰһλ
//limit��ʾ�������Ͻ�
llt dfs(int pos,int pre,bool limit){
    if ( -1 == pos ) return 1;//�ܹ����������˵��ǰ���ÿһ�����������㣬����1��

    //���û�����ƣ�����ǰ���Ѿ����D����ֱ�ӷ���
    if ( !limit && -1 != D[pos][pre] ) return D[pos][pre];

    int last = limit ? Dig[pos] : 9;
    llt ans = 0;

    //�ݹ�����
    for(int i=0;i<=last;++i){
        if ( 4==i || (2==i&&6==pre) ) continue;

        ans += dfs(pos-1,i,limit&&(i==Dig[pos]));
    }

    return 0==limit?D[pos][pre]=ans:ans;
}

//��[1,n]�������������ж��ٸ�
llt ddp(int n){
    int k = 0;
    while(n){
        Dig[k++] = n % 10;
        n /= 10;
    }
    return dfs(k-1,0,true);
}

int main(){
    //freopen("1.txt","r",stdin);

    memset(D,-1,sizeof(D));
    int a,b;
    while( scanf("%d%d",&a,&b),a+b ){
        printf("%lld\n",ddp(b)-ddp(a-1));
    }
    return 0;
}
