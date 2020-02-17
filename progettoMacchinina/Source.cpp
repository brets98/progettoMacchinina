#include "campo.h"
#include <conio.h>
#include <Windows.h>

int main() {

	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);

	bool logical = true;
	char direzione;
	bool sconfitta = false;

	campo i(30, 40, 0, 1, false);
	i.sigla();
	system("pause");
	system("cls");
	i.regolamento();
	system("pause");
	system("cls");

	while (logical)
	{
		system("cls");
		campo c(30, 40, 0, 1, false);
		c.stampa();
		system("pause");

		while (!c.perso) {

			system("cls");
			c.aggiungiOstacoli();
			c.stampa();
			c.muoviMacchina(_getch());
		}
		
	}

	return 0;
}