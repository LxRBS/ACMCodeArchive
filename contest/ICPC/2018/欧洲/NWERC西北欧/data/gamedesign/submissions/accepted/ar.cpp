// Author Alexander Rass
#include <bits/stdc++.h>
using namespace std;
const char CHAR_UP = 'U', CHAR_DOWN = 'D', CHAR_LEFT = 'L', CHAR_RIGHT = 'R';
const int BOUND = 1e9;
void impossible(){
    cout << "impossible\n";
}
void calc(){
    string input;
    cin >> input;
    vector<pair<int,int> > blocking;
    int bound_U = BOUND, bound_L = - BOUND, bound_R = BOUND, bound_D = -BOUND;
    int box_U = 0, box_L = 0, box_R = 0, box_D = 0;
    int UD = 0, LR = 0;
    bool canfinish = true;
    for(auto c: input){
        canfinish = true;
        switch(c){
            case CHAR_LEFT:
                if(bound_L == -BOUND){
                    bound_L = (box_L -= 2);
                    blocking.push_back(make_pair(bound_L - 1, UD));
                    bound_U = BOUND, bound_D = -BOUND;
                } else {
                    canfinish = false;
                }
                if(LR == bound_L)return impossible();
                LR = bound_L;
                break;
            case CHAR_RIGHT:
                if(bound_R == BOUND){
                    bound_R = (box_R += 2);
                    blocking.push_back(make_pair(bound_R + 1, UD));
                    bound_U = BOUND, bound_D = -BOUND;
                } else {
                    canfinish = false;
                }
                if(LR == bound_R)return impossible();
                LR = bound_R;
                break;
            case CHAR_UP:
                if(bound_U == BOUND){
                    bound_U = (box_U += 2);
                    blocking.push_back(make_pair(LR, bound_U + 1));
                    bound_R = BOUND, bound_L = -BOUND;
                } else {
                    canfinish = false;
                }
                if(UD == bound_U)return impossible();
                UD = bound_U;
                break;
            case CHAR_DOWN:
                if(bound_D == -BOUND){
                    bound_D = (box_D -= 2);
                    blocking.push_back(make_pair(LR, bound_D - 1));
                    bound_R = BOUND, bound_L = -BOUND;
                } else {
                    canfinish = false;
                }
                if(UD == bound_D)return impossible();
                UD = bound_D;
                break;
        }
    }
    if(!canfinish)return impossible();
    int N = 1;
    sort(blocking.begin(), blocking.end());
    auto last = blocking[0];
    for(auto it: blocking){
        if(it == last)continue;
        last = it;
        ++N;
    }
    cout << -LR << " "<< -UD << endl;
    last = blocking[0];
    cout << N << endl << last.first-LR <<  " "<< last.second-UD << endl;
    for(auto it: blocking){
        if(it == last)continue;
        last = it;
        cout << it.first-LR << " " << it.second-UD << endl;
    }
}
int main(){
    calc();
	return 0;
}
