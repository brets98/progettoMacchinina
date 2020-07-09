#include "campo.h"
#include <cstdlib>

campo::campo(int a, int b, int p, int l, bool im) {

	campo::righe = a;//a sono le righe
	campo::colonne = b;//b sono le colonne 
	campo::punti = p;
	campo::immunità = im;
	campo::livello = l;
	campo::righeDiff = 0;
	campo::flagMacchina = 0;
	campo::posMacchinaCattiva = 0;
	campo::perso = false;
	campo::benzina = 101;
	int i = 0, j = 0;

	for (i = 0; i < campo::righe; i++) {

		for (j = 0; j < campo::colonne; j++) {

			if (j == 0 || i == 0 || i == campo::righe - 1 || j == campo::colonne - 14) {
				if (i == 0 || i == campo::righe - 1) {
					if (j < campo::righe - 3)
						campo::spazio[i][j] = '_';
					else
						campo::spazio[i][j] = ' ';
                }
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

	} while (campo::spazio[i][j] == 'C');//non é mai uguale a B quindi fa una mandata e esce, in poche parole cervo dove mettere la "V"

	campo::scriviMacchina();
};

void campo::stampa() {
	int k;

	if (campo::benzina >= 10 && campo::benzina > 0) {
		k = (campo::benzina / 10);
	}
	else k = 1;

	int i, j, l;

	for (i = 0; i < campo::righe; i++) {
		for (j = 0; j < campo::colonne; j++) {

			if (campo::spazio[i][j] == '&' || campo::spazio[i][j] == '+' || campo::spazio[i][j] == '$' || campo::spazio[i][j] == '%') // il $ sta per benzina
			{	
				if (campo::spazio[i][j] == '&')
					cout << campo::punti; // & é il carattere speciale che sta ad identificare i punti, cosí da non dover sempre passare una variabile intera
				else if (campo::spazio[i][j] == '+')
					cout << campo::livello;
				else if (campo::spazio[i][j] == '$'){

					cout << "Benzina: " << campo::benzina;

					for (l = 0; l < 10; l++) {
					
						if (k > 0) {
							campo::spazio[i+1][l + j] = QUAD_PIENO;
							k--;
						}
						else {
							campo::spazio[i+1][l + j] = QUAD_VUOTO;
						}
					}
				}
				else if (campo::immunità) {
					cout << "|| SEI IMMUNE ||";
				}	
			}
			else
				cout << campo::spazio[i][j] << ' ';
		}
		cout << "\n";
	}
	for (i = campo::righe - 1; i >= 1; i--)
	{
		for (j = campo::colonne - 15;  j >= 1; j--)
		{
			if (campo::spazio[i][j] == 'O' || campo::spazio[i][j] == 'E' || campo::spazio[i][j] == 'S' || campo::spazio[i][j] == 'B' || campo::spazio[i][j] == '?' || campo::spazio[i][j] == 'V')
			{
				
				if (i <= campo::macchina.riga) // controllo che a livello della macchina cancellano le o deve controllare collisioni
					campo::spazio[i + 1][j] = campo::spazio[i][j]; // da migliorare perché cancella anche la macchina 


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
	cout << "E' possibile muovere l'auto solo nelle direzioni destra -> e sinistra <- e avanti: \n\n";
	cout << "A per far muovere l'auto a sinistra\n\n";
	cout << "D per far muovere l'auto a destra\n\n";
	cout << "W per far muovere l'auto in avanti!\n\n";

}
void campo::sconfitta() {

	system("cls");
	campo::perso = true;

	cout << " ------------- \n";
	cout << "|  HAI PERSO  |\n";
	cout << " ------------- \n\n";
	campo::punti = 0;
	campo::livello = 0;
	campo::benzina = 100;
	system("pause");
}
void campo::cosaMiHaColpito(bool* preso, int riga, int colonna) {

	switch (campo::spazio[riga][colonna]) {

		case('O'):

			if (!immunità) {

				campo::punti = campo::punti - (1 * campo::livello);
				*preso = true;
				if (campo::punti <= 0)
					campo::sconfitta();
				cout << "HAI PRESO UNA BUCA, -" << 1 * campo::livello << " PUNTI";
				system("pause");


			}
			else
				campo::immunità = false;
			break;

		case('E'): //OSTACOLI COMUNI

			if (!immunità) {

				campo::punti = campo::punti - (10 * campo::livello);
				*preso = true;
				if (campo::punti <= 0)
					campo::sconfitta();
				cout << "HAI COLPITO UN OSTACOLO, -" << 10 * campo::livello << " PUNTI" << endl;
				system("pause");

			}
			else
				campo::immunità = false;
			break;

			case('?'): //MACCHINA NEMICA

			if (!immunità) {
				campo::punti = campo::punti - 10;
				*preso = true;
				if (campo::punti <= 0)
					campo::sconfitta();
				cout << "HAI COLPITO UNA MACCHINA NEMICA, -10 PUNTI" << endl;
				system("pause");

			}
			else
				campo::immunità = false;

			//Cancello l'ostacolo macchina
			if (campo::spazio[riga][colonna - 1] == 'V') { //colpito da macchina tutta a sinistra

				campo::spazio[riga][colonna - 1] = ' ';
				campo::spazio[riga][colonna - 2] = ' ';
				campo::spazio[riga - 1][colonna - 1] = ' ';
				campo::spazio[riga + 1][colonna - 1] = ' ';

			}
			else if (campo::spazio[riga][colonna + 1] == 'V') { //colpito da macchina tutta a destra 
				
				campo::spazio[riga][colonna + 1] = ' ';
				campo::spazio[riga][colonna + 2] = ' ';
				campo::spazio[riga + 1][colonna + 1] = ' ';
				campo::spazio[riga - 1][colonna + 1] = ' ';


			}
			else { //colpito da macchina parzialmente a destra o a sinistra o sopra
				campo::spazio[riga - 1][colonna] = ' ';
				campo::spazio[riga - 2][colonna] = ' ';

			}

			if (campo::spazio[riga - 1][colonna + 1] == '*') { //colpito da sinistra
				campo::spazio[riga - 1][colonna - 1] = ' ';
				campo::spazio[riga - 1][colonna + 1] = '*';

			}
			else if (campo::spazio[riga - 1][colonna - 1] == '*') { //colpito da destra
				campo::spazio[riga - 1][colonna + 1] = ' ';
				campo::spazio[riga - 1][colonna - 1] = '*';

			}
			else { //colpito da sopra
				campo::spazio[riga - 1][colonna - 1] = ' ';
				campo::spazio[riga - 1][colonna + 1] = ' ';

			}
		break;

		case('V'): //MACCHINA NEMICA


			if (!immunità) {
				campo::punti = campo::punti - 10;
				*preso = true;
				if (campo::punti <= 0)
					campo::sconfitta();
				cout << "HAI COLPITO UNA MACCHINA NEMICA, -10 PUNTI" << endl;
				system("pause");

			}
			else
				campo::immunità = false;

			//Cancello l'ostacolo macchina

			if (campo::spazio[riga][colonna + 1] == 'A' || campo::spazio[riga][colonna - 1] == 'A') { //colpito da sinistra

				campo::spazio[riga - 1][colonna] = ' ';
				campo::spazio[riga + 1][colonna] = ' ';
				campo::spazio[riga][colonna - 1] = ' ';
				campo::spazio[riga][colonna + 1] = 'A';

			}
			else { //colpito da sopra
				campo::spazio[riga - 1][colonna] = ' ';
				campo::spazio[riga][colonna + 1] = ' ';
				campo::spazio[riga][colonna - 1] = ' ';
				campo::spazio[riga + 1][colonna] = ' ';


			}


			break;

		case('S'): //IMMUNITA'

			campo::immunità = true;
			cout << "IMMUNITA' ATTIVATA" << endl;
			system("pause");

			break;

		case('B'): //BENZINA

			campo::benzina = campo::benzina + 50;
			if (campo::benzina > 100)
				campo::benzina = 101;

			cout << "PIU' BENZINA!!" << endl;
			system("pause");

			break;

		default:
			break;
	}
}


void campo::colpito() {  // per farlo un po piú carino si puó scrivere un funzione e chiamarla sempre con var diverse

	bool *preso;
	preso = new bool;
	*preso = false;

	campo::cosaMiHaColpito(preso, campo::macchina.riga, campo::macchina.colonna + 1);
	campo::cosaMiHaColpito(preso, campo::macchina.riga, campo::macchina.colonna - 1);
	campo::cosaMiHaColpito(preso, campo::macchina.riga - 1, campo::macchina.colonna);
	campo::cosaMiHaColpito(preso, campo::macchina.riga, campo::macchina.colonna);

	if (!*preso) {
		campo::punti = campo::punti + 1;
	}

	if (campo::punti < 100)
		campo::livello = 1;
	else
		campo::livello = campo::punti / 100;
}

/*
void campo::colpito_InMovimento(char ostacolo, int riga, int colonna) {

	bool meno_punti = false;

	switch (ostacolo) {

	case('O'):
	case('E'): //OSTACOLI COMUNI

		if (!immunità) {

			campo::punti = campo::punti - (10 * campo::livello);
			if (campo::punti <= 0)
				campo::sconfitta();
			
			meno_punti = true;
		}
		else
			campo::immunità = false;
		break;

	case('?'): //MACCHINA NEMICA

		if (!immunità) {
			campo::punti = campo::punti - 10;
			if (campo::punti <= 0)
				campo::sconfitta();

			meno_punti = true;
		}
		else
			campo::immunità = false;

		//Cancello l'ostacolo macchina

		if (campo::spazio[riga][colonna - 1] == 'V') { //colpito da macchina tutta a sinistra

			campo::spazio[riga][colonna - 1] = ' ';
			campo::spazio[riga][colonna - 2] = ' ';
			campo::spazio[riga - 1][colonna - 1] = ' ';
			campo::spazio[riga + 1][colonna - 1] = ' ';

		}
		else if (campo::spazio[riga][colonna + 1] == 'V') { //colpito da macchina tutta a destra 


			campo::spazio[riga][colonna + 1] = ' ';
			campo::spazio[riga][colonna + 2] = ' ';
			campo::spazio[riga + 1][colonna + 1] = ' ';
			campo::spazio[riga - 1][colonna + 1] = ' ';

		}
		else { //colpito da macchina parzialmente a destra o a sinistra o sopra
			campo::spazio[riga - 1][colonna] = ' ';
			campo::spazio[riga - 2][colonna] = ' ';
		}

		if (campo::spazio[riga - 1][colonna + 1] == '*') { //colpito da sinistra
			campo::spazio[riga - 1][colonna - 1] = ' ';
			campo::spazio[riga - 1][colonna + 1] = '*';
		}
		else if (campo::spazio[riga - 1][colonna - 1] == '*') { //colpito da destra
			campo::spazio[riga - 1][colonna + 1] = ' ';
			campo::spazio[riga - 1][colonna - 1] = '*';
		}
		else { //colpito da sopra
			campo::spazio[riga - 1][colonna - 1] = ' ';
			campo::spazio[riga - 1][colonna + 1] = ' ';
		}

		break;

	case('V'): //MACCHINA NEMICA


		if (!immunità) {
			campo::punti = campo::punti - 10;
			if (campo::punti <= 0)
				campo::sconfitta();

			meno_punti = true;
		}
		else
			campo::immunità = false;

		//Cancello l'ostacolo macchina

		if (campo::spazio[riga][colonna + 1] == 'A' || campo::spazio[riga][colonna - 1] == 'A') { //colpito da sinistra

			campo::spazio[riga - 1][colonna] = ' ';
			campo::spazio[riga + 1][colonna] = ' ';
			campo::spazio[riga][colonna - 1] = ' ';
			campo::spazio[riga][colonna + 1] = 'A';
		}
		else { //colpito da sopra
			campo::spazio[riga - 1][colonna] = ' ';
			campo::spazio[riga][colonna + 1] = ' ';
			campo::spazio[riga][colonna - 1] = ' ';
		}


		break;

	case('S'): //IMMUNITA'

		campo::immunità = true;
		break;

	case('B'): //BENZINA

		campo::benzina = campo::benzina + 50;
		if (campo::benzina > 100)
			campo::benzina = 101;

		cout << "PIU' BENZINA!!";
		break;

	default:
		break;
	}

	if(!meno_punti)
		campo::punti = campo::punti + 1;

	if (campo::punti < 100)
		campo::livello = 1;
	else
		campo::livello = campo::punti / 100;
}
*/

// Lettere utilizzate = O E S T V


void campo::aggiungiOstacoli() {
	int limiteSotto = 2;
	int limiteSopra = 22;
	srand(time(NULL));

	if (campo::flagMacchina == 1) {
		campo::spazio[1][campo::posMacchinaCattiva] = 'V';
		campo::spazio[1][campo::posMacchinaCattiva + 1] = '?';
		campo::spazio[1][campo::posMacchinaCattiva - 1] = '?';
		campo::flagMacchina = 2;
	}
	else if (campo::flagMacchina == 2) {
		campo::spazio[1][campo::posMacchinaCattiva] = '?';
		campo::flagMacchina = 0;
	}
	else if (campo::righeDiff == 0) {
		campo::righeDiff = 4 - campo::livello;
		int j;// decide dove piazzare l'ostacolo
		int b;// decide che far stampare
		char ost = ' ';
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
			limiteSotto = 3;
			limiteSopra = 21;
				ost = '?';
				campo::flagMacchina = 1;
			break;
		}
		j = limiteSotto + rand() % limiteSopra;
		//salvare posizione macchina 
		campo::posMacchinaCattiva = j;
		campo::spazio[1][j] = ost;
	}
	else
	{
		campo::righeDiff = campo::righeDiff - 1;
	}
}
void campo::scriviMacchina()
{
	colpito();
	campo::benzina--;

	if (campo::benzina <= 0)
		campo::sconfitta();

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

	campo::spazio[18][27] = '$';

	campo::spazio[21][27] = '%';
}

char* campo::memOstacoli(char vett_ostacoli[]) {

	char *ostacolo_sopra = &campo::spazio[campo::macchina.riga - 1][campo::macchina.colonna];
	char *ostacolo_destra = &campo::spazio[campo::macchina.riga][campo::macchina.colonna + 1];
	char *ostacolo_sinistra = &campo::spazio[campo::macchina.riga][campo::macchina.colonna - 1];

	vett_ostacoli[0] = ' ';
	vett_ostacoli[1] = ' ';
	vett_ostacoli[2] = ' ';

	//ostacolo sopra
	if( *ostacolo_sopra != '*') 
	vett_ostacoli[0] = *ostacolo_sopra;

	//ostacolo destra
	if( *ostacolo_destra != '*')
	vett_ostacoli[1] = *ostacolo_destra;

	//ostacolo sinistra
	if(*ostacolo_sinistra != '*')
	vett_ostacoli[2] = *ostacolo_sinistra;

		return (vett_ostacoli);
}

void campo::muoviMacchina(char l) {

	char vett_ostacoli[3];
	char *p_vett;
	int pos_ostacolo;

	p_vett = memOstacoli(vett_ostacoli);

	if (l == 'a' || l == 'A' || l == 'd' || l == 'D' || l == 'w' || l == 'W') {
		
		switch (l) {
		case ('a'):
		case('A'):
			if (campo::spazio[campo::macchina.riga][campo::macchina.colonna - 2] != '#')
			{


				
				campo::spazio[campo::macchina.riga - 1][campo::macchina.colonna] = vett_ostacoli[0]; //Stellina sopra
				campo::spazio[campo::macchina.riga + 1][campo::macchina.colonna] = ' ';				 //Stellina sotto
				campo::spazio[campo::macchina.riga][campo::macchina.colonna + 1] = vett_ostacoli[1]; //Stellina sinistra

				campo::macchina.colonna = campo::macchina.colonna - 1;
				campo::scriviMacchina();

			}
			else
				cout << "non puoi andare di qua";//implementare una scritta piú efficace

			break;

		case('d'):
		case('D'): // qua vanno aggiunti i controlli di collisione
			if (campo::spazio[campo::macchina.riga][campo::macchina.colonna + 2] != '#') {

				campo::spazio[campo::macchina.riga - 1][campo::macchina.colonna] = vett_ostacoli[0]; //Stellina sopra
				campo::spazio[campo::macchina.riga + 1][campo::macchina.colonna] = ' ';				 //Stellina sotto
				campo::spazio[campo::macchina.riga][campo::macchina.colonna - 1] = vett_ostacoli[2]; //Stellina sinistra

				campo::macchina.colonna = campo::macchina.colonna + 1;
				campo::scriviMacchina();


			}
			else
				cout << "non puoi andare di qua";//implementare una scritta piú efficace
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

