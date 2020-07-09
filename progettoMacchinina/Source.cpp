#include "campo.h"
#include <conio.h>
#include <Windows.h>

int main() {

	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);

	bool logical = true;
	char direzione;
	bool sconfitta = false;
	char sino;

	campo i(RIGHE_CAMPO, COLONNE_CAMPO, 0, 1, false);
	i.sigla();
	system("pause");
	system("cls");
	i.regolamento();
	system("pause");
	system("cls");


		while (logical)
		{
			system("cls");
			campo c(RIGHE_CAMPO, COLONNE_CAMPO, 0, 1, false);
			c.stampa();
			system("pause");

			while (!c.perso) {

				system("cls");
				c.aggiungiOstacoli();
				c.stampa();
				c.muoviMacchina(_getch());
			}


			cout << "Premere un qualsiasi tasto per uscire o 0 per giocare di nuovo " << endl;
			sino = _getch();
			if (sino != '0')
				logical = false;
			//system("pause");
			
		}
		
		return 0;
}