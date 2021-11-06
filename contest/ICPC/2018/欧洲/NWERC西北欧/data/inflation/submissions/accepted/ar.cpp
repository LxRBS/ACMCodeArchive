// Author Alexander Rass
#include <bits/stdc++.h>
using namespace std;

int main(){
    int N;
    cin >> N;
    vector<int> num(N);
    for(int i = 0; i < N; i++)cin >> num[i];
    sort(num.begin(), num.end());
    double res = 1;
    for(int i = 0; i < N; i++)if(num[i] > 1+i){
        cout << "impossible\n";
        return 0;
    } else {
        res = min(res, num[i] / (i+1.0));
    }
    printf("%.10lf\n", res);
	return 0;
}
