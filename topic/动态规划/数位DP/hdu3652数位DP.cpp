/*
    ����Ϊ����13���ܱ�13��������
    ��[s,e]֮���ж��ٸ����Ƿ���������
*/

#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

typedef long long llt;

//Dijkw��i��ʾ���ȣ�j��ʾǰһλ��k��ʾ������w��ʾ�Ƿ���ֹ�13
llt D[40][10][13][2];
int Dig[100];

//pos��ʾ��ǰ�������λ��ֱ��0
//pre��ʾ֮ǰ��λ
//left��ʾ��ǰ��13������
//statusΪ�Ƿ���ֹ�13
//limit��ʾ�Ƿ�Ҫ�����Ͻ�
llt dfs(int pos,int pre,int left,bool status,bool limit){
    //���һ�£��Ƿ�Ϸ�
    if ( -1 == pos ) return status&&0==left?1:0;

    //���û�����ƣ�����ǰ���Ѿ����D����ֱ�ӷ���
    if ( !limit && -1 != D[pos][pre][left][status] ) return D[pos][pre][left][status];

    int last = limit ? Dig[pos] : 9;
    llt ans = 0;

    //�ݹ�����
    for(int i=0;i<=last;++i){
        ans += dfs(pos-1,i,(left*10+i)%13,status||(1==pre&&3==i),limit&&i==last);
    }

    return limit?ans:D[pos][pre][left][status]=ans;
}

//��[1,n]�������������ж��ٸ�
llt ddp(llt n){
    int k = 0;
    while(n){
        Dig[k++] = n % 10;
        n /= 10;
    }
    llt tmp = dfs(k-1,0,0,false,true);
    return tmp;
}

int main(){
    //freopen("1.txt","r",stdin);

    memset(D,-1,sizeof(D));

    llt a;
    while(1 == scanf("%I64d",&a)){
        printf("%I64d\n",ddp(a));
    }
    return 0;
}
