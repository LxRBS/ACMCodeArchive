/**
    走迷宫，把redcar走出去
*/
#include <bits/stdc++.h>
using namespace std;

int A[6][6];
bool read(){//输入6行
    if(EOF==scanf("%d%d%d%d%d%d",A[0],A[0]+1,A[0]+2,A[0]+3,A[0]+4,A[0]+5)) return false;
    for(int i=1;i<6;++i){
        scanf("%d%d%d%d%d%d",A[i],A[i]+1,A[i]+2,A[i]+3,A[i]+4,A[i]+5);
    }
    return true;
}

typedef pair<int, int> pii;
pii Vehicles[12];//车的横竖与长度
pii Pos[12];     //车的起始位置
bool Flag[12];
int Cnt;

void mkVehicle(int r,int c,int i){
    ++Cnt;
    Flag[i] = true;
    Pos[i].first = r, Pos[i].second = c;

    if(c+2<6&&A[r][c]==A[r][c+1]&&A[r][c]==A[r][c+2]){//横着的卡车
        Vehicles[i].first = 1;  //横着
        Vehicles[i].second = 3; //长度3
    }else if(c+1<6&&A[r][c]==A[r][c+1]){
        Vehicles[i].first = 1;
        Vehicles[i].second = 2;
    }else if(r+2<6&&A[r][c]==A[r+1][c]&&A[r][c]==A[r+2][c]){
        Vehicles[i].first = 2;  //竖着
        Vehicles[i].second = 3; //长度3
    }else if(r+1<6&&A[r][c]==A[r+1][c]){
        Vehicles[i].first = 2;
        Vehicles[i].second = 2;
    }else{
        throw runtime_error("XXXXXXXXXXX");
    }
}

void findAll(){
    for(int i=0;i<6;++i){
        for(int j=0;j<6;++j){
            if(A[i][j]&&!Flag[A[i][j]]){//找到一个车
                mkVehicle(i,j,A[i][j]);
            }
        }
    }
}

bool firstCheck(){
    if(Pos[1].first!=2) return false;
    if(Vehicles[1].first!=1) return false;
    //检查第二行右侧是否有别的横着的
    for(int i=1;i<=Cnt;++i){
        if(Vehicles[i].first==1&&Pos[i].first==2&&Pos[i].second>Pos[1].second){
            return false;
        }
    }
    return true;
}

unordered_map<string, int> Status;
unordered_map<string, int>::iterator It;

int moveCar(int idx, string const&u, string a[]){
    char mych = 'A' + idx;
    string&s = a[0];
    string&s2 = a[1];

    s.assign(u.begin(),u.end());
    s2.assign(u.begin(),u.end());

    int k = 0;
    while(k<u.length()){
        if(u[k]==mych){
            break;
        }
        ++k;
    }

    int row = k / 6, col = k % 6;
    if(Vehicles[idx].first==1){//横着只能左右移动
        if(col>0&&u[k-1]=='A'){//可以向左移
            s[k-1] = mych;
            s[k+Vehicles[idx].second-1] = 'A';//清空
        }
        if(col+Vehicles[idx].second<6&&u[k+Vehicles[idx].second]=='A'){//可以向右移
            s2[k+Vehicles[idx].second] = mych;
            s2[k] = 'A';
        }
    }else if(Vehicles[idx].first==2){
        if(row>0&&u[k-6]=='A'){//向上
            s[k-6] = mych;
            s[k+(Vehicles[idx].second-1)*6] = 'A';
        }
        if(row+Vehicles[idx].second<6&&u[k+6*Vehicles[idx].second]=='A'){
            s2[k+6*Vehicles[idx].second] = mych;
            s2[k] = 'A';
        }
    }else{
        throw runtime_error("XXXXXXXX");
    }
}
void disp(string const&s){
    for(int i=0;i<6;++i){
        cout<<s.substr(i*6,6)<<endl;
    }
    cout<<endl;
}
int bfs(){
    string s;
    for(int i=0;i<6;++i)for(int j=0;j<6;++j) s += 'A' + A[i][j];

    queue<string> q;
    q.push(s);
    Status.insert(make_pair(s, 0));

    while(!q.empty()){
        string u = q.front();
        q.pop();
        unordered_map<string, int>::iterator ut = Status.find(u);
        if(ut->second>7) return -1; //要求不超过10步

        for(int i=1;i<=Cnt;++i){
            string a[2];
            moveCar(i, u, a);

            if(a[0][16]=='B'&&a[0][17]=='B'){
                return ut->second+1+2;
            }
            if(a[1][16]=='B'&&a[1][17]=='B'){
                return ut->second+1+2;
            }

            It = Status.find(a[0]);
            if(It==Status.end()){
                Status.insert(It, make_pair(a[0], ut->second+1));
                q.push(a[0]);
            }

            It = Status.find(a[1]);
            if(It==Status.end()){
                Status.insert(It, make_pair(a[1], ut->second+1));
                q.push(a[1]);
            }
        }
    }

    return -1;
}
int main(){
    //freopen("1.txt","r",stdin);
    //freopen("2.txt","w",stdout);
    while(read()){
        Status.clear();
        fill(Flag,Flag+12,false);
        Cnt = 0;

        //确定vehicles
        findAll();

        //确定redcar
        if(!firstCheck()){
            puts("-1");
            continue;
        }

        printf("%d\n", bfs());
    }
    return 0;
}
