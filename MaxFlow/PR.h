#pragma once
#include<vector>
#include<queue>
#include"edge.h"
#include<algorithm>
#include<list>
using namespace std;

#define MAX_POINT 1010

class PR
{
private:
	int sumFlow, V, E;
	int s, t;
	int h[MAX_POINT], e[MAX_POINT], current[MAX_POINT];
	vector<int> map[MAX_POINT];
	vector<edge> edges;
	void push(int e);
	bool relabel(int u);
	void intialize_preflow();
	void discharge(int u);
public:
	PR(int v=0, int e=0);
	void addEdge(int h, int t, int c);
	int maxFlow();
};

