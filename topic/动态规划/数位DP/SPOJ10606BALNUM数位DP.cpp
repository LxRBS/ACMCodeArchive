/*
    ����Ϊÿһ������������ż������ÿһ��ż��������������
    ��[s,e]֮�������������
*/

#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

typedef long long llt;
typedef unsigned long long ull;

int const POW_OF_3[] = {
    1,3,9,27,81,81*3,81*9,81*27,81*81,81*81*3
};

//Dij��i��ʾ���ȣ�j��ʾ��Ӧ���ֵĳ��������ʹ��3���Ʊ�ʾ��0��ʾû�У�1��ʾ������2��ʾż��
llt D[22][59100];
int Dig[100];

//pos��ʾ��ǰ�������λ��ֱ��0
//pre��ʾ֮ǰ�����
//lead��ʾ�Ƿ�Ϊǰ��0
//limit��ʾ�Ƿ�Ҫ�����Ͻ�
llt dfs(int pos,int pre,bool lead,bool limit){
    //���һ�£��Ƿ�Ϸ�
    if ( -1 == pos ) {
        //pre%3�����0�Ͳ������ۣ�����iΪ����ʱ����������2��iΪż��ʱ����������1
        for(int i=0;pre;++i,pre/=3){
            if ( ( pre % 3 ) && ( ( pre % 3 ) & 1 ) == ( i & 1 )  ){
                return 0;
            }
        }
        return 1;
    }

    //���û�����ƣ�����ǰ���Ѿ����D����ֱ�ӷ���
    if ( !lead && !limit && -1 != D[pos][pre] ) return D[pos][pre];

    int last = limit ? Dig[pos] : 9;
    llt ans = 0;

    //�ݹ�����
    int tmp = 0, npre;
    for(int i=0;i<=last;++i){
        if ( lead && 0 == i ) ans += dfs(pos-1,pre,true,limit&&i==Dig[pos]);
        else {
            npre = pre;
            tmp = npre / POW_OF_3[i] % 3;
            npre -= tmp * POW_OF_3[i];
            if ( 2 == tmp ) tmp = 1;
            else tmp += 1;
            npre += tmp * POW_OF_3[i];
            ans += dfs(pos-1,npre,false,limit&&i==Dig[pos]);
        }
    }

    return lead||limit?ans:D[pos][pre]=ans;
}

//��[1,n]�������������ж��ٸ�
llt ddp(ull n){
    int k = 0;
    while(n){
        Dig[k++] = n % 10;
        n /= 10;
    }
    llt tmp = dfs(k-1,0,true,true);
    return tmp;
}

int main(){
    //freopen("1.txt","r",stdin);

    memset(D,-1,sizeof(D));

    int kase;
    scanf("%d",&kase);
    ull a,b;
    while(kase--){
        scanf("%llu%llu",&a,&b);
        printf("%lld\n",ddp(b)-ddp(a-1));
    }
    return 0;
}
