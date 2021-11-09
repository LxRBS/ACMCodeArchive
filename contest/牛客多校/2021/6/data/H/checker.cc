#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;

using Rect=pair<pair<int,int>,pair<int,int>>;

int n,d;
vector<Rect> rs;

inline void readInf()
{
    n=inf.readInt();
    d=inf.readInt();
    for (int i=1;i<=n;i++)
    {
        int x1=inf.readInt();
        int y1=inf.readInt();
        int x2=inf.readInt();
        int y2=inf.readInt();
        rs.push_back({{x1,y1},{x2,y2}});
    }
}

bool is_in(int x0,int y0,Rect r)
{
    int x1=r.first.first,y1=r.first.second;
    int x2=r.second.first,y2=r.second.second;
    int xl=0,xr=0,yl=0,yr=0;
    if (x2-x1>=d) xl=0,xr=d-1;
    else xl=(x1%d+d)%d,xr=((x2-1)%d+d)%d;
    if (y2-y1>=d) yl=0,yr=d-1;
    else yl=(y1%d+d)%d,yr=((y2-1)%d+d)%d;
    bool inx=false,iny=false;
    if (xl<=xr) inx=(x0>=xl && x0<=xr);
    else inx=((x0>=0 && x0<=xr) || (x0>=xl && x0<d));
    if (yl<=yr) iny=(y0>=yl && y0<=yr);
    else iny=((y0>=0 && y0<=yr) || (y0>=yl && y0<d));
    return inx && iny;
}

inline void readAndCheckAnswer(InStream& in,bool isans)
{
    int x0=in.readInt(-1000000000,1000000000);
    int y0=in.readInt(-1000000000,1000000000);
    x0=(x0%d+d)%d;
    y0=(y0%d+d)%d;
    for (auto r:rs)
    {
        if (is_in(x0,y0,r))
        {
            if (isans) in.quitf(_fail,"invalid initial position in answer");
            else in.quitf(_wa,"invalid initial position");
        }
    }
}

int main(int argc, char* argv[])
{
    registerTestlibCmd(argc, argv);
    readInf();
    string as=upperCase(ans.readWord());
    string os=upperCase(ouf.readWord());
    if (as!="YES" && as!="NO") quitf(_fail,"invalid first line in answer");
    if (os!="YES" && os!="NO") quitf(_wa,"invalid first line");
    if (os!=as) quitf(_wa, "first line mismatch");
    if (as=="YES") readAndCheckAnswer(ans,true);
    if (os=="YES") readAndCheckAnswer(ouf,false);
    quitf(_ok,"valid answer");
    return 0;
}