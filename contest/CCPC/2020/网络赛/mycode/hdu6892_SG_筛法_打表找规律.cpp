/**
    nim��Ϸ��ÿһ��ѡһ��ʯ�ӣ�����������ΪN��
    ������Ϊm��p��������m*p==n����m����1��
    ���ȫ1�Ͳ��ܶ��ˣ�Ϊ�䡣
    ���sqrt(1E9)���ҹ��� 
    sg(n)Ϊn�������ӵ����������ǲ����ظ���2��
*/
#include <bits/stdc++.h>
using namespace std;

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

//����ɸ��
int const SIZE = sqrt(1E9)+2;//һ��ֻɸ��30000+����
bool isComp[SIZE] = {false};//isComp[i]Ϊ��˵��i�Ǻ���
int P[SIZE];//P[i]Ϊ��i��������i��0��ʼ
int PCnt = 0;//PCnt��¼1~SIZE֮��������ĸ���
void sieve(){
    for(int i=2;i<SIZE;++i){
        if ( !isComp[i] ) P[PCnt++] = i;

        for(int j=0;j<PCnt&&i*P[j]<SIZE;++j){
            isComp[i*P[j]] = true;
            if ( 0 == i % P[j] ) break;
        }
    }
}

//��n��sgֵ��ȥ���ظ���2��Ȼ��һ���ж��ٸ�������
int sg(int n){
    if(1==n) return 0;

    int ans = (n&1) ? 0 : 1;
    while(!(n&1)) n>>=1;

    for(int i=1;i<PCnt&&P[i]*P[i]<=n;++i){
        if(n%P[i]==0){
            while(n%P[i]==0) ++ans, n /= P[i];
        }
    }

    return n==1?ans:ans+1;
}

int main(){
    //freopen("1.txt","r",stdin);
    sieve();
    char const s[2][10] = {"L", "W"};
    int nofkase = getUnsigned();
    while(nofkase--){
        int n = getUnsigned();
        int ans = 0;
        while(n--){
            ans = ans ^ sg(getUnsigned());
        }
        puts(s[ans?1:0]);
    }
    return 0;
}

