#pragma once
#include <iostream>
#include <time.h>
#include <conio.h>
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
	char spazio[40][40];
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
	void stampa();
	void sigla();
	void regolamento();
	void sconfitta();
	void colpito();//ancora da impplement
	void aggiungiOstacoli();
	void spostaO();
	void scriviMacchina();
	void scriviLevel();
	void muoviSinistra();
	void muoviDestra();
	void muoviMacchina(char);
	void cosaMiHaColpito(bool, int, int);
};
