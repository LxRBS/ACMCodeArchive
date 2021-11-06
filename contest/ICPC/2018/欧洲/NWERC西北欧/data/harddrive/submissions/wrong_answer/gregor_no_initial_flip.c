int bits[500000];

int main(){
	int n,e,b; scanf("%d %d %d", &n, &e, &b);
	for (int i = 0; i < n; i++) bits[i] = -1;
	for (int i = 0; i < b; i++){
		int p; scanf("%d", &p);
		bits[p-1] = 0;
	}

	bits[0] = 0; 
	for (int i = 1; i < n; i++) {
		if (e == 0 || (e == -1 && bits[1]) || (e == 1 && !bits[1])) break;
		if (bits[i] == 0) continue;
		bits[i] = 1 - bits[i-1];
		if (bits[i]) e-=2,	printf("%d\n",i+1);
	}

	if (e) bits[0] = 1;
	for(int i = 0; i < n; i++) printf("%d",bits[i]==1);
}
