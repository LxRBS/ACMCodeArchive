/**
    ����d��s��Ҫ����һ����С������d�ı����Ҹ�λ��֮��Ϊs
    dΪ500��sΪ5000
    ��DijΪģd����Ϊi�Һ�Ϊj����Сֵ������DP���ɡ�
*/
#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;

///Dij��ʾ����Ϊi��Ϊj����Сֵ
bool D[510][5010];
pii Path[510][5010];//·��
char CH[510][5010];

void output(int d,int s){
    pii const& p = Path[d][s];
    if(0==p.first&&0==p.second){
        putchar(CH[d][s]);
        return;
    }
    output(p.first,p.second);
    putchar(CH[d][s]);
}

void proc(int d,int s){
    queue<pii> q;
    q.push(pii({0,0}));
    D[0][0] = true;
    while(!q.empty()){
        pii h = q.front();
        q.pop();
        for(int i=0;i<10;++i){
            int ni = (h.first * 10 + i) % d;
            int nj = h.second + i;
            if(nj>s) break;
            if(!D[ni][nj]){
                D[ni][nj] = true;
                q.push(pii({ni,nj}));
                Path[ni][nj] = pii({h.first,h.second});
                CH[ni][nj] = i + '0';
            }
        }
    }

    if(!D[0][s]) {
        puts("-1");
        return;
    }

    output(0,s);
    printf("\n");
}

int main(){
    //freopen("1.txt","r",stdin);
    int d,s;
    scanf("%d%d",&d,&s);
    proc(d,s);
    return 0;
}
