#include <bits/stdc++.h>
using namespace std;
string s1, s2, t1, t2;
int n;
map<string, string> mp;
int main() {
	// freopen("test.in", "r", stdin);
	// freopen("test.out", "w", stdout);
	mp["aa"] = ""; mp["bc"] = "a"; mp["ca"] = "bb"; mp["abc"] = "";
	mp["aca"] = "abb"; mp["baa"] = "b"; mp["bab"] = "acc";
	mp["bba"] = "c"; mp["bbb"] = ""; mp["bbc"] = "ba";
	mp["cbc"] = "bb"; mp["cca"] = "cbb"; mp["ccc"] = "ab";
	mp["abaa"] = "ab"; mp["abab"] = "cc"; mp["abba"] = "ac";
	mp["abbb"] = "a"; mp["abbc"] = "aba"; mp["acbc"] = "abb";
	mp["acca"] = "acbb"; mp["accc"] = "b"; mp["baca"] = "accb";
	mp["bacc"] = "cb"; mp["cbaa"] = "cb"; mp["cbab"] = "bac";
	mp["cbba"] = "cc"; mp["cbbb"] = "c"; mp["cbbc"] = "cba";
	mp["ccba"] = "abac"; mp["ccbb"] = "aba"; mp["ccbc"] = "cbb";
	mp["abaca"] = "ccb"; mp["abacb"] = "cbac"; mp["abacc"] = "acb";
	mp["acbaa"] = "acb"; mp["acbab"] = "abac"; mp["acbac"] = "bacb";
	mp["acbba"] = "acc"; mp["acbbb"] = "ac"; mp["acbbc"] = "acba";
	mp["accba"] = "bac"; mp["accbb"] = "ba"; mp["accbc"] = "acbb";
	mp["bacba"] = "cbac"; mp["bacbb"] = "cba"; mp["bacbc"] = "accb";
	mp["cbaca"] = "bacb"; mp["cbacb"] = "acba"; mp["cbacc"] = "ccb";
	cin >> n;
	while(n--) {
		cin >> s1 >> s2;
		t1 = t2 = "";
		for(char ch : s1) {
			t1 = t1 + ch;
			if(mp.count(t1)) t1 = mp[t1];
		}
		for(char ch : s2) {
			t2 = t2 + ch;
			if(mp.count(t2)) t2 = mp[t2];
		}
		if(t1 == t2) puts("yes");
		else puts("no");
	}
	return 0;
}
