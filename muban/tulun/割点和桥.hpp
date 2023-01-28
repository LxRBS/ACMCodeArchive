
namespace TULUN{

struct CutAndBridge{

const Graph & g;

int BridgeCnt;//桥的数量
vector<bool> IsCut;//点i是否为割点
vector<bool> IsBridge;//边i是否为桥
vector<int> AddBlocks;// ABi表示删除i点之后多出来的块数

CutAndBridge() = delete;
CutAndBridge(const Graph & gg):g(gg){
    auto vn = g.node_size();
	auto en = g.edges.size();

	Dfn.assign(vn + 1, TimeStamp = BridgeCnt = 0);	
	Low.assign(vn + 1, 0);
	
	AddBlocks.assign(vn + 1, 0);
	IsCut.assign(vn + 1, false);

	IsBridge.assign(en, false);
	IsVisited.assign(en, false);    

	for(int i=1;i<=vn;++i)if(0==Dfn[i])dfs(i, i);
	return;
}

void dfs(int u, int pre){
	Dfn[u] = Low[u] = ++TimeStamp;

	int v, son = 0;
	for(auto i : g[u]){
		IsVisited[i] = IsVisited[i ^ 1] = true;
		const auto & e = g.edges[i];
        if(0 == Dfn[v = get<1>(e)]){
            ++son;
			dfs(v, u);
			if(Low[v] < Low[u]) Low[u] = Low[v];

			/// 这个if是桥
			if(Dfn[u] < Low[v]){
				IsBridge[i] = IsBridge[i ^ 1] = true;
				++BridgeCnt;
			}

			/// 这个if是割点
			if(u != pre && Dfn[u] <= Low[v]){
				IsCut[u] = true;
				++AddBlocks[u];
			}
		}else if(Dfn[v] < Low[u]){
            Low[u] = Dfn[v];
		}
	}

	/// 符合割点的条件1
	if(u == pre && son > 1) IsCut[u] = true;
	if(u == pre) AddBlocks[u] = son - 1;
}


int TimeStamp;
vector<int> Dfn, Low;
vector<bool> IsVisited; //边的标记数组


};

}
