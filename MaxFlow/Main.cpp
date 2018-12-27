#include<iostream>
#include<fstream>
#include<Windows.h>
#include<random>
#include<time.h>
#include<set>
#include "EK.h"
#include "PR.h"
using namespace std;
void create(int n, int m, string name, default_random_engine re);
#define MAX 200

default_random_engine re;
uniform_int_distribution<int> unif(1, 100);
uniform_int_distribution<int> point(0, MAX-1);

void create(int n, int m, string name)
{
	ofstream out(name);
	out << n << " " << m << endl;

	/*default_random_engine re;
	re.seed((unsigned)time(NULL));
	uniform_int_distribution<int> unif(1, 100);
	uniform_int_distribution<int> point(0, n - 1);*/

	set<pair<int, int>> count;
	while (count.size() < m)
	{
		int x = point(re);
		int y = point(re);
		int z = unif(re);

		pair<int, int> tmp(x, y);
		pair<int, int> tmp2(y, x);
		if ((count.find(tmp) == count.end()) && (count.find(tmp2) == count.end()))
		{
			out << x << " " << y << " " << z << endl;
			count.insert(tmp);
		}
	}

	out.close();
}

int main()
{
	re.seed((unsigned)time(NULL));

	double dqfreq;
	_LARGE_INTEGER time_start;
	_LARGE_INTEGER time_over;
	_LARGE_INTEGER f;
	QueryPerformanceFrequency(&f);
	dqfreq = (double)f.QuadPart;

	int n, m;
	//cin >> times;
	
	int point = MAX;
	int max = (point * (point - 1)) / 2;
	double rate = 0.5;
	int times = 10;

	double run_time1 = 0;
	double run_time2 = 0;

	for (int i = 0; i < times; i++)
	{
		int edge = max * rate;
		create(point, edge, "graph.txt");
		ifstream in("graph.txt");

		in >> n >> m;
		EK ek(n, m);
		PR pr(n, m);
		for (int i = 0; i < m; i++)
		{
			int x, y, z;
			in >> x >> y >> z;
			ek.addEdge(x, y, z);
			pr.addEdge(x, y, z);
		}

		/*QueryPerformanceCounter(&time_start);
		int a = ek.maxFlow();
		QueryPerformanceCounter(&time_over);
		run_time1 += 1000 * (time_over.QuadPart - time_start.QuadPart) / dqfreq;*/

		QueryPerformanceCounter(&time_start);
		int b = pr.maxFlow();
		QueryPerformanceCounter(&time_over);
		run_time2 += 1000 * (time_over.QuadPart - time_start.QuadPart) / dqfreq;

		cout << b << endl;
	}
	cout << run_time2 / times << endl;
	//cout << "PR Time: " << run_time2 / times << " ms" << endl;


	return 0;
}