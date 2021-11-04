/*
  ��һ����ȫͼ�����������ͼ���޹����ߣ�
  ������ͼ�Ƿ��Ǵ��ݵġ�
  ��ν���ݾ��ǣ�ab�бߡ�bc�бߣ���ac�����б�
  ����Ǵ��ݵģ�����ab��bc��ac�бߣ����cd���бߣ���bd��Ȼ�бߣ���ad��Ȼ�б�
  Ҳ����˵��a��ʼ�������������ĵ㣬·�����Ϊ1
*/
#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

int const SIZE = 2100;

char S[SIZE];
int N;
vector<int> GP[SIZE];
vector<int> GQ[SIZE];

bool Flag[SIZE];
int Q[SIZE];
int D[SIZE];

bool bfs(int s,vector<int> v[]){
    int *head = Q, *tail = Q;
    fill(Flag,Flag+N+1,false);

    //���Ƚ�s����һ���ڵ���������
    for(vector<int>::const_iterator it=v[s].begin();it!=v[s].end();++it){
        Flag[*tail++ = *it] = true;
    }

    //Ȼ�󰤸�����Ƿ��ж����ڵ����
    //�����һ���ڵ��������ֲ��ڶ����У����Ȼ�Ƕ����ڵ㣬���Ȼ���Ǵ��ݵ�
    while(head<tail){
        int u = *head++;
        for(vector<int>::const_iterator it=v[u].begin();it!=v[u].end();++it){
            if(!Flag[*it]) return false;
        }
    }
    return true;
}

bool proc(){
    for(int i=0;i<N;++i){
        if(!bfs(i,GP)) return false;
        if(!bfs(i,GQ)) return false;
    }
    return true;
}

int main(){
    //freopen("1.txt","r",stdin);
    int nofkase;
    scanf("%d",&nofkase);
    while(nofkase--){
        scanf("%d",&N);
        for(int i=1;i<=N;++i){
            GP[i].clear();
            GQ[i].clear();

            scanf("%s",S);
            int k = 1;
            for(char *p=S;*p;++p,++k){
                if('P'==*p){
                    GP[i].push_back(k);
                }else if('Q'==*p){
                    GQ[i].push_back(k);
                }
            }
        }
        printf(proc()?"T\n":"N\n");
    }
    return 0;
}


