/**
  ����n��k����n�ܷ��ʾΪk����ͬ����֮��
  ǰk������֮����k^2�����n�����С��Ȼ��
  Ȼ��k^2��n����ż�Լ��ɡ�
  �����ż����ͬ����1+n-K^2��ȻҲ��һ�������� 
  �����滻1���ټ��ϳ�1֮���ǰk�����������ɡ�
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long llt;

bool f(int n,int k){
    llt t = (llt)k*(llt)k;
    if ( t > n ) return false;
    return !(( n - t ) & 1);
}

int main(){
    int nofkase;
    scanf("%d",&nofkase);
    while(nofkase--){
        int n,k;
        scanf("%d%d",&n,&k);
        printf(f(n,k)?"YES\n":"NO\n");
    }
    return 0;
}
