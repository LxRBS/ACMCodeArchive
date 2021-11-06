// Author Alexander Rass
#include <bits/stdc++.h>
using namespace std;
// USAGE:
// just call the program without any parameter
// the first line of input should contain the execution command like "pypy foo.py" or "java -cp submissions/accepted/ Bar" ...
// the remaining input is parsed by string (not by line)
// next string is temporary output file
// all remaining strings are used as input file
// output are the four delta values while executing all input files

// TODO add minimal allowed distance between points
const double PI = acos(-1.0);
const int MAXN = 1024;
vector<int> adj[MAXN];
long double x[MAXN], y[MAXN];
long double distance(int i, int j){
    auto dx = x[i] - x[j], dy = y[i] - y[j];
    return sqrt(dx*dx + dy * dy);
}

struct Point { // bei ganzahligen Koordinaten double durch ll ersetzen
  union {
    long double a[2];
    struct { long double x,y; };
  };
  Point(long double i=0, long double j=0) : a{i,j} {}
  long double & operator[](size_t i) { return a[i]; }
  const long double & operator[](size_t i) const { return a[i]; }
};
long double distPointPoint(Point a, Point b) {
  long double dx = a.x - b.x, dy = a.y - b.y;
  return sqrt(dx*dx + dy*dy);
}
long double distPointLine(Point p, Point a, Point b) {
  long double c = (a.x - p.x) * (b.y - p.y) - (b.x - p.x) * (a.y - p.y);
  return abs(c) / distPointPoint(a, b);
}
long double distPointSegment(Point p, Point a, Point b) {
  long double pa = distPointPoint(p, a);
  long double pb = distPointPoint(p, b);
  long double ab = distPointPoint(a, b);
  if (pa * pa + ab * ab <= pb * pb) return pa;
  if (pb * pb + ab * ab <= pa * pa) return pb;
  return distPointLine(p, a, b);
}
long double directdistancerange[2] = {1.,-1.};
long double nearest_point = 1.0;
long double nearest_segment = 1.0;
void do_single_input(string inputfilename, string outputfilename){
    ifstream inputfile(inputfilename);
    ifstream outputfile(outputfilename);
    int N;
    inputfile >> N;
    for(int i = 0; i < N; i++)adj[i].clear();
    for(int i = 1; i < N; i++){
        int a,b;
        inputfile >> a >> b;
        adj[--a].push_back(--b);
        adj[b].push_back(a);
    }
    for(int i = 0; i < N; i++){
        outputfile >> x[i] >> y[i];
    }
    for(int n = 0; n < N; n++){
        for(auto to: adj[n]){
            auto dist = distance(n,to) - 1.0;
            directdistancerange[0] = min(directdistancerange[0], dist);
            directdistancerange[1] = max(directdistancerange[1], dist);
        }
    }
    for(int n = 0; n < N; n++){
        for(int o = 0; o < n; o++){
            nearest_point = min(nearest_point, distance(n,o));
        }
        for(int a = 0; a < N; a++)if(a != n){
            for(auto b: adj[a])if(b != n){
                nearest_segment = min(nearest_segment, distPointSegment(Point(x[n], y[n]), Point(x[a],y[a]), Point(x[b], y[b])));
            }
        }
    }
}

void printnum(long double v){
    int p = 0;
    while(v > -0.995 && v < 0.995 && p < 30){
        v *= 10;
        p++;
    }
    printf("%c%c",'$','`');
    if(p == 30){
        printf("0.00");
    } else {
        printf("%.2lf",(double)v);
        if(p)printf("\\cdot 10^{-%d}",p);
    }
    printf("%c%c",'`','$');
}
int main(){
    directdistancerange[0] = 10;
    directdistancerange[1] = -10;
    nearest_point = 10;
    nearest_segment = 10;
    string executecommand, temp_outputfile;
    getline(cin,executecommand);
    cin >> temp_outputfile;
    vector<string> inputfilenames;
    {
        string tmp;
        while(cin >> tmp){
            inputfilenames.push_back(tmp);
        }
    }
    for(auto inputfilename: inputfilenames){
        string command = executecommand + " < " + inputfilename + " > " + temp_outputfile;
        assert(0 == system(command.c_str()));
        do_single_input(inputfilename, temp_outputfile);
    }
    cout << executecommand << endl;
    printf("|");
    printnum(directdistancerange[0]);
    printf("|");
    printnum(directdistancerange[1]);
    printf("|");
    printnum(nearest_point);
    printf("|");
    printnum(nearest_segment);
    printf("|\n");
	return 0;
}
