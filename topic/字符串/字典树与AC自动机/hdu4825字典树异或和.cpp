/**
   ����һ�����������ϣ�һ����N����
   ����M��ѯ�ʣ�ÿ�θ�һ��������S
   Ҫ���ԴӼ������ҵ�һ����K��ʹ��K��S������
   ���ȶԼ��Ͻ�һ���ֵ���
   Ȼ���ÿһ��K�����ֵ����Ϸ����߾Ϳ�����
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long int llt;

//Just as its name
int const SIZE_OF_TRIE = 2000100;//100�򲻹�
//The count of all valid letters
int const ALPHA_SIZE = 2;//TODO
//The map from letters to ints
int L2I[256];
//To initialize L2I array, don't forget calling it!!!
void initL2I(){
    for(int i=0;i<ALPHA_SIZE;++i) L2I[i + '0'] = i;//TODO
}

//The transition matrix of DFA
int Trie[SIZE_OF_TRIE][ALPHA_SIZE];
llt Flag[SIZE_OF_TRIE];
int SCnt;

int StartState;
int ErrorState;

//to new a state
inline int _newState(){
    fill(Trie[SCnt],Trie[SCnt]+ALPHA_SIZE,0);
    Flag[SCnt] = 0;
    return SCnt++;
}

//to insert a string into Trie
void insert(char const word[],llt idx=1){
    int state = StartState;
    for(char const*p=word;*p;++p){
        int sn = L2I[(int)*p];
        if ( 0 == Trie[state][sn] ) Trie[state][sn] = _newState();
        state = Trie[state][sn];
    }
    Flag[state] = idx;
}

llt find(char const word[]){
    int state = StartState;
    for(char const*p=word;*p;++p){
        int sn = L2I[(int)*p];
        int osn = sn ^ 1;//��Ҫ�뵱ǰ��������
        if(Trie[state][osn]) state = Trie[state][osn];
        else state = Trie[state][sn];//û������ֻ��������
    }
    return Flag[state];
}

void initTrie(){
    SCnt = 0;
    ErrorState = _newState();
    StartState = _newState();
}

llt getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	llt ret = (long long int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10LL + (llt)(ch-'0');
	return ret;
}

int main(){
    //freopen("1.txt","r",stdin);
    initL2I();
    int nofkase = getUnsigned();
    for(int kase=1;kase<=nofkase;++kase){
        printf("Case #%d:\n",kase);

        //��ʼ��
        initTrie();

        int n = getUnsigned();
        int m = getUnsigned();
        for(int i=0;i<n;++i){
            llt a = getUnsigned();
            char word[33] = {'\0'};
            for(int i=0;i<32;++i){
                word[i] = '0' + ((a&(1<<(31-i)))?1:0);
            }
            insert(word,a);//����
        }

        while(m--){
            llt a = getUnsigned();
            char word[33] = {'\0'};
            for(int i=0;i<32;++i){
                word[i] = '0' + ((a&(1<<(31-i)))?1:0);
            }
            printf("%I64d\n",find(word));
        }
    }

	return 0;
}
