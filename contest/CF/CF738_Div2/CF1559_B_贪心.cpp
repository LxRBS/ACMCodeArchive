/**
  �ַ�����B��R��?���ɣ��������������ĸһ�������һ��
  Ҫ��?ȷ��ΪB����R�е�һ������ʹ�÷�����С
  ̰�ģ�������д��ĸ���ɡ�Ȼ�󿴿��߽���ĸ
*/
#include<bits/stdc++.h>
using namespace std;

int N;
char A[110];

void proc(){
    /// kaitou dandu chuli
    int cur = 0;
    while(cur<N&&'?'==A[cur]) ++cur;
    if(cur==N){
        for(int ch='B',i=0;i<N;++i,ch='B'+'R'-ch){
            A[i] = ch;
        }
        A[N] = '\0';
        puts(A);
        return;
    }

    if('B'==A[cur]){
        for(int i=cur-1,ch='R';i>=0;--i,ch='B'+'R'-ch){
            A[i] = ch;
        }
    }else if('R'==A[cur]){
        for(int i=cur-1,ch='B';i>=0;--i,ch='B'+'R'-ch){
            A[i] = ch;
        }
    }else{
        throw runtime_error("XX");
    }

    while(1){
        while(cur<N&&A[cur]!='?') ++cur;
        if(N==cur) break;

        int ch = A[cur-1];
        while(cur<N&&'?'==A[cur]){
            ch = 'B' + 'R' - ch;
            A[cur] = ch;
            ++cur;
        }
        if(cur==N) break;
    }

    A[N] = '\0';
    puts(A);
}

int main(){
    //freopen("1.txt","r",stdin);
    int nofkase;
    scanf("%d", &nofkase);
    while(nofkase--){
        scanf("%d%s", &N, A);
        proc();
    }
    return 0;
}
 