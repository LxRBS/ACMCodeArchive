#include <vector>
#include <set>
#include "streamcorr.h"

const int MIN_FREQ = 0;
const int MAX_FREQ = 1000000000-1;
using namespace std;
#define FOR(i,a,b) for (int i = (a); i < (b); i++)

int N, from, to, channel[2][10005][2];
set<int> usedChannels[2];
vector<int> adj[10005];

void check() {
	FOR(node, 0, N) {
		set<int> here[2];
		// channels on this side of the edge
		FOR(j, 0, 2) FOR(k, 0, 2) here[k].insert(channel[k][node][j]);
		for (auto next : adj[node]) {
			bool connected[2] = {false, false};
			FOR(j, 0, 2) FOR(k, 0, 2) 
				if (here[k].count(channel[k][next][j])) {
					usedChannels[k].insert(channel[k][next][j]);
					connected[k] = true; // edges share same freq
				}
			if (!connected[0])
				report_error("nodes %d and %d do not share a frequency in team output", node+1, next+1);
			if (!connected[1])
				judge_error("nodes %d and %d do not share a frequency in judge solution", node+1, next+1);
		}
	}

	if (usedChannels[0].size() > usedChannels[1].size()) {
		judge_error("Team solution is better than judge solution! (team %d vs. judge %d)\n",
					usedChannels[0].size(), usedChannels[1].size());
	}
	if (usedChannels[0].size() != usedChannels[1].size()) {
		report_error("incorrect number of channels: %d vs %d (team vs. judge)", usedChannels[0].size(), usedChannels[1].size());
	}
}

int main(int argc, char **argv) {
	init_io(argc, argv);

	// reading input
	judge_in >> N;
	FOR(i, 0, N-1) {
		judge_in >> from >> to;
		from--, to--;
		adj[from].push_back(to);
		adj[to].push_back(from);
	}

	// reading judge output
	FOR(i, 0, N) FOR(j, 0, 2) {
		if (!(judge_ans >> channel[1][i][j]))
			judge_error("failed to read freq %d of node %d from judge answer", j+1, i+1);
		if (channel[1][i][j] < MIN_FREQ || channel[1][i][j] > MAX_FREQ)
			judge_error("channel freq %d of node %d out of bounds in judge data\n", j+1, i+1);
	}

	// reading contestant output
	FOR(i, 0, N) FOR(j, 0, 2) {
		if (!(author_out >> channel[0][i][j]))
			report_error("cannot read freq %d of node %d from team output", j+1, i+1);
		if (channel[0][i][j] < MIN_FREQ || channel[0][i][j] > MAX_FREQ) 
			report_error("channel freq %d of node %d out of bounds in team output", j+1, i+1);
	}
	
	// do the real checking
	check();

	/* Check for trailing output in author file. */
	string trash;
	if (author_out >> trash) report_error("Trailing output in team output");
	if (judge_ans >> trash) judge_error("Trailing output in judge data");

	/* Yay! */
	accept();
	return 0;
}
