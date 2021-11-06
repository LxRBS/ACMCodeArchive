#include <bits/stdc++.h>
using namespace std;

enum Event: int{
  END, CONCAT, SORT, SHUFFLE
};

template <template<class> class Comp>
vector<int> eval(string const &s){
  vector<tuple<Event,size_t,size_t>> events;
  vector<int> nums;

  stack<int> open_events;
  for (size_t i=0; i<s.size(); i++){
    if (s[i]=='('){
      open_events.push(events.size());
      switch (s[i-1]){
        case 't': events.emplace_back(CONCAT,  nums.size(), 0); break;
        case 'e': events.emplace_back(SHUFFLE, nums.size(), 0); break;
        case 'd': events.emplace_back(SORT,    nums.size(), 0); break;
        default: assert(false);
      }
    }
    else if (s[i]==')'){
      assert(not open_events.empty());
      get<2>(events[open_events.top()])=nums.size();
      open_events.pop();
    }
    else if ('0'<=s[i] and s[i]<='9'){
      int val=0;
      while ('0'<=s[i] and s[i]<='9'){
        (val*=10)+=(s[i++]-'0');
      }
      nums.push_back(val);
      --i;
    }
  }

  for (size_t i=0; i<events.size();){
    switch (get<0>(events[i])){
      case SHUFFLE:
        sort(nums.begin()+get<1>(events[i]),nums.begin()+get<2>(events[i]),Comp<int>());
        break;
      case SORT:
        sort(nums.begin()+get<1>(events[i]),nums.begin()+get<2>(events[i]));
        break;
      default:
        ++i;
        continue;
    }
    for (auto j=i; i<events.size() and get<1>(events[i])<get<2>(events[j]); i++);
  }
  return nums;
}

int main(){
  string a,b; cin>>a>>b;
  if (eval<less>(a)==eval<less>(b) and eval<greater>(a)==eval<greater>(b)){
    cout<<"equal"<<endl;
  }else{
    cout<<"not equal"<<endl;
  }
}
