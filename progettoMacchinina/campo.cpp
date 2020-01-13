#include "campo.h"
#include <cstdlib>

campo::campo(int a, int b, int p, int l, bool im) {

	campo::righe = a;//a sono le righe
	campo::colonne = b;//b sono le colonne 
	campo::punti = p;
	campo::immunit� = im;
	campo::livello = l;

	int i = 0, j = 0;

	for (i = 0; i < campo::righe; i++) {

		for (j = 0; j < campo::colonne; j++) {

			if (j == 0 ||/* j == campo::colonne - 1 ||*/ i == 0 || i == campo::righe - 1 || j == campo::colonne - 14) {
				if (i == 0 || i == campo::righe - 1)
					campo::spazio[i][j] = '_';
				else
					campo::spazio[i][j] = '|';
			}
			else if (j == 1 || j == campo::colonne - 15)
				campo::spazio[i][j] = '#';
			else
				campo::spazio[i][j] = ' ';
		}


	}

	campo::scriviLevel();
	//campo::spazio[14][33] = per far stampare dei punti secondo me va usato un carattere speciale 
	//crea la pedina

	//inizializza tutti i valori relativi agli indirizzi della maccina
	campo::macchina.riga = campo::righe - 3; // SOLLEVO DI 3 LA MACCHININA 
	do
	{
		campo::macchina.colonna = 2 + rand() % 24;//prende un numero casuale tra 2 e 37 e lo mette nel numrto della colonna

	} while (campo::spazio[i][j] == 'C');//non � mai uguale a B quindi fa una mandata e esce, in poche parole cervo dove mettere la "V"

	campo::scriviMacchina();



};

void campo::stampa() {
	int i, j;
	for (i = 0; i < campo::righe; i++) {
		for (j = 0; j < campo::colonne; j++) {

			if (campo::spazio[i][j] == '&' || campo::spazio[i][j] == '+') //bisogna aggiungere
			{	
				if (campo::spazio[i][j] == '&')
					cout << campo::punti; // & � il carattere speciale che sta ad identificare i punti, cos� da non dover sempre passare una variabile intera
				else if (campo::spazio[i][j] == '+')
					cout << campo::livello;
			}
			else
				cout << campo::spazio[i][j] << " ";
		}
		cout << "\n";
	}
	for (i = campo::righe - 1; i >= 1; i--)
	{
		for (j = campo::colonne - 15;  j >= 1; j--)
		{
			// aggiungere controllo collisioni 
			if (campo::spazio[i][j] == 'O' || campo::spazio[i][j] == 'E' || campo::spazio[i][j] == 'S' || campo::spazio[i][j] == 'B' || campo::spazio[i][j] == 'V')
			{
				
				if (i <= campo::macchina.riga) // controllo che a livello della macchina cancellano le o deve controllare collisioni
					campo::spazio[i + 1][j] = campo::spazio[i][j]; // da migliorare perch� cancella anche la macchina 

				campo::spazio[i][j] = ' ';		
			}

		}
	}

}



void campo::sigla() {
	cout << " -------------------------------\n";
	cout << "| BENVENUTO NEL GIOCO CAR SPEED |\n";
	cout << " -------------------------------\n\n";
}


void campo::regolamento() {
	cout << "*******************\n";
	cout << "* REGOLE DI GIOCO *\n";
	cout << "*******************\n\n";
	cout << "*       Il gioco consiste nel far muovere l'auto (indentificata da: V )\n";
	cout << "*       e farla arrivare alla fine del percorso (ovvero dopo 100 passi)\n";
	cout << "*    evitanto gli ostacoli presenti! Se invece l'auto colpisce un ostacolo\n";
	cout << "*                            finisce la partita!\n\n";
	cout << "                            *************\n";
	cout << "                            * MOVIMENTI *\n";
	cout << "                            *************\n\n";
	cout << "E' possibile muovere l'auto solo nelle direzioni destra -> e sinistra <-: \n\n";
	cout << "A per far muovere l'auto a sinistra\n\n";
	cout << "D per far muovere l'auto a destra\n\n";
	cout << "W per far muovere l'auto in avanti!\n\n";

}


void campo::colpito() { // ci sar� una schermata quando l'auto viene colpita da qualcosa 

	bool preso = false;

	switch (campo::spazio[campo::macchina.riga - 1][campo::macchina.colonna]) {
	
	case('*'):
		break;
	case('O'):
	case('E'):
	case('V'):
		if (!immunit�) {
			campo::punti = campo::punti - 10;
			preso = true;
		}
		else
			campo::immunit� = false;
		break;
	case('S'):
		campo::immunit� = true;
		break;
	case('B'):
		//vorrei aumentare la benzina ma prima chiedo a Bretta
		cout << "PIU' BENZINA!!";
		break;
	default:
		break;
	}

	switch (campo::spazio[campo::macchina.riga][campo::macchina.colonna + 1]) {

	case('*'):
		break;
	case('O'):
	case('E'):
	case('V'):
		if (!immunit�) {
			campo::punti = campo::punti - 10;
			preso = true;
		}
		else
			campo::immunit� = false;
		break;
	case('S'):
		campo::immunit� = true;
		break;
	case('B'):
		//vorrei aumentare la benzina ma prima chiedo a Bretta
		cout << "PIU' BENZINA!!";
		break;
	default:
		break;
	}

	switch (campo::spazio[campo::macchina.riga][campo::macchina.colonna - 1]) {

	case('*'):
		break;
	case('O'):
	case('E'):
	case('V'):
		if (!immunit�) {
			campo::punti = campo::punti - 10;
			preso = true;
		}
		else
			campo::immunit� = false;
		break;
	case('S'):
		campo::immunit� = true;
		break;
	case('B'):
		//vorrei aumentare la benzina ma prima chiedo a Bretta
		cout << "PIU' BENZINA!!";
		break;
	default:
		break;
	}
	
	if (!preso) {
		campo::punti = campo::punti + 1;
		if (campo::punti%100 == 0) {
			campo::livello = campo::livello + 1;
		}
	}
}


// Lettere utilizzate = O E S T V

void campo::aggiungiOstacoli() { 
	int j;// decide dove piazzare l'ostacolo
	int b;// decide che far stampare
	char ost; 
	b = 1 + rand() % 5;
	switch (b) {
	case 1:
		ost = 'O';
		break;
	case 2:
		ost = 'E';
		break;
	case 3:
		ost = 'S';
		break;
	case 4:
		ost = 'B';
		break;
	case 5:
		ost = 'V';
		break;	
	}

	j = 2 + rand() % 23;
	campo::spazio[1][j] = ost;

}
void campo::scriviMacchina()
{
	colpito();
	campo::spazio[campo::macchina.riga + 1][campo::macchina.colonna] = '*';
	campo::spazio[campo::macchina.riga - 1][campo::macchina.colonna] = '*';
	campo::spazio[campo::macchina.riga][campo::macchina.colonna + 1] = '*';
	campo::spazio[campo::macchina.riga][campo::macchina.colonna - 1] = '*';
	campo::spazio[campo::macchina.riga][campo::macchina.colonna] = 'A';
}
void campo::scriviLevel() {

	campo::spazio[14][27] = 'P';
	campo::spazio[14][28] = 'U';
	campo::spazio[14][29] = 'N';
	campo::spazio[14][30] = 'T';
	campo::spazio[14][31] = 'I';
	campo::spazio[14][32] = '=';
	campo::spazio[14][33] = '&';

	campo::spazio[16][27] = 'L';
	campo::spazio[16][28] = 'E';
	campo::spazio[16][29] = 'V';
	campo::spazio[16][30] = 'E';
	campo::spazio[16][31] = 'L';
	campo::spazio[16][32] = '=';
	campo::spazio[16][33] = '+';
}
void campo::muoviMacchina(char l) {
	if (l == 'a' || l == 'A' || l == 'd' || l == 'D' || l == 'w' || l == 'W') {
		
		switch (l) {
		case ('a'):
		case('A'):
			if (campo::spazio[campo::macchina.riga][campo::macchina.colonna - 2] != '#')
			{

				campo::spazio[campo::macchina.riga - 1][campo::macchina.colonna] = ' ';
				campo::spazio[campo::macchina.riga + 1][campo::macchina.colonna] = ' ';
				campo::spazio[campo::macchina.riga][campo::macchina.colonna + 1] = ' ';

				campo::macchina.colonna = campo::macchina.colonna - 1;

				campo::scriviMacchina();
			}

			else
				cout << "non puoi andare di qua";//implementare una scritta pi� efficace
			break;

		case('d'):
		case('D'): // qua vanno aggiunti i controlli di collisione
			if (campo::spazio[campo::macchina.riga][campo::macchina.colonna + 2] != '#') {

				campo::spazio[campo::macchina.riga - 1][campo::macchina.colonna] = ' ';
				campo::spazio[campo::macchina.riga + 1][campo::macchina.colonna] = ' ';
				campo::spazio[campo::macchina.riga][campo::macchina.colonna - 1] = ' ';

				campo::macchina.colonna = campo::macchina.colonna + 1;

				campo::scriviMacchina();
			}
			else
				cout << "non puoi andare di qua";//implementare una scritta pi� efficace
			break;

		case('w'):
		case('W'):
			scriviMacchina();
			break;
		}
	}
	else {
		cout << "Non puoi premere questo tasto";
		campo::muoviMacchina(_getch());
	}
}

