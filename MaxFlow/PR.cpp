#include "PR.h"
#include<iostream>

PR::PR(int v, int e) : V(v), E(e), s(0), t(v - 1) {};

void PR::addEdge(int h, int t, int c)
{
	edges.push_back(edge(h, t, c));
	edges.push_back(edge(t, h, 0));
	int l = edges.size() - 1;
	map[h].push_back(l - 1);
	map[t].push_back(l);
}

void PR::push(int index)	//输入边的下标
{
	edge & e1 = edges[index];
	edge & e2 = edges[index ^ 1];

	int increase = min(e[e1.head], e1.capcity);
	e1.capcity -= increase;
	e2.capcity += increase;

	e[e1.head] -= increase;
	e[e1.tail] += increase;
}

//void PR::relabel(int u)
//{
//	int min = INT_MAX;
//	for (int i : map[u])
//		if ((min > h[edges[i].tail]) && edges[i].capcity)
//			min = h[edges[i].tail];
//	h[u] = ++min;
//}

void PR::intialize_preflow()
{
	memset(h, 0, sizeof(h));
	memset(e, 0, sizeof(e));
	memset(current, 0, sizeof(current));
	h[s] = V;

	for (int i : map[0])
	{
		int tmp = edges[i].capcity;
		e[edges[i].tail] += tmp;
		e[0] -= tmp;

		edges[i ^ 1].capcity = tmp;
		edges[i].capcity = 0;
	}
}

//void PR::discharge(int u)
//{
//	while (e[u] > 0)
//	{
//		int ei = current[u];
//		if (ei >= map[u].size())
//		{
//			relabel(u);
//			current[u] = 0;
//		}
//		else if ((edges[map[u][ei]].capcity > 0) && (h[edges[map[u][ei]].head] > h[edges[map[u][ei]].tail]))
//			push(map[u][ei]);
//		else current[u]++;
//	}
//}

//int PR::maxFlow()
//{
//	intialize_preflow();
//	list<int> topo;
//	for (int i = 1; i < t; i++)
//		topo.push_back(i);
//	list<int>::iterator it = topo.begin();
//
//	while (it != topo.end())
//	{
//		int old_height = h[*it];
//		discharge(*it);
//		if (old_height < h[*it])
//		{
//			int tmp = *it;
//			topo.erase(it);
//			topo.push_front(tmp);
//			it = topo.begin();
//		}
//		++it;
//	}
//
//	return e[t];
//}


/***********************************************************************************/
void PR::discharge(int u)
{
	int height = h[u];
	while (e[u] > 0)
	{
		for (int ei : map[u])
		{
			if ((edges[ei].capcity > 0) && (height > h[edges[ei].tail]))
			{
				push(ei);
				if (e[u] == 0)
					return;
			}
		}
		relabel(u);
	}
}

bool PR::relabel(int u)
{
	int min = INT_MAX;
	for (int i : map[u])
		if ((min > h[edges[i].tail]) && edges[i].capcity)
			min = h[edges[i].tail];
	h[u] = min+1;

	for (int ei : map[u])
	{
		if (h[edges[ei].tail] == min && edges[ei].capcity)
			push(ei);
		if (e[u] == 0)
			break;
	}
	return true;
}

int PR::maxFlow()
{
	intialize_preflow();
	bool flag = true; //表示是否还有relabel操作
	while (flag)
	{
		flag = false;
		for (int i = 1; i < t; i++)
			if (e[i] > 0)
			{
				relabel(i);
				//discharge(i);
				flag = true;
			}
	}
	return e[t];
}
