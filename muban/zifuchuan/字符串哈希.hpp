template<unsigned N = 1>
struct StrHash{

size_t operator () (const string & s){
	size_t ans = 0;
    for(char ch : s) ans = ans * seeds[0] + ch;
	return ans;
}

array<size_t, N> hash(const string & s){
	array<size_t, N> ans;
    fill(ans.begin(), ans.end(), 0);
	for(char ch : s){
		for(int i=0;i<N;++i){
            ans[i] = ans[i] * seeds[i] + ch;
		}
	}
	return ans;
}

public:
StrHash():seeds({13331}){}

private:
array<size_t, N> seeds;

};
