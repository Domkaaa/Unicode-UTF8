// xdv2unic.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cstring>
#include <string>
#include "windows.h"
#include <stdlib.h>
#include <fcntl.h>
#include <io.h>
#include <iomanip>
#include <sstream>
#include <bitset>
#include <fstream>

using namespace std;

string getSymbol(unsigned int sk);
void Pirmauzd();
void iutf(unsigned long long int code);
void skaitymas();


string getSymbol(unsigned int dsk)
{
	stringstream stream;
	stream << hex << dsk;
	return stream.str();
}
void Pirmauzd()
{
	setlocale(LC_ALL, " ");
	long long int a;
	string b;
	cout << "Iveskite int tipo desimtaini skaiciu";
	cin >> a;
	cout << "Unicode:U+";
	cout << setfill('0') << setw(4);
	cout << hex << a << endl;
	//http://www.ltg.ed.ac.uk/~richard/utf-8.cgi?input=210&mode=decimal
	b = getSymbol(a);
	//a = iutf(a);
	iutf(a);
	cout << "Char: ";
	wchar_t simb_charas = strtol(b.c_str(), NULL, 16);
	_setmode(_fileno(stdout), _O_WTEXT);
	wcout << simb_charas << endl;
	_setmode(_fileno(stdout), _O_TEXT);

}

void iutf(unsigned long long int irasymas) {
	// long long int galut;
	unsigned char ch_saugok[8];
	//bitset<8> set;
	
	unsigned long long galut;
	string baitai[5], galutb; // 4 per mazai
	if (irasymas <= 127)
	{
		//0xxxxxxxx
		//cout<<ch_saugok[0]<<" "<<ch_saugok[2];
		galut = irasymas;
	}
	else if (irasymas <= 2047)                   
	{
		//110xxxxx 10xxxxxx
		//https://www.geeksforgeeks.org/bitwise-operators-in-c-cpp/
		ch_saugok[1] = 128 | (irasymas & 63);  
		//cout << (int)ch_saugok[1] << "CH_S integeris <<" << endl;
		irasymas = (irasymas >> 6);

		ch_saugok[0] = 192 | (irasymas & 31);   
		//cout << (int)ch_saugok[0] << "CH_S integeris <<" << endl;

		for (int i = 0; i < 2; i++) {
			//https://www.geeksforgeeks.org/c-bitset-and-its-application/
			baitai[i] = bitset<8>(ch_saugok[i]).to_string();

			galutb = galutb + baitai[i];
		}

		galut = stoull(galutb, NULL, 2);             
	}
	else if (irasymas <= 65535)                                     
	{
		//https://www.rapidtables.com/convert/number/decimal-to-hex.html
		//1110xxxx 10xxxxxx 10xxxxxx
		ch_saugok[2] = 128 | (irasymas & 63); 
		irasymas = (irasymas >> 6);

		//cout << irasymas << endl;

		ch_saugok[1] = 128 | (irasymas & 63);
		irasymas = (irasymas >> 6);

		//cout << irasymas << endl;

		ch_saugok[0] = 224 | (irasymas & 15);	
		//cout << ch_saugok[0] << " cia >> "<<irasymas<<endl;
		for (int i = 0; i < 3; i++)
		{
			baitai[i] = bitset<8>(ch_saugok[i]).to_string();

			//cout << baitai[i] << "< tikrinimas < ";

			galutb = galutb + baitai[i];

			//cout << endl;
			//cout << galutb << endl;
		}
		galut = stoull(galutb, NULL, 2);
	}
	else if (irasymas <= 1114111)
	{
		//11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
		ch_saugok[3] = 128 | (irasymas & 63);
		irasymas = (irasymas >> 6);

		ch_saugok[2] = 128 | (irasymas & 63);
		irasymas = (irasymas >> 6);

		ch_saugok[1] = 128 | (irasymas & 63);
		irasymas = (irasymas >> 6);

		ch_saugok[0] = 240 | (irasymas & 7);
		for (int i = 0; i < 4; i++) {
			
			baitai[i] = bitset<8>(ch_saugok[i]).to_string();

			galutb = galutb + baitai[i];
		}
		galut = stoull(galutb, NULL, 2);
	}
	else {
		cout << "Iveskite mazesni skaiciu!" << endl;
	}
	cout << "UTF-8: ";
	cout << galut << endl;
}


/*	ifstream lent("CP437.txt");
int ind = 0;
int ind2 = 0;
int seka = 0;
int hx;
while (!lent.eof())
{
	lent >> seka[ind2] >> hx[ind2];
}


	
	ifstream fd("386intel.txt");
    ofstream fn("386intel_rez.txt");
//nfun();
char t; // tikr
char chars[5];
long long int n;
string bit;
wstring siml;
while (!fd.eof())
{
	
}*/


void skaitymas(){

	ifstream lent("CP437.txt");
	int ind = 0;
	int ind2 = 0;
	int seka[257];
	string hx[257];
	while (!lent.eof())
	{
		lent >> seka[ind2] >> hx[ind2];
		
		cout << seka[ind2] << " " << hx[ind2] << endl;
		ind2++;
	}
	lent.close();
	char sim_t;
	int sim_n;
	ifstream fin("386intel.txt");
	ofstream fo("386intel_rez.txt");
	while (!fin.eof())
	{
		fin.get(sim_t);
		sim_n = (int)sim_t;
		cout << sim_n<<" vienas "<<sim_t;
	}
	fin.close();
	fo.close();
}



int main()
{
	int menu;
	cout << "1. Failo nuskaitymas ir konevertavimas \n2. int(desimtainio) skaiciaus konvertavimas i unikoda \n3. Iseiti is programos" << endl;
	cin >> menu;
	if (menu == 1)
	{
		//Pirmauzd();
		cout << endl;
		skaitymas();
	}
	else if (menu == 2)
	{
		Pirmauzd();
	}

	else if (menu == 3)
	{
		system("exit");
	}

	return 0;
}