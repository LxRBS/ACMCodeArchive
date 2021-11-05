/*
    两个罐子，互相倒水，问是否能得到指定体积的水
    需要输出步骤
*/

#include <stdio.h>
#include <queue>
#include <vector>
using namespace std;

bool Flag[110][110] = {false};
int A,B,C;

struct _t{
    int a,b;
    vector<int> v;
    _t(int aa=0,int bb=0,vector<int>const&cc=vector<int>()):a(aa),b(bb),v(cc){}
};

char const CMD[][22] = {
    "FILL(1)","FILL(2)","DROP(1)","DROP(2)","POUR(1,2)","POUR(2,1)"
};

vector<int> Ans;
int bfs(){
    queue<_t> q;
    q.push(_t(0,0));
    Flag[0][0] = true;

    while( !q.empty() ){
        _t u = q.front();
        q.pop();

        //fill 1
        if ( !Flag[A][u.b] ){
            Flag[A][u.b] = true;
            u.v.push_back(0);
            q.push(_t(A,u.b,u.v));
            u.v.pop_back();
        }

        //fill 2
        if ( !Flag[u.a][B] ){
            Flag[u.a][B] = true;
            u.v.push_back(1);
            q.push(_t(u.a,B,u.v));
            u.v.pop_back();
        }

        //drop 1
        if ( !Flag[0][u.b] ){
            Flag[0][u.b] = true;
            u.v.push_back(2);
            q.push(_t(0,u.b,u.v));
            u.v.pop_back();
        }

        //drop 2
        if ( !Flag[u.a][0] ){
            Flag[u.a][0] = true;
            u.v.push_back(3);
            q.push(_t(u.a,0,u.v));
            u.v.pop_back();
        }

        //pour 1 2
        u.v.push_back(4);
        if ( u.a + u.b <= B ){
            if ( !Flag[0][u.a+u.b] ){
                if ( u.a+u.b == C ){
                    Ans = u.v;
                    return 1;
                }
                Flag[0][u.a+u.b] = true;
                q.push(_t(0,u.a+u.b,u.v));
            }
        }else{
            if ( !Flag[u.a+u.b-B][B] ){
                if ( u.a + u.b - B == C ){
                    Ans = u.v;
                    return 1;
                }

                Flag[u.a+u.b-B][B] = true;
                q.push(_t(u.a+u.b-B,B,u.v));

            }
        }
        u.v.pop_back();

        //pour 2 1
        u.v.push_back(5);
        if ( u.a + u.b <= A ){
            if ( !Flag[u.a+u.b][0] ){
                if ( u.a + u.b == C ){
                    Ans = u.v;
                    return 1;
                }

                Flag[u.a+u.b][0] = true;
                q.push(_t(u.a+u.b,0,u.v));
            }
        }else{
            if ( !Flag[A][u.a+u.b-A] ){
                if ( u.a+u.b-A == C ){
                    Ans = u.v;
                    return 1;
                }

                Flag[A][u.a+u.b-A] = true;
                q.push(_t(A,u.a+u.b-A,u.v));
            }
        }
    }

    return 0;
}

int main(){
    scanf("%d%d%d",&A,&B,&C);
    if ( C==A ){
        printf("1\nFILL(1)\n");
        return 0;
    }

    if ( C==B ){
        printf("1\nFILL(2)\n");
        return 0;
    }

    int r = bfs();
    if ( 0 == r ){
        printf("impossible\n");
        return 0;
    }

    printf("%u\n",Ans.size());
    for(vector<int>::const_iterator it=Ans.begin();it!=Ans.end();++it) printf("%s\n",CMD[*it]);

    return 0;
}
