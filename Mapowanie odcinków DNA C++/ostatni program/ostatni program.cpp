// ostatni program.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <time.h>
#include <conio.h>

using namespace std;


/************************************************************* globalne *********************************************************/

vector <int> A;
vector <int> elem;
clock_t start, koniec;
double czas;

void wczytaj_multizbior(vector<int>);
void ile_elemntow(vector<int>);
void szukaj(int total, int *tab_rozw, int *tab_zuzyte, int ind, int *jest);

int l_frag;
int p_el;
int id_p;
int el_1;
int el_2;
int maxind;




int k = 5; // liczba ciec 
int n = k + 2;
int liczba_fragmentow = k + 1;

vector<int> vec_frag_dlug;
vector <int> multizbior_A;

void generuj();


/************************************************************* main *********************************************************/


int main()
{	
	//generuj(); 
	wczytaj_multizbior(A);
	cout <<endl << "A.size = " << A.size() << endl;
	ile_elemntow(A);
	
	maxind = l_frag -1;
	//cout << endl << "maxind " << maxind << endl;

	int * tab_rozw = new int[l_frag];
	for (int i = 0; i < l_frag; i++)
		tab_rozw[i] = 0;
	tab_rozw[0] = p_el;


	int * tab_zuzyte = new int[A.size()];  // dynamiczna tablica zuzytych elementow A
	for (int i = 0; i < A.size(); i++)
		tab_zuzyte[i] = 0;
	tab_zuzyte[id_p] = 1;

	int total = p_el;
	int jest=0;



	start = clock();
	szukaj(total, tab_rozw, tab_zuzyte, 0, &jest);
	koniec = clock();
	
	
	czas = (double)(koniec - start) / (double)(CLOCKS_PER_SEC);
	cout << "\n czas trwania to: "<< czas <<endl;

	if (jest == 0) 
	{ 
		cout << endl <<" BRAK ROZWIAZANIA " << endl;
	}

	cout << endl <<endl << "wzor = "  <<((l_frag + 1) * (l_frag)) / 2;
	//cout << endl << " id_p " << id_p;


}





void generuj()
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

		for (int j = i + 1; j < vec_frag_dlug.size(); j++)
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
	cout << endl << "mapa: ";
	for (int i = 0; i < multizbior_A.size(); i++)
		cout << multizbior_A[i] << " ";

	cout << endl << " a size : " << multizbior_A.size() << endl<<endl<<endl;


	fstream plik;
	string sciezka = "C:/Users/Konto/source/repos/ostatni program/ostatni program/plik_zad4.txt";
	plik.open(sciezka, std::ios::out);

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



/************************************************************* wczytaj multizbior *********************************************************/

void wczytaj_multizbior(vector<int> $A)
{
	fstream plik;
	string sciezka = "C:/Users/Konto/source/repos/ostatni program/ostatni program/plik_zad4.txt";
	plik.open(sciezka, std::ios::in);

	int cos = 0;

	if (plik.good())
	{
		while (!plik.eof())
		{
			plik >> cos;
			A.push_back(cos);
		}
	}
	plik.close();

	cout << "A: ";
	for (int i = 0; i < A.size(); i++)
		cout << A[i] << " ";

	int max = A[0];

	
	for (int i = 1; i < A.size(); i++)
	{
		if (A[i] > max)
		{	
			max = A[i];
		}	
	}
	
	int max_2 = A[0];
	if (max_2 == max)
	{
		max_2 = A[1];
		for (int j = 2; j < A.size(); j++)
		{
			if (A[j] > max_2)
				max_2 = A[j];
		}
	}
	else
	{
		for (int j = 1; j < A.size(); j++)
		{
			if(A[j] != max)
				if (A[j] > max_2)
					max_2 = A[j];
		}

	}
	
	//cout << endl << "max : " << max << endl;
	//cout << endl << "max_2 : " << max_2 << endl;
	p_el = max - max_2;
	//cout << endl<<"p_el = " << p_el << endl;

	el_1 = A[0];
	el_2 = A[1];

	for (int i = 0; i < A.size(); i++)
	{
		if (A[i] == p_el)
		{
			id_p = i;
			break;
		}
	
	}

}


void ile_elemntow(vector<int> $A)
{
	
	for (int i = 5; i < A.size(); i++)
	{
		//cout << ((i *(i - 1)) / 2) <<endl ;
		if (((i *(i - 1)) / 2) == A.size())
		{
			int l_pkt = i;
			l_frag = l_pkt - 1;
			cout <<"l_frag = "<< l_frag << endl;
			break;
		}

		if (((i *(i - 1)) / 2) > A.size())
		{
			cout << "zla licznosc wejscia" << endl;
			break;
		}

	}
}

void szukaj(int total, int *tab_rozw, int *tab_zuzyte, int ind, int *jest)
{
	int element;
	bool suma_jest = false;
	//cout << endl;
	//cout  << "tab_z : ";
	//for (int i = 0; i < A.size(); i++)
		//cout << tab_zuzyte[i];
	
	//cout << endl <<  "\t\t\tTOTAL: " << total << endl;
	
	//cout << "ind " << ind << endl;
	//cout << " maxind " << maxind << endl;

	for (int i = 0; i < A.size(); i++)
		tab_zuzyte[i] = 0;

	for (int i = 0; i < l_frag; i++)
	{
		//cout << endl<< "i= " << i << endl;
		//cout << "tab_rozw [i]  " << tab_rozw[i] << endl;
		//cout << "A.size  " << A.size() << endl;

		for (int j = 0; j < A.size(); j++)
		{
			//cout << " j= " <<j << endl;
			//cout << "tab_zuzyte[j] przed:  " << tab_zuzyte[j] << endl;
			if (A[j] == tab_rozw[i]) 
			{
				if (tab_zuzyte[j] == 0)
				{
					tab_zuzyte[j] = 1;
					//cout << endl << "tab[" << j << "] po: " << tab_zuzyte[j] << endl;
					break;
				}
			}
		}
		
	}
	/*cout << "tab_z : ";
	for (int i = 0; i < A.size(); i++)
		cout << tab_zuzyte[i];
	cout << endl;*/

	//cout << endl;
	
		if (ind == maxind)
		{
			//cout << "IND = MAXIND\n";
			bool rozwiazanie = true;
			vector < int > sumy;
			for (int i = 0; i < l_frag; i++)
			{		
				//cout << "tab_r[i]" << tab_rozw[i] << endl << endl;
				int cos = tab_rozw[i];
				sumy.push_back(cos);
				for (int j = i + 1; j < l_frag; j++)
				{
					//cout << "    tab_r[j]" << tab_rozw[j] << endl;
					int suma = cos + tab_rozw[j];
					cos += tab_rozw[j];
					sumy.push_back(suma);
				}
			}
			sort(sumy.begin(), sumy.end());
			sort(A.begin(), A.end());

			/*cout << endl << "tab_rozw :";
			for (int i = 0; i < l_frag; i++)
				cout << tab_rozw[i] << " ";
			cout << endl;

			cout << "sumy :";
			for (int i = 0; i < sumy.size(); i++)
				cout << sumy[i] << " ";

			cout << endl<< "A    :";
			for (int i = 0; i < A.size(); i++)
				cout << A[i] << " ";*/
				
			if (sumy.size() != A.size())
				rozwiazanie = false;
			else if (sumy.size() == A.size())
				for (int k = 0; k < sumy.size(); k++)
				{
					if (sumy[k] != A[k])
					{
						rozwiazanie = false;
						break;
					}
				}

			if (rozwiazanie)
			{
				cout << endl << "  rozwiazanie : ";
				for (int r = 0; r < l_frag; r++)
					cout << tab_rozw[r] << " ";
				*jest = 1;
			}
			else
			{
				int ten = tab_rozw[ind];
				for (int i = 0; i < A.size(); i++)
				{
					if (ten == A[i])
					{
						tab_zuzyte[i] = 0;
						break;
					}
				}
			}

		}
		else for (int a = 0; a <A.size(); a++)  //przechodzimy przez multizbior  - [i] szuka elementu 
		{	
			bool warto = true;

			if (tab_zuzyte[a] == 0)
			{
				element = A[a];
				tab_rozw[ind + 1] = element;

				/*cout << "tab_rozw [z]  ";
				for(int z = 0; z < l_frag; z++)
					cout  << tab_rozw[z] << " ";
				cout << endl;*/

				for (int i = 0; i < l_frag-1; i++)									//sprawdzamy czy sumy elementow sa w A
				{
					//cout << "tab_r[i]" << tab_rozw[i] << endl<<endl;
					int sklad = tab_rozw[i];
					for (int j = i + 1; j < l_frag; j++)
					{
						//cout << "    tab_r[j]" << tab_rozw[j] << endl;
						int suma = sklad + tab_rozw[j];
						sklad += tab_rozw[j];
						//cout << "    suma " << suma << endl<<endl;
						suma_jest = false;

						if (suma == 0)
							suma_jest = true;
						else
							for (int k = 0; k < A.size(); k++)
							{
								if (suma == A[k])						
									suma_jest = true;							
							
							}
						if (!suma_jest)
						{
							warto = false;
							//cout << "nie ma fal" << endl << endl;
							tab_rozw[ind + 1] = 0;
							break;
						}
						else
							warto = true;
					}
					if(!suma_jest)
						break;
				}
				if (warto)
				{
					//cout << "warto " << endl;
					//cout << " rozw : " << endl;
					//for (int i = 0; i < l_frag; i++)
					//	cout << tab_rozw[i] << " ";
					//cout << endl;

					//cout <<endl << "ind +1 = " << ind + 1 << endl;
					//cout << "jest " << *jest << endl;

					szukaj(total + element, tab_rozw, tab_zuzyte, ind + 1, jest);

				}
			}
			if (*jest == 1) 
				break;			
		}
}




/*
int indeks = 0;


	cout << endl << "wszedlem" << endl;
	cout << "vec: ";

	if (elem.size() < A.size())
	for (int c = 0; c < elem.size(); c++)
		cout << elem[c] << " ";

	int total = 0;
	int wzor = ((l_frag+1) * (l_frag)) /2;
	bool warto = false;
	int maxind = l_frag;

	cout << "maxind " << maxind << endl;
	cout << "wzor " << wzor << endl;


	for (int i = 0; i < elem.size(); i++) // liczymy sume elementow
		total += elem[i];

	cout <<  "total " << total << endl;
	cout << "ind  " << ind << endl;
*/

//int * tab = new int[A.size()];  // dynamiczna tablica zuzytych elementow A

	//for (int i = 0; i < A.size(); i++)
		//tab[i] = 0;

	//cout << endl << "elem.size : " << elem.size() << endl;

	//cout << "tab przed " << endl;
	//for (int i = 0; i < A.size(); i++)
	//	cout << tab[i] << " ";
	//cout << endl;

	//for (int i = 0; i < elem.size(); i++)
	//{
		//cout << endl<< "i= " << i << endl;
		//cout << "A.size  " << A.size() << endl;

		/*for (int j = 0; j < A.size(); j++)
		{
			cout << " j= " <<j << endl;
			cout << "tab[j] przed:  " << tab[j] << endl;
			if (tab[j] == 0)
			{
				if (A[j] == elem[i])
				{
					tab[j] = 1;
					cout << "tab["<<j<<"] po: " << tab[j] << endl;
					if (i == elem.size() - 1)
					{
						indeks = j;
					}
					break;
				}
			}
		}*/
		//cout << endl << "i== " << i << endl;
		//cout << "elem.size  " << elem.size() << endl;	
	//}

	//
	//cout << endl << " indeks " << indeks << endl;
	/*cout <<endl << "tab po " << endl;
	for (int i = 0; i < A.size(); i++)
		cout << tab[i] << " ";
	cout << endl;
	*/



/*

			if (tab_zuzyte[i] == 0)
			{
				for (int k = i + 1; k < A.size(); k++)
				{
					if (tab_zuzyte[k] == 0)
					{
						if (total + A[i] == A[k])
						{
							warto = true;
							tab_zuzyte[i] = 1;
							int id = ind + 1;
							tab_rozw[id] = A[i];
							element = A[i];
							
							//cout << endl << "i: " << i << endl;
							cout << " A[" << i << "] : " << A[i] << endl;
							break;

						}
					}			
				}
			}*/