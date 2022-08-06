#include <bits/stdc++.h>
using namespace std;
const double PI=acos(-1);
using namespace std;
int n;    
double sum=0,ans=0;

struct point{ 
    double x,y,r;
}p[2005];

double dist2(float x){return((x)*(x));}

double dis(point a, point b){
    return dist2(b.x-a.x)+dist2(b.y-a.y);
}

double lenc(point a, double x){return a.x+a.r*cos(x);}

double lens(point a, double x){return a.y+a.r*sin(x);}

double eps(point a) {return 1e-10*sum/a.r;}

int main(){

    cin>>n;
    for(int i=0; i<n; ++i){
        cin>>p[i].x>>p[i].y>>p[i].r;
        sum+=p[i].r;
    }
    
    for(int i=0; i<n; i++){
        map<double, int> tz;
        tz[-PI]=1,tz[PI]=-1;
        for(int j=i+1;j<n;j++){
            if(dis(p[i],p[j])>=dist2(p[j].r+p[i].r)){
                continue;
            } else if(dis(p[i],p[j])<=dist2(p[j].r-p[i].r)){
                if(p[i].r<=p[j].r){
                    tz.clear();
                    break;
                }
            } else {
                double t=atan2(p[j].y-p[i].y, p[j].x-p[i].x);
                double lcir=0,rcir=PI;
                double mcir=(rcir+lcir)/2;
                while(rcir-lcir>eps(p[i])){
                    double xx=lenc(p[i],t+mcir); 
                    double yy=lens(p[i],t+mcir);
                    if(dist2(xx-p[j].x)+dist2(yy-p[j].y)<dist2(p[j].r)){
                        lcir=mcir;mcir=(rcir+lcir)/2;
                    } else {
                        rcir=mcir;mcir=(rcir+lcir)/2;
                    }
                }
                if(t+rcir>PI) tz[PI]++,tz[-PI]--,tz[t+rcir-2*PI]++;
                else tz[t+rcir]++;

                if(t-rcir<-PI) tz[PI]++,tz[-PI]--,tz[t-rcir+2*PI]--;
                else tz[t-rcir]--;
                
            }
        }

        double pos=-PI;
        int tz_sum=0;
        for(auto pa: tz){
            if(tz_sum>0){
                ans+=(pa.first-pos)*p[i].r;
            }
            pos=pa.first;
            tz_sum+=pa.second;
        }
    }

    cout<<fixed<<setprecision(9)<<ans;
    return 0;
}