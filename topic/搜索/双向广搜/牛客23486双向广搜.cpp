/**
    一个迷宫，AB两个人
    A每分钟可以朝八邻域走一步
    B每分钟可以走二步，八邻域
    问最短几分钟相遇，有可能不相遇
    显然是双向广搜，成批扩展比较方便
*/
#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
#define fi first
#define se second
#define mp make_pair

int const DR[] = {-1,1,0,0,-1,-1,1,1};
int const DC[] = {0,0,-1,1,-1,1,-1,1};

int N,M;
char TT[2200],A[1010][1010];
int SX,SY,EX,EY;

bool Flag[2][1010][1010];

//走一步
bool move(int aorb,int idx,int r,int c,int& nr,int& nc){
    nr = r + DR[idx];
    nc = c + DC[idx];
    return 0<=nr&&nr<N&&0<=nc&&nc<M&&A[nr][nc]=='.'&&!Flag[aorb][nr][nc];
}

int bibfs(){
    for(int i=0;i<N;++i){
        fill(Flag[0][i],Flag[0][i]+M+1,false);
        fill(Flag[1][i],Flag[1][i]+M+1,false);
    }

    queue<pii> qa,qb;
    qa.push(mp(SX,SY));
    qb.push(mp(EX,EY));
    Flag[0][SX][SY] = Flag[1][EX][EY] = true;

    int ans = 0;
    while(!qa.empty()&&!qb.empty()){
        ++ans;
        int sz = qa.size();
        while(sz--){
            pii u = qa.front();qa.pop();
            for(int dr,dc,i=0;i<8;++i){
                if(move(0,i,u.fi,u.se,dr,dc)){
                    if(Flag[1][dr][dc]) {
                        return ans;
                    }
                    Flag[0][dr][dc] = true;
                    qa.push(mp(dr,dc));

                }
            }
        }

        sz = qb.size();
        while(sz--){
            pii u = qb.front();qb.pop();
            for(int dr,dc,i=0;i<4;++i){
                if(move(1,i,u.fi,u.se,dr,dc)){
                    if(Flag[0][dr][dc]){
                        return ans;
                    }
                    Flag[1][dr][dc] = true;
                    qb.push(mp(dr,dc));
                    for(int nr,nc,j=0;j<4;++j){
                        if(move(1,j,dr,dc,nr,nc)){
                            if(Flag[0][nr][nc]) {
                                return ans;
                            }
                            Flag[1][nr][nc] = true;
                            qb.push(mp(nr,nc));
                        }
                    }
                }
            }
        }
    }

    while(!qa.empty()){
        ++ans;
        int sz = qa.size();
        while(sz--){
            pii u = qa.front();qa.pop();
            for(int dr,dc,i=0;i<8;++i){
                if(move(0,i,u.fi,u.se,dr,dc)){
                    if(Flag[1][dr][dc]) return ans;
                    Flag[0][dr][dc] = true;
                    qa.push(mp(dr,dc));
                }
            }
        }
    }
    while(!qb.empty()){
        ++ans;
        int sz = qb.size();
        while(sz--){
            pii u = qb.front();qb.pop();
            for(int dr,dc,i=0;i<4;++i){
                if(move(1,i,u.fi,u.se,dr,dc)){
                    if(Flag[0][dr][dc]) return ans;
                    Flag[1][dr][dc] = true;
                    qb.push(mp(dr,dc));
                    for(int nr,nc,j=0;j<4;++j){
                        if(move(1,j,dr,dc,nr,nc)){
                            if(Flag[0][nr][nc]) return ans;
                            Flag[1][nr][nc] = true;
                            qb.push(mp(nr,nc));
                        }
                    }
                }
            }
        }
    }
    return -1;
}

int main(){
    //freopen("1.txt","r",stdin);
    while(2==scanf("%d%d",&N,&M)){
        fgets(TT,2100,stdin);
        for(int i=0;i<N;++i){
            fgets(TT,2100,stdin);
            int k = 0;
            for(char const*p=TT;*p;++p){
                if(*p=='.'||*p=='#') A[i][k++] = *p;
                else if(*p==' ') ;
                else if(*p=='C'){
                    A[i][k] = 'C';
                    SX = i, SY = k++;
                }else if(*p=='D'){
                    A[i][k] = 'D';
                    EX = i, EY = k++;
                }else{
                    //throw runtime_error("XXXXXXX");
                }
            }
            A[i][M] = '\0';
        }

        int ret = bibfs();
        if(-1==ret) puts("NO");
        else {printf("YES\n%d\n",ret);}
    }
	return 0;
}

