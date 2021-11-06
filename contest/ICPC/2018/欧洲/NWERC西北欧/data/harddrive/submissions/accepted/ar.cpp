// Author Alexander Rass
#include <bits/stdc++.h>
using namespace std;

int main(){
    int N,AIM,BROKEN;
    cin >> N >> AIM >> BROKEN;
    int DONE = 1;
    if(AIM&1){
        printf("10");
        DONE = 2;
    } else {
        printf("0");
    }
    AIM /= 2;
    for(;BROKEN;--BROKEN){
        int NEXT;
        cin >> NEXT;
        while(AIM > 0 && NEXT - DONE >= 2){
            printf("10");
            DONE+=2;
            --AIM;
        }
        while(NEXT != DONE){
            printf("0");
            ++DONE;
        }
    }
    printf("\n");
	return 0;
}
