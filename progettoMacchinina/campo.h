#pragma once
#include <iostream>
#include <time.h>
using namespace std;

class campo {
protected:
	struct coordinateMaccina {
		int riga = 0;
		int colonna = 0;
	};
	coordinateMaccina macchina;
	int righe, colonne;
	int punti;
	char spazio[40][40];

public:
	campo();
	campo(int a, int b, int p);
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

};
