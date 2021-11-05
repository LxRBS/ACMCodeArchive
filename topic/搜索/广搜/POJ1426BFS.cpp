/*
    ����n����n�ı���m
    ʹ��m����0/1���
    
    ʵ���ϲ��ᳬ��longlong��Χ�����Ժܼ�
    ����C++��ʱ��G++AC
*/
#include <stdio.h>
#include <queue>
#include <algorithm>
using namespace std;

int N;
long long bfs(){
    if ( 1 == N ) return 1LL;

    queue<long long> q;
    q.push(1LL);

    long long u,v;
    while( !q.empty() ){
        u = q.front();
        q.pop();

        if ( (v = u * 10) % N == 0 ) return v;
        q.push(v);

        if ( ++v % N == 0 ) return v;
        q.push(v);
    }
}

int main(){
    while( scanf("%d",&N),N ){
        printf("%lld\n",bfs());
    }
    return 0;
}
