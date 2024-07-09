#include <bits/stdc++.h>
#include "libreriaP.cpp"
using namespace std;
const int d = 70;
const int n = 10000;
pair<int, pair<vector<int>, vector<int>>> diffuse1d(vector<vector<int>> N, int c, vector<int> B, vector<int> G)
{
	int newi = 0;
	bool p = 0.001;
	vector<bool> newB(n, false);
	for(int i = 0; i < n; i++) if(B[i])
	{
		B[i]--;
		if(!B[i]) c--;
	}
	for(int i = 0; i < n; i++)
	{
		if(B[i])
		{
			for(int j = 0; j < N[i].size(); j++) if(!B[N[i][j]]&&!newB[N[i][j]])
			{
				int a = rand();
				double b = double(a);
				if(G[N[i][j]]) b*= (G[N[i][j]] * 15);
				if(b / double(RAND_MAX) < p)
				{
					newB[N[i][j]] = true;
					G[N[i][j]]++;
					c++;
					newi++;
				}
			}
		}
	}
	for(int i = 0; i < n; i++) if(newB[i]) B[i] = d;
	cout << newi << ' ';
	return make_pair(c, make_pair(B, G));
}
int main()
{
	int d = 1500;
	srand(1991302);
	ofstream fout("epidemy_diffusion_3.0.dat", ios_base::out);
	double p = 0.0003;
	vector<vector<int>> V = prandomgraph(n, p);
	for(int i = 0; i < n; i++) V[i][i] = 0;
	vector<vector<int>> N(n);
	for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) if(V[i][j]) N[i].push_back(j);
	vector<int> B(n, 0);
	B[0] = B[1] = B[2] = B[3] = B[4] = d;
	vector<int> G(n, 0);
	G[0] = G[1] = G[2] = G[3] = G[4] = 1;
	int c = 5;
	pair<int, pair<vector<int>, vector<int>>> P = make_pair(c, make_pair(B, G));
	fout << "0 5\n";
	cout << "0 5\n";
	for(int i = 1; i <= d; i++)
	{
		P = diffuse1d(N, P.first, P.second.first, P.second.second);
		fout << i << ' ' << P.first << '\n';
		cout << i << ' ' << P.first << '\n';
	}
	fout.close();
	ofstream gout ("epidemy_diffusion_plotter_3.0.txt", ios_base::out);
	gout << "plot 'epidemy_diffusion_3.0.dat' using 1:2 with lines" << "\n" << "set xrange[0:" << d << "]\nset yrange[0:" << n << "]\nreplot\n";
	gout << "pause -1";
	gout.close();
	system("pause -1");
	system("gnuplot epidemy_diffusion_plotter_3.0.txt");
	system("pause -1");
}
