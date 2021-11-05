//求最小表示开始的地方
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

//Just as its name
int const SIZE_OF_SAM = 10000<<2;
//The count of all valid letters
int const ALPHA_SIZE = 26;
//The map from letters to ints
int L2I[256];
//To initialize L2I array, don't forget calling it!!!
void initL2I(){
    for(int i=0;i<26;++i) L2I[i+'a'] = i;
}

//The transition matrix of DFA
int SAM[SIZE_OF_SAM][ALPHA_SIZE];
int Pre[SIZE_OF_SAM];
int Step[SIZE_OF_SAM];
int SCnt;

int StartState;
int ErrorState;
int FinalState;

inline int _newState(){
    fill(SAM[SCnt],SAM[SCnt]+ALPHA_SIZE,0);
    Pre[SCnt] = Step[SCnt] = 0;
    return SCnt++;
}

inline int _newState(int state){
    Pre[SCnt] = Pre[state];
    Step[SCnt] = Step[state];
    copy(SAM[state],SAM[state]+ALPHA_SIZE,SAM[SCnt]);
    return SCnt++;
}

inline void initSAM(){
    SCnt = 0;
    ErrorState = _newState();
    FinalState = StartState = _newState();
}

//在后缀自动机上插入1个字符，返回不同子串的个数
int mkSAM1Step(int startState,int& finalState,char ch){
    int sn = L2I[(int)ch];

    int nn = _newState();
    Step[nn] = Step[finalState] + 1;

    int pt = finalState;
    finalState = nn;

    //遍历Pre链
    while( pt && 0 == SAM[pt][sn] ){
        SAM[pt][sn] = nn;
        pt = Pre[pt];
    }

    //1st condition, all states of the whole chain has no sn son
    if ( 0 == pt ){
        Pre[nn] = startState;
        return Step[nn] - Step[startState];
    }

    //2nd condition
    int q = SAM[pt][sn];
    if ( Step[pt] + 1 == Step[q] ){
        Pre[nn] = q;
        return Step[nn] - Step[q];
    }

    //3rd condition
    int nq = _newState(q);
    Step[nq] = Step[pt] + 1;
    Pre[q] = Pre[nn] = nq;
    while( pt && q == SAM[pt][sn] ){
        SAM[pt][sn] = nq;
        pt = Pre[pt];
    }
    return Step[nn] - Step[nq];
}

char A[SIZE_OF_SAM];
int main(){
    //freopen("1.txt","r",stdin);
    initL2I();

    int nofkase;
    scanf("%d",&nofkase);
    while(nofkase--){
        scanf("%s",A);

        initSAM();

        //将AA做成SAM
        int len = 0;
        for(char *p=A;*p;++p,++len) mkSAM1Step(StartState,FinalState,*p);
        for(char *p=A;*p;++p) mkSAM1Step(StartState,FinalState,*p);

        //run SAM
        int state = StartState;
        for(int i=0;i<len;++i)for(int j=0;j<ALPHA_SIZE;++j)if(SAM[state][j]){state=SAM[state][j];break;}
        printf("%d\n",Step[state]+1-len);
    }
    return 0;
}
