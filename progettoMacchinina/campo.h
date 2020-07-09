#pragma once
#include <iostream>
#include <time.h>
#include <conio.h>
#include "utili.h"

using namespace std;

class campo {
protected:
	struct coordinateMacchina {
		int riga = 0;
		int colonna = 0;
	};
	coordinateMacchina macchina;
	int righe, colonne;
	int punti;
	char spazio[RIGHECAMP_TOT][COLONNE_CAMPO];
	int livello;
	bool immunità;
	int righeDiff;
	int flagMacchina;
	int posMacchinaCattiva;
	int benzina;
public:

	//Variabile utile al main
	bool perso;

	//METODI
	campo(int a, int b, int p, int l, bool im);
	void  stampa();
	void  sigla();
	void  regolamento();
	void  sconfitta();
	void  colpito(); 
	void  aggiungiOstacoli();
	void  scriviMacchina();
	void  scriviLevel();
	char* memOstacoli(char vett_ostacoli[]);
	void  muoviMacchina(char l);
	void  cosaMiHaColpito(bool *preso , int, int);
};
