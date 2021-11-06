// Author Alexander Rass
#include <bits/stdc++.h>
using namespace std;

int main(){
    int N,M;
    string last_part, encrypted;
    cin >> N >> M >> last_part>> encrypted;
    while(true){
        string key(N,' ');
        for(int i = 0; i < N; i++)key[i] = (char)((rand() % 26) + 'a');
        for(int i = 0; i < M ; i++){
            char next_l = (char) (((encrypted[i] - 'a') - (key[i] - 'a') + 26) % 26) + 'a';
            key += string(1,next_l);
        }
        if(key.substr(key.size() - N) == last_part){
            cout << key.substr(N) << endl;
            return 0;
        }
    }
}
