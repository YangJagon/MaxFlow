#pragma once
#include<vector>
#include<queue>
#include"edge.h"
#include<algorithm>
using namespace std;

#define MAX_POINT 1010

class EK
{	//默认0是源结点，V-1是汇结点
private:
	int V, E;
	int s, t;
	int f[MAX_POINT], pre[MAX_POINT];
	vector<int> map[MAX_POINT];
	vector<edge> edges;
	queue<int> path;
	int bfs();
public:
	EK(int v=0, int e=0);
	void addEdge(int h, int t, int c);
	int maxFlow();
};

