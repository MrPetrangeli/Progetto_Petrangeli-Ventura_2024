#include <bits/stdc++.h>
using namespace std;
pair<vector<int>, int> evolve1y(vector<int> V, int n)
{
	double e = 2.7182818;
	double A = 0.0002;
	double B = 0.0001;
	double C = 0.1;
	n = 0;
	for(int i = 150; i > 0; i--)
	{
		V[i] = 0;
		for(int j = 0; j < V[i - 1]; j++)
		{
			int a = rand();
			if((double(a)/double(RAND_MAX)) > (double(1.0) - (pow(e, -(A + (B * pow(e, C * (i - 2))))))))//la popolazione non deceduta sale di un anno d'età, i 150enni decedono
			{
				V[i]++;
				n++;
			}
		}
	}
	int r = 0;
	for(int i = 22; i < 42; i++) for(int j = 0; j < V[i]; j++)
	{
		int a = rand();
		if((double(a)/double(RAND_MAX)) < (double(4.0) / double(i - 2))) r++;
	}//persone riprodotte tra quelle che sono ancora vive e l'anno prima erano nella fascia d'età [20 - 40]
	r/= 2;
	cout << r << ' ';
	V[0] = r;
	n+= V[0];
	return make_pair(V, n);
}
int main()
{
	int d = 1000;
	srand(1991302);
	ofstream fout("population_over_time.dat", ios_base::out);
	vector<int> V(151, 0);
	V[26] = 40;
	pair<vector<int>, int> P = make_pair(V, 40);
	cout << "0 40\n";
	fout << "0 40\n";
	for(int i = 1; i <= d; i++)
	{
		P = evolve1y(P.first, P.second);
		cout << i << ' ' << P.second << '\n';
		fout << i << ' ' << P.second << '\n';
	}
	fout.close();
	ofstream gout ("population_over_time_plotter.txt", ios_base::out);
	gout << "plot 'population_over_time.dat' using 1:2 with lines" << "\n" << "set xrange[0:" << d << "]\nset yrange[0:" << double(P.second)*1.05 << "]\nreplot\n";
	gout << "pause -1";
	gout.close();
	system("pause -1");
	system("gnuplot population_over_time_plotter.txt");
	system("pause -1");
}
