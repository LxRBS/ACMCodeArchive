/*
    ���������Լ����ӵĹ��ɹ��� 
    �����������У��ж��Ƿ�Ϊ���� 
*/
#include <cstdio>
#include <vector>
#include <cctype>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

//Just as its name
int const SIZE_OF_TRIE = 500000;//TODO
//The count of all valid letters
int const ALPHA_SIZE = 26;//TODO
//The map from letters to ints
int L2I[256];
//To initialize L2I array, don't forget calling it!!!
void initL2I(){//�����ִ�Сд
    for(int i=0;i<26;++i) L2I[i+'a'] = L2I[i+'A'] = i;
}
//The transition matrix of DFA
int Trie[SIZE_OF_TRIE][ALPHA_SIZE];
int Flag[SIZE_OF_TRIE];
int SCnt;

int StartState;
int ErrorState;

//to new a state
inline int _newState(){
    fill(Trie[SCnt],Trie[SCnt]+ALPHA_SIZE,0);
    Flag[SCnt] = 0;
    return SCnt++;
}

//run DFA by a string
int _run(char const word[]){
    int state = StartState;
    for(char const*p=word;*p;++p){
        int sn = L2I[(int)*p];
        state = Trie[state][sn];
        if ( ErrorState == state ) return ErrorState;
    }
    return state;
}

//to insert a string into Trie
void insert(char const word[],int idx=1){
    int state = StartState;
    for(char const*p=word;*p;++p){
        int sn = L2I[(int)*p];
        if ( 0 == Trie[state][sn] ) Trie[state][sn] = _newState();
        state = Trie[state][sn];
    }
    Flag[state] = idx;
}

//to find whether a given string exists in Trie
int find(char const word[]){
    return Flag[_run(word)];
}

void initTrie(){
    SCnt = 0;
    ErrorState = _newState();
    StartState = _newState();
}

int const NOUN = 1;//��
int const VI = 2;//�����ﶯ��
int const VT = 3;//���ﶯ��
int const ADJ = 4;//���ݴ�
int const PRON = 5;//����
int const ADV = 6;//����
int const ART = 7;//�ڴ�
int const VERB = 8;//����
int const PREP = 9;//���

int const DFA[][10] = {
/*0*/{0},
//    # �� Vi Vt �� �� �� �� ��
/*1*/{0,0, 0, 0, 0, 2, 0, 3},
/*2*/{0,0, 5, 7, 0, 0, 6, 0, 8},
/*3*/{0,2, 0, 0, 4},
/*4*/{0,2},
/*5*/{0},//Final
/*6*/{0,0, 5, 7, 0, 0, 0, 0, 8},
/*7*/{0,0, 0, 0, 0, 9, 0, 10},
/*8*/{0,0, 0, 0, 0, 9, 0, 10},//Final
/*9*/{0},//Final
/*10*/{0,11,0, 0,12},
/*11*/{0},//Final
/*12*/{0,11}
};

bool run(vector<int>const&word){
    int state = 1;
    for(vector<int>::const_iterator it=word.begin();it!=word.end();++it){
        state = DFA[state][*it];
        if ( !state ) return false;
    }
    return 5 == state || 8 == state || 9 == state || 11 == state;
}

inline int _g(char const a[]){
    switch( a[0] ){
        case 'n':return NOUN;
        case 'v':if ( '.' == a[1] )return VERB;
            if ( 'i' == a[1] ) return VI;
            return VT;
        case 'a': if ( 'r' == a[1] ) return ART;
            if ( 'j' == a[2] ) return ADJ;
            return ADV;
        case 'p': if ( 'o' == a[2] ) return PRON;
            return PREP;
    }
}

int N,M;
char A[1000],B[1000];
void read(){
    scanf("%d%d",&N,&M);

    initTrie();
    //�����ִ�Сд
    for(int i=0;i<N;++i){
        scanf("%s%s",A,B);
        insert(A,_g(B));
    }
    return;
}

typedef vector<int>::iterator vit;
//�жϽ��
bool doPrep(vector<int>& tokens){
    vit pit;
    int cnt = 0;
    for(vit it=tokens.begin();it!=tokens.end();++it){
        if ( PREP == *it ) ++cnt,pit = it;
    }

    if ( cnt > 1 ) return false;
    if ( 0 == cnt ) return true;
    //��ʺ������Ӵ��ʣ����߹��������߹�����
    vit tt = pit + 1;
    //����ǽ�ʣ�OK
    if ( PRON == *tt ){
        tokens.erase(pit,tt+1);
        return true;
    }
    //������ǹڴʣ�NO
    if ( ART != *tt ) return false;

    ++tt;

    if ( NOUN == *tt ){
        tokens.erase(pit,tt+1);
        return true;
    }

    if ( ADJ != *tt ) return false;

    ++tt;
    if ( NOUN == *tt ) {
        tokens.erase(pit,tt+1);
        return true;
    }

    return false;
}

bool proc(){
    //�������ʷ�
    vector<int> tokens;
    stringstream ss(A);
    string s;
    while( ss >> s ){
        char ch = *--s.end();
        if ( !isalpha(ch) ) s.erase(s.end()-1);

        tokens.push_back(find(s.c_str()));
    }

    //�жϽ�ʣ��������ɾ��
    if ( !doPrep(tokens) ) return false;

    //��û�н�ʵ�token���﷨����
    return run(tokens);
}



int main(){
    //freopen("1.txt","r",stdin);
    initL2I();

    read();

    fgets(A,200000,stdin);
    for(int i=0;i<M;++i){
        fgets(A,200000,stdin);
        printf(proc()?"YES\n":"NO\n");
    }
    return 0;
}
