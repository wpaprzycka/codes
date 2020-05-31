#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <iomanip>
#include <string>

using namespace std;
vector< vector <int> > nad_lista;
vector< vector <int> > nowa_nad_lista;


void wczytaj(vector<vector<int>>$nad_lista);
int sprzezony(vector<vector<int>>$nad_lista);
void liniowy(vector<vector<int>>$nad_lista);
void transformacja(vector<vector<int>>$nad_lista, vector<vector<int>>$nowa_nad_lista);
void zapis(vector<vector<int>>$nowa_nad_lista);
int multigraf(vector<vector<int>>$nad_lista);


int main()
{

	wczytaj(nad_lista);

	bool sprzez = sprzezony(nad_lista);
	if(sprzez)
		liniowy(nad_lista);
	
	if (sprzez)
		transformacja(nad_lista, nowa_nad_lista);

	zapis(nowa_nad_lista);

	system("pause");

	return 0;
}


/* WCZYTYWANIE GRAFU*/


void wczytaj(vector<vector<int>>$nad_lista)
{
	string wiersz;
	int wierzcholek;
	int iter = -1;

	fstream plik;
	plik.open("plik_zad1.txt", ios::in);

	while (!plik.eof())
	{
		getline(plik, wiersz);
		if (wiersz == ";")
		{
			nad_lista.push_back(vector<int>());
			iter++;
		}
		else
		{
			wierzcholek = atoi(wiersz.c_str());
			nad_lista[iter].push_back(wierzcholek);
		}
	}
	plik.close();

	for (int i = 0; i < nad_lista.size(); i++)
	{
		for (int j = 0; j < nad_lista[i].size(); j++)
		{
			cout << nad_lista[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}


/* CZY MULTIGRAF*/


int multigraf(vector<vector<int>>$nad_lista)
{	
	bool nie_multi = true;

	for (int i = 0; i < nad_lista.size(); i++)
	{
		if (nad_lista[i].size() > 2)
		{
			for(int j = 1; j < nad_lista[i].size()-1; j++)
			{	
				if (nad_lista[i][j] == nad_lista[i][j + 1])
				{	
					nie_multi = false;
					return nie_multi;
				}
			}
		}		
	}
	return nie_multi;
}



/*CZY SPRZEZONY */

int sprzezony(vector<vector<int>>$nad_lista)
{
	bool sprzezony = false;
	bool nie_multi = multigraf(nad_lista);

	if(nie_multi)
	{
		bool sprzezony = true;

		for (int i = 0; i < nad_lista.size(); i++)
		{
			if (nad_lista[i].size() > 1)
			{
				for (int k = (i + 1); k < nad_lista.size() - 1; k++)
				{
					if (nad_lista[k].size() > 1)
					{
						int total = 0;
						bool jest = false;

						int rozmiar = (nad_lista[i].size() - 1);
						int * tab = new int[rozmiar];

						for (int z = 0; z < rozmiar; z++)
							tab[z] = 0;					

						for (int j = 1; j < nad_lista[i].size(); j++)
						{
							int m = j - 1;

							for (int l = 1; l < nad_lista[k].size(); l++)
							{
								if (nad_lista[i][j] == nad_lista[k][l])
								{
									jest = true;
									tab[m] = 1;
								}												
							}
						}
						for (int p = 0; p < rozmiar; p++)
						{
							total += tab[p];
						}

						if (total == 0 || total == rozmiar)
							sprzezony = true;
						else
						{
							sprzezony = false;
							break;
						}

						if (nad_lista[i].size() < nad_lista[k].size() && total == rozmiar)
						{
							sprzezony = false;
							break;
						}
						delete[] tab;
					}

				}
				if (!sprzezony)
					break;
			}

		}


		if (sprzezony)
			cout << "sprzezony" << endl;
		else if (!sprzezony)
			cout << "nie-sprzezony" << endl;

		return sprzezony;
	}
	else
	{	
		cout << "nie-sprzezony - multigraf" << endl;
		return sprzezony;
	}
		
	
}


/* CZY LINIOWY */


void liniowy(vector<vector<int>>$nad_lista)
{
	
// struktura 1 i 2 

	bool struktura1 = false;
	bool jeden = false;
	bool dwa = false;
	bool trzy = false;
	int linia = 0;
	int tutaj = 0;
	int mamy = 0;


	for (int i = 0; i < nad_lista.size(); i++)
	{
		if (nad_lista[i].size() > 2)
		{
			for (int j = 1; j < nad_lista[i].size(); j++)
			{
				for (int m = 0; m < nad_lista.size(); m++)
				{
					if (m != i)
					{
						if (nad_lista[i][j] == nad_lista[m][0])
						{
							tutaj = m;
							jeden = true;

							for (int k = (j + 1); k < nad_lista[i].size(); k++)
							{
								if (nad_lista[i][k] != nad_lista[i][j])
								{
									for (int n = 0; n < nad_lista.size(); n++)
									{
										if (n != i)
										{
											if (nad_lista[i][k] == nad_lista[n][0])
											{
												mamy = n;
												dwa = true;
												break;
											}
										}
									}
								}
								
							}

							if (!dwa)
							{
								jeden = false;
								break;
							}

							if (jeden && dwa)
								break;
						}
					}
				}

				if (!dwa)
				{
					jeden = false;
					break;
				}

				if (jeden && dwa)
					break;
			}
		}

		if (jeden && dwa)
			break;
			
	}

	if (jeden && dwa)
	{
		for (int i = 1; i < nad_lista[tutaj].size(); i++)
		{
			for (int j = 1; j < nad_lista[mamy].size(); j++)
			{
				if (nad_lista[tutaj][i] == nad_lista[mamy][j])
					trzy = true;
			}
		}
	}

	if (jeden && dwa && trzy)
		struktura1 = true;

	
	// struktura 3

	bool struktura3 = false;

	for (int i = 0; i < nad_lista.size(); i++)
	{
		for (int j = 1; j < nad_lista[i].size(); j++) // czy wierzcholek i ma siebie
		{
			if (nad_lista[i][j] == nad_lista[i][0])
			{
				for (int k = 1; k < nad_lista[i].size(); k++) //  kolejne nastepniki i
				{
					for (int l = 0; l < nad_lista.size(); l++)
					{
						if (l != i)
						{
							if (nad_lista[l][0] == nad_lista[i][k]) // nastepnik staje sie wierzcholkiem [l][0]
							{
								for (int m = 1; m < nad_lista[l].size(); m++)
								{
									if (nad_lista[l][m] == nad_lista[l][0]) // czy wierzcholek l ma siebie
									{
										for (int n = 1; n < nad_lista[l].size(); n++)
										{
											if (nad_lista[l][n] == nad_lista[i][0]) //czy ma nastepnika rownego wierzcholkowi i
											{
												struktura3 = true;
												break;
											}
										}
									}
								}
								if (struktura3)
									break;								
							}
							if (struktura3)
								break;
						}
						if (struktura3)
							break;
					}
				}
			}
			if (struktura3)
				break;
		}
		if (struktura3)
			break;
	}

	if (struktura1 || struktura3)
		cout << "nie-liniowy" << endl;
	else
		cout << "liniowy" << endl << endl;
}


/*TRANSFORMACJA */


void transformacja(vector<vector<int>>$nad_lista, vector<vector<int>>$nowa_nad_lista)
{
	
		int nowy_wierzch = 1;
		int l_wierzcholkow = nad_lista.size();

		for (int i = 0; i < l_wierzcholkow; i++)
		{
			nowa_nad_lista.push_back(vector<int>());

			for (int j = 0; j < 2; j++)
			{
				nowa_nad_lista[i].push_back(nowy_wierzch);
				nowy_wierzch++;
			}
		}
		//wyswietl nadmiarowy graf
/*		for (int i = 0; i < nowa_nad_lista.size(); i++)
		{
			for (int j = 0; j < nowa_nad_lista[i].size(); j++)
			{
				cout << nowa_nad_lista[i][j] << " ";
			}
			cout << endl;
		}
*/
		int zmienna = 0;
		int linia = 0;
		int roznica = 0;

		int it = 0;

		for (int i = 0; i < nad_lista.size(); i++)
		{
			for (int j = 1; j < nad_lista[i].size(); j++)
			{
				zmienna = nad_lista[i][j];

				for (int k = 0; k < nad_lista.size(); k++)
				{
					if (nad_lista[k][0] == zmienna)
					{
						linia = k;
						break;
					}
				}
				
				roznica = linia - i;
				int porownak = nowa_nad_lista[i + roznica][0];

				nowa_nad_lista[i + roznica][0] = nowa_nad_lista[i][1];

				for (int k = 0; k < nowa_nad_lista.size(); k++)
				{
					if (nowa_nad_lista[k][1] == porownak)
						nowa_nad_lista[k][1] = nowa_nad_lista[i][j];
				}
			}
		}

		cout << endl;

		for (int i = 0; i < nowa_nad_lista.size(); i++)
		{
			for (int j = 0; j < nowa_nad_lista[i].size(); j++)
			{
				cout << nowa_nad_lista[i][j] << " ";
			}
			cout << endl;
		}
		
		for (int i = 0; i < nowa_nad_lista.size(); i++)
		{
			for (int k = i + 1; k < nowa_nad_lista.size(); k++)
			{

				if (nowa_nad_lista[i][0] == nowa_nad_lista[k][0])
				{
					nowa_nad_lista[i].push_back(nowa_nad_lista[k][1]);
				}


			}
		}

	cout << endl << "nowa_nad_lista: " << endl;

		for (int i = 0; i < nowa_nad_lista.size(); i++)
		{
			for (int j = 0; j < nowa_nad_lista[i].size(); j++)
			{
				cout << nowa_nad_lista[i][j] << " ";
			}
			cout << endl;
		}

	

	


}


/*ZAPIS DO PLIKU */

void zapis(vector<vector<int>>$nowa_nad_lista)
{
	fstream plik_out("graf oryginalny.txt", std::ios::out);

	bool izol = true;
	vector <int> izolki;

	if (plik_out.good())
	{
		for (int i = 0; i < nowa_nad_lista.size(); i++)
		{
			bool juz_jest = false;
			izol = true;

			if (i == 0)
				plik_out << ";" << "\n";
			else
			{
				for (int z = 0; z < i; z++)
				{
					if (nowa_nad_lista[i][0] == nowa_nad_lista[z][0])
					{
						juz_jest = true;
						break;
					}
				}
			}

			if (!juz_jest)
			{
				if (i != 0)
					plik_out << ";" << "\n";

				for (int j = 0; j < nowa_nad_lista[i].size(); j++)
				{
					if (i == 0)
					{
						plik_out << nowa_nad_lista[i][j] << "\n";
					}
					else
					{
						plik_out << nowa_nad_lista[i][j] << "\n";
					}
					if (j != 0)
					{
						for (int k = 0; k < nowa_nad_lista.size(); k++)
						{
							if (nowa_nad_lista[i][j] == nowa_nad_lista[k][0])
							{
								izol = false;
								break;
							}
						}
						if (izol)
							izolki.push_back(nowa_nad_lista[i][j]);
					}
				}
			}
			for (int l = 0; l < izolki.size(); l++)
			{
				plik_out << ";" << "\n";
				plik_out << izolki[l] << "\n";
			}
			izolki.clear();
		}
		plik_out.close();
		//cout << endl << "zapisano do pliku" << endl;
	}

}