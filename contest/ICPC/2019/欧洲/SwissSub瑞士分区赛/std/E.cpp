#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    scanf("%d", &n);
    
    for(int i=0; i<n; i++) printf("%c", 'a');
    for(int i=0; i<n; i++) printf("%c", 'b');
    printf("\n");

    for(int i=0; i<n-1; i++) printf("%c", 'a');
    printf("%c", 'b');
    printf("%c", 'a');
    for(int i=0; i<n-1; i++) printf("%c", 'b');
    printf("\n");

    return 0;
}