#include <iostream>
#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;

typedef unsigned long long ull;

int const SIZE = 40;
int const ALPHA_SIZE = 26;

typedef ull(*mat_ptr_t)[SIZE];

int C2I['z'+1];
void initC2I(){
    for(int i=0;i<ALPHA_SIZE;++i) C2I['a'+i] = i;
}

int AC[SIZE][ALPHA_SIZE];//AC is used as DFA actually
int Fail[SIZE];          //Fails act as epsilon arc of NFA
bool Flag[SIZE];         //whether state i is final state
int toUsed;
int START_STATE;

void disp(mat_ptr_t p){
    for(int i=START_STATE;i<toUsed;++i){
        for(int j=START_STATE;j<toUsed;++j)
            printf("%3I64u",p[i][j]);
        printf("\n");
    }
}

void disp(int (*p)[ALPHA_SIZE]){
    for(int i=START_STATE;i<toUsed;++i){
        for(int j=0;j<ALPHA_SIZE;++j)
            printf("%3d",AC[i][j]);
        printf("\n");
    }
}

inline int _newState(){
    fill(AC[toUsed],AC[toUsed]+ALPHA_SIZE,0);
    Flag[toUsed] = false;
    Fail[toUsed] = 0;
    return toUsed++;
}

//to insert word into AC
void insert(char const word[]){
    int state = START_STATE;
    for(char const*p=word;*p;++p){
        int sn = C2I[(int)*p];
        if ( 0 == AC[state][sn] ){
            AC[state][sn] = _newState();
        }
        state = AC[state][sn];
    }
    Flag[state] = true;
}

void buildAC(){
    Fail[START_STATE] = START_STATE;

    queue<int> q;

    for(int i=0;i<ALPHA_SIZE;++i){
        int& v = AC[START_STATE][i];

        if ( v ){
            q.push(v);
            Fail[v] = START_STATE;
        }else{
            v = START_STATE;
        }
    }

    while( !q.empty() ){
        int u = q.front();
        q.pop();

        if ( Flag[Fail[u]] ) Flag[u] = true;

        for(int i=0;i<ALPHA_SIZE;++i){
            int& v = AC[u][i];

            if ( v ){
                q.push(v);
                Fail[v] = AC[Fail[u]][i];
            }else{
                v = AC[Fail[u]][i];
            }
        }
    }
}

ull Mat[SIZE][SIZE];

//to assign values of transition matrix
void buildMat(){
    //to set original transition matrix
    for(int i=START_STATE;i<toUsed;++i){
        fill(Mat[i],Mat[i]+toUsed,0ULL);

        if ( Flag[i] ){
            Mat[i][i] = ALPHA_SIZE;
            continue;
        }

        for(int j=0;j<ALPHA_SIZE;++j){
            ++Mat[i][AC[i][j]];
        }
    }

    //to remove final states from transition matrix
    for(int i=toUsed-1;i>=START_STATE;--i){
        if ( !Flag[i] ) continue;

        //to remove row i
        for(int k=i+1;k<toUsed;++k) copy(Mat[k],Mat[k]+toUsed,Mat[k-1]);

        //to remove column i
        for(int k=START_STATE;k<toUsed;++k) copy(Mat[k]+i+1,Mat[k]+toUsed,Mat[k]+i);

        --toUsed;
    }

    //add 1s into the last column to calculate the sum of matrices geometric progression
    fill(Mat[toUsed],Mat[toUsed]+toUsed,0ULL);
    for(int i=START_STATE;i<=toUsed;++i) Mat[i][toUsed] = 1ULL;
    ++toUsed;
}

//multiplication of matrices
void multiMat(mat_ptr_t a,mat_ptr_t b,mat_ptr_t c){
    for(int i=START_STATE;i<toUsed;++i){
        fill(c[i],c[i]+toUsed,0ULL);

        for(int j=START_STATE;j<toUsed;++j){
            for(int k=START_STATE;k<toUsed;++k){
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

//swap pointers to matrix
void swap(mat_ptr_t&a,mat_ptr_t&b){
    mat_ptr_t t = a;
    a = b;
    b = t;
}

ull TM1[SIZE][SIZE],TM2[SIZE][SIZE];

//to calculate Mat^n, the return is the pointer to the result
mat_ptr_t powerMat(int n){
    for(int i=START_STATE;i<toUsed;++i){
        fill(TM1[i],TM1[i]+toUsed,0ULL);
        TM1[i][i] = 1ULL;
    }

    mat_ptr_t a = Mat;
    mat_ptr_t ans = TM1;
    mat_ptr_t t = TM2;

    while( n ){
        if ( n & 1 ){
            multiMat(a,ans,t);
            swap(ans,t);
        }

        multiMat(a,a,t);
        swap(a,t);

        n >>= 1;
    }
    return ans;
}

int N,L;

bool read(){
    if ( 2 != scanf("%d%d",&N,&L) ) return false;

    toUsed = 1; //Zero should not be used!!!
    START_STATE = _newState();

    char s[6];
    for(int i=0;i<N;++i){
        scanf("%s",s);
        insert(s);
    }

    buildAC();
    buildMat();
    return true;
}

void proc(){
    mat_ptr_t p = powerMat(L);

    ull t = 0ULL;
    for(int i=START_STATE;i<toUsed;++i) t += p[START_STATE][i];

    //to calculate the sum of geometric progression with the ratio 26
    toUsed = 3;
    Mat[1][1] = 26ULL;
    Mat[1][2] = Mat[2][2] = 1ULL;
    Mat[2][1] = 0ULL;

    //it should be L+1 in fact, but L+1 will exceed the range of int
    p = powerMat(L);

    printf("%I64u\n",p[1][1]+p[1][2]-t);
}

int main(){
    initC2I();
    while( read() ) proc();
    return 0;
}
