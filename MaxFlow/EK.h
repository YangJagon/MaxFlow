#pragma once
#include<vector>
#include<queue>
#include"edge.h"
#include<algorithm>
using namespace std;

#define MAX_POINT 1010

class EK
{	//Ĭ��0��Դ��㣬V-1�ǻ���
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

