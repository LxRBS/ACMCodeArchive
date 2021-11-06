#include <bits/stdc++.h>
using namespace std;

void fail_(const char *reason, int condition, int lineno) {
  if (!condition) {
    printf("failed to check (line %d): %s\n",lineno, reason);
    exit(1);
  }
}
#define fail(reason,condition) fail_((reason), (condition), (__LINE__))


int parse_expression(string & a, int l, int r){
	if (a[l] == '['){
		// check integer list
		int curdigi = 0;
		int size = 1;
		while (true){
			fail("not enough chars", l+size < r);
			if (a[l+size] == ']'){
				fail ("empty list",size != 1);
				fail ("empty number", curdigi);
				fail ("number too long", curdigi <= 9);
				return size+1;
			} else if (a[l+size] == ','){
				fail ("number too long", curdigi <= 9);
				curdigi = 0;
			} else if (a[l+size] == '0'){
				fail ("number starting with digit zero", curdigi);
				curdigi++;
			} else if ('1' <= a[l+size] && a[l+size] <= '9'){
				curdigi++;
			} else fail("unexpected character", false);

			size++;
		}
	} else if (a[l] == 'c'){
		fail("not enough chars for (c)oncat(...)", r-l >= 15);
		fail("wrong chars", a[l+1] == 'o');
		fail("wrong chars", a[l+2] == 'n');
		fail("wrong chars", a[l+3] == 'c');
		fail("wrong chars", a[l+4] == 'a');
		fail("wrong chars", a[l+5] == 't');
		fail("wrong chars", a[l+6] == '(');
		int size1 = parse_expression(a,l+7,r);
		fail("subexpression to large", l+7+size1 < r);
		fail("no comma", a[l+7+size1] == ',');
		int size2 = parse_expression(a,l+7+size1+1,r);
		fail("subexpression to large", l+7+size1+1+size2 < r);
		fail("no comma", a[l+7+size1+1+size2] == ')');
		return 7+size1+1+size2+1;
	} else if (a[l] == 's'){
		fail("not enough chars for anything", l+1 < r);
		if (a[l+1] == 'o'){
			fail("not enough chars for (so)rted(...)", r-l >= 11);
			fail("wrong chars", a[l+2] == 'r');
			fail("wrong chars", a[l+3] == 't');
			fail("wrong chars", a[l+4] == 'e');
			fail("wrong chars", a[l+5] == 'd');
			fail("wrong chars", a[l+6] == '(');
			int size1 = parse_expression(a,l+7,r);
			fail("subexpression to large", l+7+size1 < r);
			fail("no comma", a[l+7+size1] == ')');
			return 7+size1+1;
		} else if (a[l+1] == 'h'){
			fail("not enough chars for (sh)uffle(...)", r-l >= 12);
			fail("wrong chars", a[l+2] == 'u');
			fail("wrong chars", a[l+3] == 'f');
			fail("wrong chars", a[l+4] == 'f');
			fail("wrong chars", a[l+5] == 'l');
			fail("wrong chars", a[l+6] == 'e');
			fail("wrong chars", a[l+7] == '(');
			int size1 = parse_expression(a,l+8,r);
			fail("subexpression to large", l+8+size1 < r);
			fail("no comma", a[l+8+size1] == ')');
			return 8+size1+1;
		} else fail("unexpected character", false);
	} else fail("unexpected character", false);
	return 0;
}



int main(){
	string a,b; cin >> a >> b;
	fail("Input must contain two expression", !cin.eof());
	string c; cin >> c;
	fail("Input should not contain more than two lines",  cin.eof());

	fail("expressions a must contain at least 3 chars.", a.size() >= 3);
	fail("expressions b must contain at least 3 chars.", b.size() >= 3);
	fail("expressions a must contain at most 10^6 chars.", a.size() <= 1000000);
	fail("expressions b must contain at most 10^6 chars.", b.size() <= 1000000);

	parse_expression(a,0,a.size());
	parse_expression(b,0,b.size());
	return 42;
}
