#include<random>
#include<time.h>
#include<set>
#include<string>
#include<fstream>
using namespace std;

void create(int n, int m, string name, default_random_engine re)
{
	ofstream out(name);
	out << n << " " << m << endl;

	/*default_random_engine re;
	re.seed((unsigned)time(NULL));*/
	uniform_int_distribution<int> unif(1, 100);
	uniform_int_distribution<int> point(0, n-1);

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