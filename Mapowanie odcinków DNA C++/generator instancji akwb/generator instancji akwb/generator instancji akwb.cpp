// generator instancji akwb.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "pch.h"
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>    
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>


using namespace std;

int k = 5; // liczba ciec 
int n = k + 2;
int liczba_fragmentow = k + 1;

vector<int> vec_frag_dlug;
vector <int> multizbior_A;

int main()
{
	srand(time(NULL));
	int dlugosc = rand() % 5 + 200;

	cout << "dlugosc : " << dlugosc << endl << endl;

	int frag_pozostale = liczba_fragmentow - 1;
	int akt_dlug = dlugosc;
	int max_dlug = 0;
	int dlug_fragmentu = 0;

	//cout << "fragmenty : " << fragmenty << endl;
	//cout << "frag_pozostale : " << frag_pozostale << endl;
	//cout << "skt_dlug : " << akt_dlug << endl << endl;


	for (int i = 0; i < liczba_fragmentow; i++)
	{
		if (i == liczba_fragmentow - 1)
		{
			max_dlug = akt_dlug - frag_pozostale;
			dlug_fragmentu = max_dlug;
			vec_frag_dlug.push_back(dlug_fragmentu);
		}
		else
		{
			max_dlug = akt_dlug - frag_pozostale;
			//cout << "max_dlug : " << max_dlug << endl;

			dlug_fragmentu = rand() % max_dlug + 1;
			//cout << "dlug_fragmetnu : " << dlug_fragmentu << endl;

			vec_frag_dlug.push_back(dlug_fragmentu);

			akt_dlug = akt_dlug - dlug_fragmentu;
			//cout << "akt_dlug : " << akt_dlug << endl;
			frag_pozostale--;
			//cout << "frag_pozostale : " << frag_pozostale << endl << endl;
		}
	}

	int total = 0;
	cout << "k = " << k << endl;
	cout << "fragmenty: ";
	for (int j = 0; j < vec_frag_dlug.size(); j++)
	{
		cout << vec_frag_dlug[j] << " ";
		total += vec_frag_dlug[j];

	}
	//cout << endl << "total : " << total;


	for (int i = 0; i < vec_frag_dlug.size(); i++)
	{
		multizbior_A.push_back(vec_frag_dlug[i]);
		int cos = vec_frag_dlug[i];

		for (int j = i+1; j < vec_frag_dlug.size(); j++)
		{
			cos += vec_frag_dlug[j];
			multizbior_A.push_back(cos);
		}

		cos = 0;
	}

	//for (int i = 0; i < multizbior_A.size(); i++)
		//cout << multizbior_A[i] << " ";

	//cout << endl << " ile : " << multizbior_A.size()<<endl<<endl;

	sort(multizbior_A.begin(), multizbior_A.end());
	cout << endl<< "mapa: ";
	for (int i = 0; i < multizbior_A.size(); i++)
		cout << multizbior_A[i] << " ";

	cout << endl<< " a size : " << multizbior_A.size()<<endl;


	fstream plik;
	string sciezka = "C:/Users/Konto/source/repos/ostatni program/ostatni program/plik.txt";
	plik.open( sciezka ,std::ios::out);

	if (plik.good())
	{
		for (int i = 0; i < multizbior_A.size(); i++)
		{
			if (i == multizbior_A.size() - 1)
				plik << multizbior_A[i];
			else 
				plik << multizbior_A[i] << " ";
		}
		plik.close();
	}


	fstream plik_1;
	string sciezka_1 = "C:/Users/Konto/source/repos/ostatni program/ostatni program/rozwiazanie.txt";
	plik_1.open(sciezka_1, std::ios::out);

	if (plik_1.good())
	{
		for (int i = 0; i < vec_frag_dlug.size(); i++)
		{
			if (i == vec_frag_dlug.size() - 1)
				plik_1 << vec_frag_dlug[i];
			else
				plik_1 << vec_frag_dlug[i] << " ";
		}
		plik_1.close();
	}



}
