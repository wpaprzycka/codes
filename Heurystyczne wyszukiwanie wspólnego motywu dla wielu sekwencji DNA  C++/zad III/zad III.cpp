// zad III.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <iomanip>
#include <string>

using namespace std;

class Wierzcholek1
{
public:
	string kod;
	int seq;
	int poz;
	bool wiarygodny;
	vector <int> jakosc;

	Wierzcholek1();
	Wierzcholek1(bool xwiarygodny, string xkod, int xseq, int xpoz,  vector <int> xjakosc);
	~Wierzcholek1();
};

Wierzcholek1::Wierzcholek1(bool xwiarygodny, string xkod, int xseq, int xpoz, vector <int> xjakosc)
{
	kod = xkod;
	seq = xseq;
	poz = xpoz;
	for (int i = 0; i < xjakosc.size(); i++)
		jakosc.push_back(xjakosc[i]);
	wiarygodny = xwiarygodny;

	
}

Wierzcholek1::Wierzcholek1() {}
Wierzcholek1::~Wierzcholek1() {}

/************************************************************* GLOBALE *********************************************************/


vector< vector <char> > nad_lista;  //WEKTOR WEKTOROW SEKWENCJI
vector< vector <int> > lista;		//wektor jakosc
vector <Wierzcholek1*> wierzcholki1; //WEKTOR WSKAZNIKOW NA OBIEKTY - WIERZCHOLKI
vector <Wierzcholek1*> wierzcholki_zdelecjonowane; //WEKTOR WSKAZNIKOW NA OBIEKTY - WIERZCHOLKI zdelecjonowane


int podciag = 7;
int dlugosc_sekwencji;
int liczba_wierz;  
int l_wierz_w_sek;
int poz_wiary = 27;
int delecje = podciag / 2;
int l_sekw = 7;

void wczytaj_sekwencje(vector<vector<char>>$nad_lista);
void wczytaj_jakosc(vector<vector<int>>$lista);
void stworz_wierzcholki(vector<vector<char>>$nad_lista, vector<vector<int>>$lista);
void stworz_wierzcholki_zdelecjonowane(vector <Wierzcholek1*> $wierzcholki1, vector <Wierzcholek1*> $wierzcholki_zdelecjonowane);
void stworz_kliki_tryb_1(vector <Wierzcholek1*> $wierzcholki1, int **tab_1);
void stworz_kliki_tryb_2(vector <Wierzcholek1*> $wierzcholki_zdelecjonowane, int **tab_2);
void znajdz_motyw(int **tab, vector <Wierzcholek1*>);




/***********************************************************     main     *******************************************************************/

int main()
{
	wczytaj_sekwencje(nad_lista);

	l_wierz_w_sek = ((dlugosc_sekwencji - podciag) + 1);
	//cout << endl << "l_wierz_w_sek : " << l_wierz_w_sek << endl;

	liczba_wierz  = l_wierz_w_sek * 7;
	//cout << endl << "liczba_wierz : " << liczba_wierz << endl;
	//cout << endl << "d sek : " << dlugosc_sekwencji << endl;

	wczytaj_jakosc(lista);

	

	for (int i = 0; i < nad_lista.size(); i++)
	{
		if (nad_lista[i].size() != lista[i].size())
		{
			cout << "nie rowna ilosc nukleotydow i jakosci dla " << i << " wiersza \n";
			cout << "nad_lista[i] : " << nad_lista[i].size() << endl;
			cout << "lista[i] : " << lista[i].size() << endl;
		}
	}
	
	stworz_wierzcholki(nad_lista, lista);  // WEKTOR WIERZCHOLKI - TRYB 1 

	int **tab_1 = new int *[liczba_wierz]; // INICJACJA - MACIERZ WIERZCHOLKOW BEZ DELECJI - TRYB 1 
	for (int i = 0; i < liczba_wierz; i++)
	{
		tab_1[i] = new int[liczba_wierz];
		for (int j = 0; j < liczba_wierz; j++)
			tab_1[i][j] = 0;
	}

	stworz_kliki_tryb_1(wierzcholki1, tab_1); // WYPELNIANIE MACIERZ BEZ DELECJI - TRYB 1


	stworz_wierzcholki_zdelecjonowane(wierzcholki1, wierzcholki_zdelecjonowane); //WEKTOR WIERZCHOLKI - TRYB 2 

	int **tab_2 = new int *[liczba_wierz]; // INICJACJA - MACIERZ WIERZCHOLKOW Z DELECJAMI - TRYB 2
	for (int i = 0; i < liczba_wierz; i++)
	{
		tab_2[i] = new int[liczba_wierz];
		for (int j = 0; j < liczba_wierz; j++)
			tab_2[i][j] = 0;
	}
	

	stworz_kliki_tryb_2(wierzcholki_zdelecjonowane, tab_2); // WYPELNIANIE MACIERZ Z DELECJAMI - TRYB 2 

	//cout << endl << endl << "tryb 1: \n";
	//znajdz_motyw(tab_1, wierzcholki1);
	
	cout << endl << endl << "tryb 2: \n";
	znajdz_motyw(tab_2, wierzcholki_zdelecjonowane);
	
	for (int i = 0; i < liczba_wierz; i++)
		delete[] tab_1[i];

	delete[] tab_1;


	for (int i = 0; i < liczba_wierz; i++)
		delete[] tab_2[i];

	delete[] tab_2;
	
}

/********************************************************   WCZYTAJ sekwencje **********************************************************/

void wczytaj_sekwencje(vector<vector<char>>$nad_lista)
{
	fstream plik;
	plik.open("plik_fasta.txt", ios::in);

	string wiersz;
	int iter = 0;

	if (plik.is_open())
	{
		for(int w=0; w<(l_sekw*2); w++)
		{
			getline(plik, wiersz);

			if (wiersz[0] != '>')
			{
				/*cout << "wiersz : ";
				for (int i = 0; i < wiersz.length(); i++)
					cout << wiersz[i] << " ";
				cout << endl;*/

				dlugosc_sekwencji = wiersz.length();
				
				nad_lista.push_back(vector<char>());

				for (int i = 0; i < dlugosc_sekwencji; i++)
				{
					nad_lista[iter].push_back(wiersz[i]);
				}
				iter++;
			}	
		}
	}
	else
		cout << "ej" << endl;

	plik.close();

	//cout << "sekwencje \n\n";
/*
	for (int i = 0; i < nad_lista.size(); i++)
	{
		for (int j = 0; j < nad_lista[i].size(); j++)
		{
			cout << nad_lista[i][j];
		}
		cout << endl;
	}
	cout << endl;
	*/
}

/*****************************************************************  wczytaj jakosc  ******************************************/

void wczytaj_jakosc(vector<vector<int>>$lista)
{
	fstream plik1;
	plik1.open("plik_qual.txt", ios::in);

	string wiersz;
	int iter = 0;
	int parametr;

	if (plik1.is_open())
	{
		for (int w = 0; w < 7; w++)
		{	
			//cout << endl << iter << endl;
			//std::streampos iOdczytanaPozycja = plik1.tellg();
			//std::cout << "Aktualna pozycja odczytu danych z  pliku: " << iOdczytanaPozycja << std::endl;
			getline(plik1, wiersz);
			//cout << wiersz << endl;

			lista.push_back(vector<int>());
		
			for (int i = 0; i < dlugosc_sekwencji; i++)
			{
				plik1 >> parametr;
				//cout << parametr << endl;
				lista[iter].push_back(parametr);
			}
			plik1.seekg(+2, std::ios::cur);
			iter++;
		}
	}
	else
		cout << "ej" << endl;

	plik1.close();

	//cout << "jakosci \n\n";
	/*
	for (int i = 0; i < lista.size(); i++)
	{
		for (int j = 0; j < lista[i].size(); j++)
		{
			cout << lista[i][j]<< " ";
		}
		cout << endl;
	}
	cout << endl;
	*/
}



/*****************************************************************  STWORZ WIERZCHOLKI  ******************************************/

void stworz_wierzcholki(vector<vector<char>>$nad_lista, vector<vector<int>>$lista)
{	
	int jak_daleko = podciag - 1;
	int sekw;
	int pozycja;
	string cos(podciag, 'X');

	for (int i = 0; i < nad_lista.size(); i++)
	{
		for (int j = 0; j < (nad_lista[i].size() - jak_daleko); j++)
		{
			int z = j; 
			for (int b = 0; b < podciag; b++)
			{
				cos[b] = nad_lista[i][z];
				z++;
			}

			sekw = i;
			pozycja = j;

			vector <int> qual;
			for(int k=0; k<podciag; k++)
				qual.push_back(lista[i][j+k]);
			
		
			//cout << cos << endl << sekw << endl;// << pozycja << endl;
			Wierzcholek1 *wierz1 = new Wierzcholek1(true, cos, sekw, pozycja, qual);
			wierzcholki1.push_back(wierz1);

			qual.clear();
		}
	}

	//cout << "wierzcholki i jakosci\n\n"; 
	/*
	for (int i = 0; i < wierzcholki1.size(); i++)
	{
		cout << i << ":\t" << wierzcholki1[i]->kod;
		for(int j=0; j < wierzcholki1[i]->jakosc.size(); j++)
			cout<< " " << wierzcholki1[i]->jakosc[j];
		cout << endl;

	}
	
	
		cout << endl;
	
	cout << endl;
		*/
}
/*****************************************************************  STWORZ wierzcholki zdelecjonowane ******************************************/


void stworz_wierzcholki_zdelecjonowane(vector <Wierzcholek1*> $wierzcholki1, vector <Wierzcholek1*> $wierzcholki_zdelecjonowane)
{
	for (int i = 0; i < wierzcholki1.size(); i++)
	{	
		int licznik = 0;
		string cos = wierzcholki1[i]->kod;
		int sekw = wierzcholki1[i]->seq;
		int pozycja = wierzcholki1[i]->poz;
		vector <int> qual;

		for (int k = 0; k < wierzcholki1[i]->jakosc.size(); k++)
			qual.push_back(wierzcholki1[i]->jakosc[k]);


		Wierzcholek1 *wierz1 = new Wierzcholek1(true, cos, sekw, pozycja, qual);
		wierzcholki_zdelecjonowane.push_back(wierz1);
		
		for (int j = 0; j < wierzcholki1[i]->jakosc.size(); j++)
		{
			if (wierzcholki1[i]->jakosc[j] < poz_wiary)
			{
				wierzcholki_zdelecjonowane[i]->kod[j] = 'X';
				licznik++;
			}
		}

		if (licznik > delecje)
			wierzcholki_zdelecjonowane[i]->wiarygodny = false;
		
	}
//	cout << "wierzcholki zdelecjonowane \n\n";
	/*
	for (int i = 0; i < wierzcholki_zdelecjonowane.size(); i++)
	{
		cout << i << ":\t" << wierzcholki_zdelecjonowane[i]->kod;
		for (int j = 0; j < wierzcholki_zdelecjonowane[i]->jakosc.size(); j++)
		{
			cout << " " << wierzcholki_zdelecjonowane[i]->jakosc[j];	
		}
		cout << "   " << wierzcholki_zdelecjonowane[i]->wiarygodny;
		cout << endl;

	}
	
	cout << endl;

	cout << endl;*/
}


/*****************************************************************  STWORZ kliki I ******************************************/

void stworz_kliki_tryb_1(vector <Wierzcholek1*> $wierzcholki1, int **tab_1)
{
	
	for (int i = 0; i < wierzcholki1.size(); i++)
	{
		for (int j = i + 1; j < wierzcholki1.size(); j++)
		{
			if (wierzcholki1[i]->seq != wierzcholki1[j]->seq)
			{
				if (wierzcholki1[i]->kod == wierzcholki1[j]->kod)
				{
					tab_1[i][j] = 1;
					tab_1[j][i] = 1;
				}
			}
		}
	}

	//cout << "macierz klik I \n\n";
	/*
	for (int i = 0; i < liczba_wierz; i++)
	{
		for (int j = 0; j < liczba_wierz; j++)
		{
			cout << tab_1[i][j]<< " ";
		}
		cout << endl;
	}
	cout << endl;
	*/
}

/*****************************************************************  STWORZ kliki II ******************************************/


void stworz_kliki_tryb_2(vector <Wierzcholek1*> $wierzcholki_zdelecjonowane, int **tab_2)
{
	
	int *tabka = new int[podciag];


	for (int i = 0; i < wierzcholki_zdelecjonowane.size(); i++)
	{
		for (int j = i + 1; j < wierzcholki_zdelecjonowane.size(); j++)
		{
			if (wierzcholki_zdelecjonowane[i]->seq != wierzcholki_zdelecjonowane[j]->seq)
			{
				if (wierzcholki_zdelecjonowane[i]->kod == wierzcholki_zdelecjonowane[j]->kod)
				{
					tab_2[i][j] = 1;
					tab_2[j][i] = 1;
				}
			}
		}
	}


	for (int i = 0; i < wierzcholki_zdelecjonowane.size(); i++)
	{
		
		for (int z = 0; z < podciag; z++)
		{
			tabka[z] = 0;
		}

		if (wierzcholki_zdelecjonowane[i]->wiarygodny == true)
		{
			for (int j = i + 1; j < wierzcholki_zdelecjonowane.size(); j++)
			{
				int total = 0;
				if (wierzcholki_zdelecjonowane[j]->wiarygodny == true)
				{
					if (wierzcholki_zdelecjonowane[i]->seq != wierzcholki_zdelecjonowane[j]->seq)
					{
						if (wierzcholki_zdelecjonowane[i]->kod == wierzcholki_zdelecjonowane[j]->kod)
						{
							tab_2[i][j] = 1;
							tab_2[j][i] = 1;
						}
						else
						{
							for (int k = 0; k < podciag; k++)
							{
								if (wierzcholki_zdelecjonowane[i]->kod[k] == wierzcholki_zdelecjonowane[j]->kod[k])
									tabka[k] = 1;
								else if (wierzcholki_zdelecjonowane[i]->kod[k] == 'X')
									tabka[k] = 1;
								else if (wierzcholki_zdelecjonowane[j]->kod[k] == 'X')
									tabka[k] = 1;
								else
									tabka[k] = 0;
							}

							for (int c = 0; c < podciag; c++)
								total += tabka[c];

							if (total == podciag)
							{
								tab_2[i][j] = 1;
								tab_2[j][i] = 1;
							}
						}						
					}
				}
			}
		}
	}
	/*
	cout << "macierz klik II \n\n";
	
	for (int i = 0; i < liczba_wierz; i++)
	{
		for (int j = 0; j < liczba_wierz; j++)
		{
			cout << tab_2[i][j] << " ";
		}
		cout << endl;
	}*/
	
	delete[]  tabka;
}




/***************************************************************** znajdz motyw ******************************************/


void znajdz_motyw(int **tab, vector <Wierzcholek1*> $wierzcholki)
{
	int I=0;
	vector<int> potencjal;
	vector<int> nwm_co; // indeksy j+1
	vector<int> motyw;
	vector <int> final_motyw;
	int dlug_motywu = 0;
	int final_dlug_mot = 0;
	int licz_sek = 0;

	//cout << "w_size() : " << $wierzcholki.size() << endl;
	
	for (int i = 0; i < $wierzcholki.size();)								// Przechodzimy po tab w dol - i 
	{	
		//cout << endl << i << endl;
		licz_sek++;

			if (potencjal.empty())											// <tworzymy potencjal>
			{

				//cout << "nowy element  " ;
				//cout <<"i: "<< i <<endl;

				for (int j = 0; j < $wierzcholki.size(); j++)				// Przechodzimy po tab w prawo - j 
				{
					//cout << "j:" << j << "  ";
					if (tab[i][j] == 1)
					{
						potencjal.push_back(j);
						//cout << "j:" << j << "  ";
					}
				}

				/*
				cout << endl;
				for (int c = 0; c < potencjal.size(); c++)
					cout << "pot[c] : " << potencjal[c] << endl;*/
				
			}

			i++;
			
			if (potencjal.size() > 2)
			{
				/*
				cout << endl << "pot["<<wierzcholki1[i]->seq<<"]: ";
				for (int c = 0; c < potencjal.size(); c++)
					cout << potencjal[c] << " ";
					*/

				dlug_motywu++;

				//cout <<endl<< "dlugosc motywu: " << dlug_motywu << endl;
				//cout << "final_dlug_mot" <<  final_dlug_mot << endl;
								
				motyw.assign(potencjal.begin(), potencjal.end());			//tworzymy motyw

				//cout << endl << i << endl;
				//cout << liczba_wierz << endl;
				if (i == liczba_wierz-1) // DLA OSTATNIEGO WIERZCHOLKA NIE MOZNA SPRAWDZAC KOLEJNEJ KOLUMNY I WIERSZA 
				{
					if (final_motyw.empty() || dlug_motywu > final_dlug_mot)
					{
						final_motyw.assign(motyw.begin(), motyw.end());
						final_dlug_mot = dlug_motywu;
						//cout << endl << "final dlugosc motywu : " << final_dlug_mot << endl;
						I = i;
						dlug_motywu = 0;
						potencjal.clear();
						nwm_co.clear();
						licz_sek = 0;
						break;
					}
					else
						break;
				}

				/*
				cout << endl;
				for (int c = 0; c < motyw.size(); c++)
					cout << "mot[c] : " << motyw[c] << endl;
				*/

				for (int w = 0; w < potencjal.size(); w++)					//tworzymy nwm_co -> indkesy j+1
				{
					int temp = potencjal[w];
					temp++;
					nwm_co.push_back(temp); // wektor nwm_co = wartosci +1			
				}

				potencjal.clear();											//czyscimy potencjal
				/*
				cout << endl << "nwm[c]: ";
				for (int c = 0; c < nwm_co.size(); c++)
					cout << nwm_co[c] << " ";*/
				

				//cout << endl << "i = " <<i <<  endl;
				for (int k = 0; k < nwm_co.size(); k++)						//tworzymy nowy potencjal
				{
					int cur = nwm_co[k];
					if (tab[i][cur] == 1)
					{
						potencjal.push_back(cur);

					}
				}
				nwm_co.clear();												//czyscimy nwm_co
				
				/*
				cout << endl << "pot["<<wierzcholki1[i]->seq << "]: ";
				for (int c = 0; c < potencjal.size(); c++)
					cout << potencjal[c] << " ";
				
				cout << endl << "mot[" <<wierzcholki1[i]->seq<<"]:";
				for (int c = 0; c < motyw.size(); c++)
					cout << motyw[c] << " ";
				*/

				if (potencjal.size() < 3 || licz_sek == l_wierz_w_sek)
				{		
					if (final_motyw.empty() || dlug_motywu > final_dlug_mot)
					{
						final_motyw.assign(motyw.begin(), motyw.end());
						final_dlug_mot = dlug_motywu;
						//cout << endl << "final dlugosc motywu : " << final_dlug_mot << endl;
						I = i;

						//cout << " I:  " << I;
						/*
						cout << endl << "final_motyw[c]:";
						for (int c = 0; c < final_motyw.size(); c++)
							cout << final_motyw[c] << " ";*/
					}
					

					dlug_motywu = 0;
					potencjal.clear();
					nwm_co.clear();
					licz_sek = 0;
				}

			}
			//cout << endl;

			if (potencjal.size() < 3 && potencjal.size() != 0)
			{
				potencjal.clear();
			}
	
	}
	/*
	cout << endl << "wynik: " << endl;
	for (int i = 0; i < motyw.size(); i++)
		cout << motyw[i] << " ";

	cout << endl << "final dlugosc motywu : " << final_dlug_mot << endl;
	cout << "I: " << I;
	cout << endl << endl;
	*/




	// ****************************************** wypisanie winiku  **************************************************** //


	if (final_motyw.empty())
		cout << "nie znaleziono motywu\n";
	else
	{
		int j_pocz = 0;
		int i_pocz = 0;
		string kod_1;
		int seq_1 = 0;
		int poz_1 = 0;
		int poz_2 = 0;

		//cout << endl << " I " << I << endl;

		i_pocz = I - final_dlug_mot;

		//cout << endl << "final dlugosc motywu : " << final_dlug_mot << endl;
		//cout << " i_pocz : " << i_pocz << endl;

		/*cout << endl << "final_motyw[c]:";
		for (int c = 0; c < final_motyw.size(); c++)
			cout << final_motyw[c] << " ";
		cout << endl;*/

		for (int m = 0; m < final_motyw.size(); m++) // przechodzi przez wektor
		{

			j_pocz = final_motyw[m] - final_dlug_mot + 1;
			//cout <<"j_pocz: " << j_pocz << endl;

			for (int n = 0; n < final_dlug_mot; n++)
			{
				if (n == 0)
				{
					kod_1 = $wierzcholki[j_pocz]->kod;
					//cout << "kod_1 : " << kod_1 << endl;

					seq_1 = $wierzcholki[j_pocz]->seq;
					//cout << "seq_1 : " << seq_1 << endl;

					poz_1 = $wierzcholki[j_pocz]->poz;
					//cout << "poz_1 : " << poz_1 << endl;

					poz_2 = ($wierzcholki[j_pocz]->poz) + (podciag - 1);
				}
				else
				{
					j_pocz++;
					kod_1 += $wierzcholki[j_pocz]->kod[podciag - 1];
					//cout << "kod_2 : " << kod_1 << endl;

					poz_2 = ($wierzcholki[j_pocz]->poz) + (podciag - 1);
				}
			}
			cout << "znaleziono motyw " << kod_1 << " w sekwencji " << seq_1 + 1 << " od pozycji " << poz_1 << " do " << poz_2 << endl;

		}



		for (int n = 0; n < final_dlug_mot; n++)
		{
			if (n == 0)
			{
				kod_1 = $wierzcholki[i_pocz]->kod;
				//cout << "kod_1 : " << kod_1 << endl;

				seq_1 = $wierzcholki[i_pocz]->seq;
				//cout << "seq_1 : " << seq_1 << endl;

				poz_1 = $wierzcholki[i_pocz]->poz;
				//cout << "poz_1 : " << poz_1 << endl;

				poz_2 = ($wierzcholki[j_pocz]->poz) + (podciag - 1);
			}
			else
			{
				i_pocz++;
				kod_1 += $wierzcholki[i_pocz]->kod[podciag - 1];
				//cout << "kod_2 : " << kod_1 << endl;

				poz_2 = $wierzcholki[i_pocz]->poz + (podciag - 1);
			}
		}
		cout << "znaleziono motyw " << kod_1 << " w sekwencji " << seq_1 + 1 << " od pozycji " << poz_1 << " do " << poz_2 << endl;
	}


	

	
}

/*
for (int k = 0; k < podciag; k++)
{
	if (wierzcholki_zdelecjonowane[i]->kod[k] == 'X')
	{
		jest_X = true;
		gdzie = k;
	}
	else if (wierzcholki_zdelecjonowane[j]->kod[k] == 'X')
	{
		jest_X = true;
		gdzie = k;
	}
}

if (jest_X)
{

	for (int l = 0; l < podciag; l++)
	{
		if (l != gdzie)
		{
			if (wierzcholki_zdelecjonowane[i]->kod[l] == wierzcholki_zdelecjonowane[j]->kod[l])
				tabka[l] = 1;
		}
	}

	tabka[gdzie] = 0;

	for (int c = 0; c < podciag; c++)
		total += tabka[c];

	if (total == podciag - 1)
	{
		tab[i][j] = 1;
		tab[j][i] = 1;
	}

}*/


/*
void stworz_kliki(vector <Wierzcholek1*> $wierzcholki1)
{
	int **tab = new int *[liczba_wierz];

	for (int i = 0; i < liczba_wierz; i++)
	{
		tab[i] = new int[liczba_wierz];
		for (int j = 0; j < liczba_wierz; j++)
			tab[i][j] = 0;
	}

	vector<int> juz_byly;
	int it = 0;

	for (int i = 0; i < wierzcholki1.size(); i++)
	{
		//cout << "i : " << i << endl;
		vector<int> sprawdzone;
		bool nie_ma = true;
		it++;
		//cout << "it : " << it << endl;

		for (int z = 0; z < juz_byly.size(); z++)
		{
			//cout << "sprawdzone[z] : " << sprawdzone[z] << endl;
			if (i == juz_byly[z])
			{
				//cout << "i = sprawdzone[z]  = " << sprawdzone[z] << endl;
				nie_ma = false;
			}
		}

		if(nie_ma)
		{
			for (int j = i + 1; j < wierzcholki1.size(); j++)
			{
				if (wierzcholki1[i]->kod == wierzcholki1[j]->kod)
				{
					tab[i][j] = it;
					tab[j][i] = it;
					sprawdzone.push_back(j);
					juz_byly.push_back(j);
				}
			}
			for (int s = 0; s < sprawdzone.size(); s++)
			{
				//cout << "sprawdzone[s] : " << sprawdzone[s] << endl;
				for (int s2 = s + 1; s2 < sprawdzone.size(); s2++)
				{
					//cout << "sprawdzone[s2] : " << sprawdzone[s2] << endl;
					//cout << "tab[sprawdzone[s]]: " << tab[sprawdzone[s]]<< endl;

					tab[sprawdzone[s]][sprawdzone[s2]] = it;
					tab[sprawdzone[s2]][sprawdzone[s]] = it;
				}
			}
			//cout << endl << endl;
		}
	}


	for (int i = 0; i < liczba_wierz; i++)
	{
		for (int j = 0; j < liczba_wierz; j++)
		{
			cout << tab[i][j];
		}
		cout << endl;
	}
	for (int i = 0; i < liczba_wierz; i++)
		delete[] tab[i];

	delete[] * tab;
}


*/







// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln
