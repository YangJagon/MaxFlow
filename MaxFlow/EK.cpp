#include "EK.h"

EK::EK(int v, int e) : V(v), E(e), s(0), t(v-1) {};

int EK::bfs()
{
	while (!path.empty())
		path.pop();

	path.push(s);
	memset(f, -1, sizeof(f));
	f[s] = INT_MAX;

	while (!path.empty())
	{
		int now = path.front();
		path.pop();

		for (int e : map[now])
		{
			edge& tmp = edges[e];
			if (tmp.capcity && f[tmp.tail] < 0)
			{
				f[tmp.tail] = min(tmp.capcity, f[now]);
				pre[tmp.tail] = e;
				if (tmp.tail == t)
					return f[tmp.tail];
				path.push(tmp.tail);
			}
		}
	}

	return 0;
}

void EK::addEdge(int h, int t, int c)
{
	edges.push_back(edge(h, t, c));
	edges.push_back(edge(t, h, 0));
	int l = edges.size() - 1;
	map[h].push_back(l - 1);
	map[t].push_back(l);
}

int EK::maxFlow()
{
	int sumFlow = 0;
	int increase = 0;

	while (increase = bfs())
	{
		sumFlow += increase;
		int last = t;

		while (last != s)
		{
			int e = pre[last];
			edges[e].capcity -= increase;
			edges[e ^ 1].capcity += increase;
			last = edges[e].head;
		}
	}

	return sumFlow;
}