#include <bits/stdc++.h>
using namespace std;

int x[1000];
int y[1000];
int nei[1000];

double cx[1000];
double cy[1000];

int n;

struct pt{
	double x,y;
	pt():x(0),y(0){};
	pt(double _x,double _y):x(_x),y(_y){};

	pt operator+(const pt& p) { return pt(x+p.x,y+p.y); }
	pt operator-(const pt& p) { return pt(x-p.x,y-p.y); }
	pt operator*(const double f) { return pt(x*f,y*f); }
	pt operator/(const double f) { return pt(x/f,y/f); }
	double operator*(const pt& p) { return x*p.x+y*p.y; }
};
double len(pt p) { return sqrt(double(p*p)); }

pt closestpt(pt a0, pt a1, pt p) {
	pt d=a1-a0;
	return a0+(d*(d*(p-a0))/(d*d));
}

void dfs(int c, int p, double f, double t){
	
	// get maximum reachable angles
	pt my(cx[c], cy[c]);
	if (len(my) > 1){
		double mang = asin(1 / len(my));
		double nf = max(f, (f+t)/2 - mang);
		double nt = min(t, (f+t)/2 + mang);
		f = nf; t = nt;
	}


	int cn = 0;
	for (int i = 0; i < n-1; i++){
		int o = -1;
		if (x[i] == c) o = y[i];
		if (y[i] == c) o = x[i];
		if (o == -1 || o == p) continue;
		double nf = f + (t-f)/(nei[c]-(p==-1?0:1)) * cn;
		double nt = f + (t-f)/(nei[c]-(p==-1?0:1)) * (cn + 1);

		double pa = (nf + nt) / 2;
		pt c1(0,0);
		pt c2(2000*sin(pa),2000*cos(pa));
		pt cl = closestpt(c1,c2,my);
		double db = len(c1 - cl); 
		double dadd = sqrt(1 - ((cl-my) * (cl-my)));

		cx[o] = ((db + dadd) * sin(pa));
		cy[o] = ((db + dadd) * cos(pa));
		dfs(o,c,nf,nt);
		cn++;
	}
}

int main(){
	scanf("%d",&n);
	for (int i = 0; i < n; i++) nei[i] = 0;
	for (int i = 0; i < n - 1; i++){
		scanf("%d %d", x+i, y+i);
		x[i]--;
		y[i]--;
		nei[x[i]]++;
		nei[y[i]]++;
	}

	cx[0] = 0;
	cy[0] = 0;
	dfs(0,-1,0,2*acos(0));

	for (int i = 0; i < n; i++) printf("%.9f %.9f\n", cx[i], cy[i]);

}
